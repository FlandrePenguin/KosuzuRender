#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include "geometry.h"
#include "model.h"
#include "transform.h"

#include <QPaintEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class RenderWidget;
}
QT_END_NAMESPACE

class RenderWidget : public QWidget {
    Q_OBJECT

public:
    RenderWidget(QWidget* parent = nullptr);
    ~RenderWidget();

public slots:
    void render();

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;

private:
    void initWindow();
    void initRender();
    int fps();
    void mvp();
    void drawLine(int x0, int y0, int x1, int y1, QColor color);
    Vector3f barycentric(Point3f t0, Point3f t1, Point3f t2, Point3f p);
    bool insideTriangle(Point3f t0, Point3f t1, Point3f t2, Point3f p);
    void drawTriangle(Point3f t0, Point3f t1, Point3f t2, QColor color);

private:
    Ui::RenderWidget* ui;
    Model* model;
    QImage canvas;
    float* z_buffer;
    QTimer timer;
    Transform transformation, model_transformation, view_transformation, projection_transformation;
    Point3f camera_pos, camera_look;
    Vector3f camera_up;
    float fov = 30;
    int width = 800;
    int height = 800;
};
#endif // RENDERWIDGET_H