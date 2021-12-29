#ifndef PROTOBUFVISUALIZER_H
#define PROTOBUFVISUALIZER_H

#include "IVisualization.h"
#include "visualization.pb.h"

namespace utils::visualization{
    class ProtobufVisualizer : public IVisualizer{
    private:
        proto_visualizer m_obj;
    public:
        ProtobufVisualizer();
        bool addPoint(Point point,const FeatureProperties& properties) override;
        bool addLine(Line line,FeatureProperties properties) override;
        bool serializeToFile(const std::string& fileName) override;
    };
}

#endif //TINYEHORIZON_PROTOBUFVISUALIZER_H
