#include "widget.h"
#include "./ui_widget.h"
#include <iostream>

RenderWidget::RenderWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::RenderWidget) {
    ui->setupUi(this);
    ui->FPSLabel->setStyleSheet("background:transparent; color:red");
    ui->FPSLabel->setVisible(false);
    initWindow();
    initRender();
    connect(&timer, &QTimer::timeout, this, &RenderWidget::render);
    timer.start();
}

RenderWidget::~RenderWidget() {
    delete[] z_buffer;
    delete model;
    delete ui;
}

void RenderWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawImage(0, 0, canvas);
    canvas = QImage(width, height, QImage::Format::Format_RGB888);
}

void RenderWidget::wheelEvent(QWheelEvent* event) {
    if (event->angleDelta().y() > 0 && fov > 1.f) {
        fov -= 0.1f;
    }
    if (event->angleDelta().y() < 0 && fov < 179.f) {
        fov += 0.1f;
    }
    projection_transformation = perspective(fov, (float)width / (float)height, 0.1f, 1e3);
    mvp();
    update();
}

void RenderWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        begin_pos = end_pos = Point3f(event->x(), event->y(), 0.f);
    }
}

void RenderWidget::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        end_pos = Point3f(event->x(), event->y(), 0.f);
        Vector3f screen_tangent_vector = end_pos - begin_pos;
        Vector3f world_tangent_vector = inverse(viewPort(width, height) * projection_transformation *
                                                view_transformation)(screen_tangent_vector);
        float world_tangent_vector_length = world_tangent_vector.length();
        Vector3f world_normal_vector = cross(world_tangent_vector, camera_look - camera_pos);
        model_transformation = rotate(-2000 * world_tangent_vector_length, world_normal_vector) *
                               model_transformation;
        begin_pos = end_pos;
        mvp();
        update();
    }
}

void RenderWidget::initWindow() {
    this->setWindowTitle("Kosuzu Render");
    this->setFixedSize(width, height);
    ui->FPSLabel->setVisible(true);
}

void RenderWidget::initRender() {
    model = new Model("../obj/Ganyu.obj");
    canvas = QImage(width, height, QImage::Format::Format_RGB888);
    z_buffer = new float[width * height];
    model_transformation = translate(Point3f(0, 0, 0) - model->getCenter());
    camera_pos = Point3f(0, 0, 50);
    camera_look = Point3f(0, 0, 0);
    camera_up = Vector3f(0, 1, 0);
    view_transformation = lookAt(camera_pos, camera_look, camera_up);
    projection_transformation = perspective(fov, (float)width / (float)height, 0.1f, 1e3);
    mvp();
}

int RenderWidget::fps() {
    static int fps = 0;
    static int last_time = QTime::currentTime().msecsSinceStartOfDay();
    static int frame_count = 0;
    ++frame_count;
    int current_time = QTime::currentTime().msecsSinceStartOfDay();
    if (current_time - last_time > 1000) {
        fps = frame_count;
        frame_count = 0;
        last_time = current_time;
    }
    return fps;
}

void RenderWidget::mvp() {
    transformation = viewPort(width, height) * projection_transformation *
                     view_transformation;
}

void RenderWidget::render() {
    ui->FPSLabel->setText(QStringLiteral("FPS : ") + QString::number(fps(), 'i', 0));
    std::fill_n(z_buffer, width * height, -1.f);
    for (int i = 0; i < model->numOfFaces(); ++i) {
        std::vector<int> face = model->getFace(i);
        Point3f screen_coords[3];
        Point3f world_coords[3];
        for (int j = 0; j < 3; ++j) {
            Point3f v = model->getVertex(face[j]);
            // screen_coords[j] = Point3f(int((v.x + 10.) * width / 20.), int((v.y + 0.5) * height / 20.), v.z);
            world_coords[j] = model_transformation(v);
            Point3f tv = transformation(world_coords[j]);
            screen_coords[j] = Point3f(int(tv.x + .5f), int(tv.y + .5f), tv.z);
        }
        Vector3f n = cross(world_coords[2] - world_coords[0], world_coords[1] - world_coords[0]);
        n = normalize(n);
        float intensity = dot(n, normalize(camera_look - camera_pos));
        if (intensity > 0)
            drawTriangle(screen_coords[0], screen_coords[1], screen_coords[2], QColor(intensity * 255, intensity * 255, intensity * 255));
    }
    update();
}

void RenderWidget::drawLine(int x0, int y0, int x1, int y1, QColor color) {
    bool steep = false;
    if (std::abs(x1 - x0) < std::abs(y1 - y0)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x1 < x0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; ++x) {
        if (steep)
            canvas.setPixelColor(y, x, color);
        else
            canvas.setPixelColor(x, y, color);
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0) ? 1 : -1;
            error2 -= 2 * dx;
        }
    }
}

Vector3f RenderWidget::barycentric(Point3f t0, Point3f t1, Point3f t2, Point3f p) {
    Vector3f sx = Vector3f(t1.x - t0.x, t2.x - t0.x, t0.x - p.x);
    Vector3f sy = Vector3f(t1.y - t0.y, t2.y - t0.y, t0.y - p.y);
    Vector3f u = cross(sx, sy);
    if (std::fabs(u.z) < 1)
        return Vector3f(-1, 1, 1);
    return Vector3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

bool RenderWidget::insideTriangle(Point3f t0, Point3f t1, Point3f t2, Point3f p) {
    float c1 = (t1 - t0).x * (p - t0).y - (t1 - t0).y * (p - t0).x;
    float c2 = (t2 - t1).x * (p - t1).y - (t2 - t1).y * (p - t1).x;
    float c3 = (t0 - t2).x * (p - t2).y - (t0 - t2).y * (p - t2).x;
    return (c1 >= 0 && c2 >= 0 && c3 >= 0) || (c1 <= 0 && c2 <= 0 && c3 <= 0);
}

void RenderWidget::drawTriangle(Point3f t0, Point3f t1, Point3f t2, QColor color) {
    Point3f ver_vec[3] = {t0, t1, t2};
    Vector2f bbox_min = Vector2f(MAX_FLOAT, MAX_FLOAT);
    Vector2f bbox_max = Vector2f(MIN_FLOAT, MIN_FLOAT);
    Vector2f clamp = Vector2f(width - 1, height - 1);
    for (int i = 0; i < 3; ++i) {
        bbox_min.x = std::max(0.f, std::min(ver_vec[i].x, bbox_min.x));
        bbox_min.y = std::max(0.f, std::min(ver_vec[i].y, bbox_min.y));
        bbox_max.x = std::min(clamp.x, std::max(ver_vec[i].x, bbox_max.x));
        bbox_max.y = std::min(clamp.y, std::max(ver_vec[i].y, bbox_max.y));
    }
    int block_size = 8;
    float orient = (bbox_max.x - bbox_min.x) / (bbox_max.y - bbox_min.y);
    if (orient < 0.4 || orient > 1.6) {
        auto [i01, i02, i03] = std::make_tuple(ver_vec[0].y - ver_vec[1].y, ver_vec[1].y - ver_vec[2].y, ver_vec[2].y - ver_vec[0].y);
        auto [j01, j02, j03] = std::make_tuple(ver_vec[1].x - ver_vec[0].x, ver_vec[2].x - ver_vec[1].x, ver_vec[0].x - ver_vec[2].x);
        auto [k01, k02, k03] = std::make_tuple(ver_vec[0].x * ver_vec[1].y - ver_vec[0].y * ver_vec[1].x,
                                               ver_vec[1].x * ver_vec[2].y - ver_vec[1].y * ver_vec[2].x, ver_vec[2].x * ver_vec[0].y - ver_vec[2].y * ver_vec[0].x);
        auto [cx1, cx2, cx3] = std::make_tuple(0, 0, 0);
        auto [cy1, cy2, cy3] = std::make_tuple(i01 * bbox_min.x + j01 * bbox_min.y + k01, i02 * bbox_min.x + j02 * bbox_min.y + k02, i03 * bbox_min.x + j03 * bbox_min.y + k03);
        for (int y = bbox_min.y; y <= bbox_max.y; ++y) {
            cx1 = cy1;
            cx2 = cy2;
            cx3 = cy3;
            for (int x = bbox_min.x; x <= bbox_max.x; ++x) {
                if ((cx1 >= 0 && cx2 >= 0 && cx3 >= 0) || (cx1 <= 0 && cx2 <= 0 && cx3 <= 0)) {
                    Vector3f bc = barycentric(t0, t1, t2, Point3f(x, y, 0));
                    float z = t0.z * bc.x + t1.z * bc.y + t2.z * bc.z;
                    if (z > z_buffer[x + y * width]) {
                        z_buffer[x + y * width] = z;
                        canvas.setPixelColor(x, y, color.rgb());
                    }
                }
                cx1 += i01;
                cx2 += i02;
                cx3 += i03;
            }
            cy1 += j01;
            cy2 += j02;
            cy3 += j03;
        }
    } else {
        for (int j = bbox_min.y; j <= bbox_max.y; j += block_size) {
            for (int i = bbox_min.x; i <= bbox_max.x; i += block_size) {
                auto [x1, y1, x2, y2] = std::make_tuple(i, j,
                                                        (i + block_size - 1 > bbox_max.x ? bbox_max.x : i + block_size - 1),
                                                        (j + block_size - 1 > bbox_max.y ? bbox_max.y : j + block_size - 1));
                if (insideTriangle(t0, t1, t2, Point3f(x1, y1, 0)) && insideTriangle(t0, t1, t2, Point3f(x2, y1, 0)) &&
                    insideTriangle(t0, t1, t2, Point3f(x1, y2, 0)) && insideTriangle(t0, t1, t2, Point3f(x2, y2, 0))) {
                    for (int y = y1; y <= y2; ++y) {
                        for (int x = x1; x <= x2; ++x) {
                            Vector3f bc = barycentric(t0, t1, t2, Point3f(x, y, 0));
                            float z = t0.z * bc.x + t1.z * bc.y + t2.z * bc.z;
                            if (z > z_buffer[x + y * width]) {
                                z_buffer[x + y * width] = z;
                                canvas.setPixelColor(x, y, color.rgb());
                            }
                        }
                    }
                    continue;
                }
                auto [i01, i02, i03] = std::make_tuple(ver_vec[0].y - ver_vec[1].y, ver_vec[1].y - ver_vec[2].y, ver_vec[2].y - ver_vec[0].y);
                auto [j01, j02, j03] = std::make_tuple(ver_vec[1].x - ver_vec[0].x, ver_vec[2].x - ver_vec[1].x, ver_vec[0].x - ver_vec[2].x);
                auto [k01, k02, k03] = std::make_tuple(ver_vec[0].x * ver_vec[1].y - ver_vec[0].y * ver_vec[1].x,
                                                       ver_vec[1].x * ver_vec[2].y - ver_vec[1].y * ver_vec[2].x, ver_vec[2].x * ver_vec[0].y - ver_vec[2].y * ver_vec[0].x);
                auto [cx1, cx2, cx3] = std::make_tuple(0, 0, 0);
                auto [cy1, cy2, cy3] = std::make_tuple(i01 * x1 + j01 * y1 + k01, i02 * x1 + j02 * y1 + k02, i03 * x1 + j03 * y1 + k03);
                for (int y = y1; y <= y2; ++y) {
                    cx1 = cy1;
                    cx2 = cy2;
                    cx3 = cy3;
                    for (int x = x1; x <= x2; ++x) {
                        if ((cx1 >= 0 && cx2 >= 0 && cx3 >= 0) || (cx1 <= 0 && cx2 <= 0 && cx3 <= 0)) {
                            Vector3f bc = barycentric(t0, t1, t2, Point3f(x, y, 0));
                            float z = t0.z * bc.x + t1.z * bc.y + t2.z * bc.z;
                            if (z > z_buffer[x + y * width]) {
                                z_buffer[x + y * width] = z;
                                canvas.setPixelColor(x, y, color.rgb());
                            }
                        }
                        cx1 += i01;
                        cx2 += i02;
                        cx3 += i03;
                    }
                    cy1 += j01;
                    cy2 += j02;
                    cy3 += j03;
                }
            }
        }
    }
}
