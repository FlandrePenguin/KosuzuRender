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
        if (property == "f") {
            auto [first, second, third] = spilt(ss, 0);
            faces.push_back(std::vector<int>{first, second, third});
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
        std::vector<int> face = getFace(i);
        Point3f baycentric = (getVertex(face[0]) + getVertex(face[1]) + getVertex(face[2])) / 3;
        bbox_min.x = std::min(bbox_min.x, baycentric.x);
        bbox_min.y = std::min(bbox_min.y, baycentric.y);
        bbox_min.z = std::min(bbox_min.z, baycentric.z);
        bbox_max.x = std::max(bbox_max.x, baycentric.x);
        bbox_max.y = std::max(bbox_max.y, baycentric.y);
        bbox_max.z = std::max(bbox_max.z, baycentric.z);
    }
    return Point3f((bbox_min.x + bbox_max.x) / 2, (bbox_min.y + bbox_max.y) / 2, (bbox_min.z + bbox_max.z) / 2);
}

std::vector<int> Model::getFace(int index) {
    return faces[index];
}

Point3f Model::getVertex(int index) {
    return vertices[index - 1];
}

std::tuple<int, int, int> Model::spilt(std::stringstream& ss, int index) {
    std::vector<std::string> vec;
    std::string str;
    while (ss >> str)
        vec.push_back(str);
    std::vector<std::vector<int>> index_vec(3);
    for (int i = 0; i < 3; ++i) {
        std::stringstream ss2(vec[i]);
        std::string token;
        while (std::getline(ss2, token, '/')) {
            index_vec[i].push_back(std::stoi(token.c_str()));
        }
    }
    return {index_vec[0][index], index_vec[1][index], index_vec[2][index]};
}