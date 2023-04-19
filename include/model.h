#ifndef MODEL_H
#define MODEL_H
#include "geometry.h"

#include <string>
#include <tuple>
#include <vector>

class Model {
public:
    Model(const std::string& filename);
    ~Model();

    size_t numOfFaces();
    Point3f getCenter();
    std::vector<int> getFace(int index);
    Point3f getVertex(int index);

private:
    std::tuple<int, int, int> spilt(std::stringstream& ss, int index);

    Point3f bbox_min;
    Point3f bbox_max;
    std::vector<Point3f> vertices;
    std::vector<std::vector<int>> faces;
};
#endif // MODEL_H