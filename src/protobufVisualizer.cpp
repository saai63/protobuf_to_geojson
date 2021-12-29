#include <fstream>
#include "protobufVisualizer.h"

namespace utils::visualization{

ProtobufVisualizer::ProtobufVisualizer()
{
    m_obj.set_type("FeatureCollection");
}

bool ProtobufVisualizer::addPoint(Point point, const FeatureProperties &properties)
{
    auto *feature = m_obj.add_features();
    auto *geom = feature->mutable_geometry();
    geom->set_type("Point");
    auto *cords = geom->add_coordinates();
    cords->add_internal_cordinates(point.m_longitude);
    cords->add_internal_cordinates(point.m_latitude);
    feature->set_type("Feature");
    if(!properties.empty())
    {
        auto* property = feature->mutable_properties();
        for(const auto &item : properties)
        {
            property->insert({item.first, item.second});
        }
    }
    return true;
}

bool ProtobufVisualizer::addLine(Line line, FeatureProperties properties)
{
    auto *feature = m_obj.add_features();
    auto *geom = feature->mutable_geometry();
    geom->set_type("LineString");
    for(const auto point : line.m_points)
    {
        auto *cords = geom->add_coordinates();
        cords->add_internal_cordinates(point.m_longitude);
        cords->add_internal_cordinates(point.m_latitude);
    }
    feature->set_type("Feature");
    if(!properties.empty())
    {

        for(const auto &item : properties)
        {
            auto* property = feature->mutable_properties();
            property->insert({item.first, item.second});
        }
    }
    return true;
}

bool ProtobufVisualizer::serializeToFile(const std::string &fileName)
{
    std::fstream os(fileName.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    return m_obj.SerializeToOstream(&os);
}

}
