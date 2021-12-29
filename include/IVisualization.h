#ifndef IVISUALIZATION_H
#define IVISUALIZATION_H

#include "visualization_types.h"

namespace utils::visualization{
class IVisualizer{
public:
    virtual bool addPoint(Point point,const FeatureProperties& properties) = 0;
    virtual bool addLine(Line line,FeatureProperties properties) = 0;
    virtual bool serializeToFile(const std::string& fileName) = 0;
};

}

#endif //IVISUALIZATION_H
