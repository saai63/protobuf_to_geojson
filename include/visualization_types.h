#ifndef VISUALIZATION_TYPES_H
#define VISUALIZATION_TYPES_H

#include <cstdint>
#include <vector>
#include <map>

namespace utils::visualization{
class Point{
public:
    double m_latitude, m_longitude;
    Point(double latitude, double longitude) : m_latitude(latitude), m_longitude(longitude)
    {
    }
};

class Line{
public:
    std::vector<Point> m_points;
    explicit Line(std::vector<Point> points) : m_points(std::move(points))
    {
    }
};

using FeatureProperties = std::map<std::string, std::string>;
}

#endif
