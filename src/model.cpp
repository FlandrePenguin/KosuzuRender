#include "model.h"
#include <fstream>
#include <sstream>

Model::Model(const std::string& filename)
    : bbox_min(Point3f(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT)), bbox_max(Point3f(MIN_FLOAT, MIN_FLOAT, MIN_FLOAT)), vertices(), faces() {
    std::fstream obj;
    obj.open(filename, std::ios::in);
    if (!obj.is_open()) {
        exit(-1);
    }
    std::string line;
    while (std::getline(obj, line)) {
        std::stringstream ss(line);
        std::string property;
        ss >> property;
        if (property == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            vertices.push_back(Point3f(x, y, z));
        }
        if (property == "vt") {
            float x, y, z;
            ss >> x >> y >> z;
            vertex_tangents.push_back(Vector3f(x, y, z));
        }
        if (property == "vn") {
            float x, y, z;
            ss >> x >> y >> z;
            vertex_normals.push_back(Vector3f(x, y, z));
        }
        if (property == "f") {
            auto [first, second, third] = spilt(ss, 0);
            faces.push_back(Face{first, second, third});
        }
    }
    obj.close();
}

Model::~Model() {}

size_t Model::numOfFaces() {
    return faces.size();
}

Point3f Model::getCenter() {
    for (int i = 0; i < numOfFaces(); ++i) {
        Face face = getFace(i);
        Point3f baycentric = (getVertex(face.vertex[0]) + getVertex(face.vertex[1]) + getVertex(face.vertex[2])) / 3;
        bbox_min.x = std::min(bbox_min.x, baycentric.x);
        bbox_min.y = std::min(bbox_min.y, baycentric.y);
        bbox_min.z = std::min(bbox_min.z, baycentric.z);
        bbox_max.x = std::max(bbox_max.x, baycentric.x);
        bbox_max.y = std::max(bbox_max.y, baycentric.y);
        bbox_max.z = std::max(bbox_max.z, baycentric.z);
    }
    return Point3f((bbox_min.x + bbox_max.x) / 2, (bbox_min.y + bbox_max.y) / 2, (bbox_min.z + bbox_max.z) / 2);
}

Face Model::getFace(int index) {
    return faces[index];
}

Point3f Model::getVertex(int index) {
    return vertices[index - 1];
}

Vector3f Model::getVertexTangent(int index) {
    return vertex_tangents[index - 1];
}

Vector3f Model::getVertexNormal(int index) {
    return vertex_normals[index - 1];
}

std::tuple<std::array<int, 3>, std::array<int, 3>, std::array<int, 3>> Model::spilt(std::stringstream& ss, int index) {
    std::vector<std::string> str_vec;
    std::string str;
    std::array<int, 3> vertex, vertex_tangent, vertex_normal;
    while (ss >> str)
        str_vec.push_back(str);
    for (int i = 0; i < 3; ++i) {
        std::stringstream ss2(str_vec[i]);
        std::string token;
        std::vector<int> face_property;
        while (std::getline(ss2, token, '/')) {
            face_property.push_back(std::stoi(token.c_str()));
        }
        vertex[i] = face_property[0];
        vertex_tangent[i] = face_property[1];
        vertex_normal[i] = face_property[2];
    }
    return {vertex, vertex_tangent, vertex_normal};
}