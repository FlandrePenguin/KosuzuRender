#ifndef MODEL_H
#define MODEL_H
#include "geometry.h"

#include <array>
#include <string>
#include <tuple>
#include <vector>

struct Face {
    std::array<int, 3> vertex;
    std::array<int, 3> vertex_tangent;
    std::array<int, 3> vertex_normal;
};
class Model {
public:
    Model(const std::string& filename);
    ~Model();

    size_t numOfFaces();
    Point3f getCenter();
    Face getFace(int index);
    Point3f getVertex(int index);
    Vector3f getVertexTangent(int index);
    Vector3f getVertexNormal(int index);

private:
    std::tuple<std::array<int, 3>, std::array<int, 3>, std::array<int, 3>> spilt(std::stringstream& ss, int index);

    Point3f bbox_min;
    Point3f bbox_max;
    std::vector<Point3f> vertices;
    std::vector<Vector3f> vertex_normals;
    std::vector<Vector3f> vertex_tangents;
    std::vector<Face> faces;
};
#endif // MODEL_H