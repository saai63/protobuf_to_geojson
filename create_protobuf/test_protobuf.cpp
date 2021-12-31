#include "protobufVisualizer.h"
#include <memory>

using namespace utils::visualization;
int main()
{
    std::unique_ptr<IVisualizer> visualizer = std::make_unique<ProtobufVisualizer>();
    visualizer->addPoint({43.1761398773783,-84.3475341796875},{});
    std::vector<Point> line;
    line.emplace_back(43.12003138678775, -84.31182861328125);
    line.emplace_back(43.033764503405315, -84.03030395507812);
    line.emplace_back(43.26420629463836, -84.00146484374999);
    FeatureProperties properties;
    properties["SpeedLimit"] = "50";
    visualizer->addLine(Line{line},properties);
    visualizer->serializeToFile("test.pbf");
    return 0;
}
