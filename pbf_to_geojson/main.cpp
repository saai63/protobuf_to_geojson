#include <iostream>
#include <fstream>
#include <google/protobuf/util/json_util.h>
#include <nlohmann/json.hpp>
#include <iomanip>
#include "../proto/srcgen/visualization.pb.h"

std::string getFeatureType(const utils::visualization::proto_visualizer_FeatureType& featureType)
{
    switch(featureType)
    {
        case utils::visualization::proto_visualizer_FeatureType_POINT:
            return "Point";
        case utils::visualization::proto_visualizer_FeatureType_LINESTRING:
            return "LineString";
        default:
            return "";
    }
}

int main(int argc, char*argv[])
{
    if(argc != 3)
    {
        std::cout << "Usage protobuf_to_geojson <input_pbf> <output_geojson>" << std::endl;
        return -1;
    }
    try
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        std::string inputFile(argv[1]);
        std::string outputFile(argv[2]);

        utils::visualization::proto_visualizer protoVisualizer;
        std::fstream input(inputFile.c_str(), std::ios::in | std::ios::binary);
        if (!input) {
            std::cout << inputFile.c_str() << ": File not found.  Creating a new file." << std::endl;
        }
        else if (!protoVisualizer.ParseFromIstream(&input)) {
            std::cout << "Failed to parse input file." << std::endl;
            return -1;
        }
#ifdef MANUAL_JSON_CREATION
        nlohmann::json myJson;
        myJson["type"] = "FeatureCollection";
        auto geoJsonFeatures = nlohmann::json::array();
        for(const auto& item : protoVisualizer.features())
        {
            nlohmann::json tmp;
            tmp["type"] = "Feature";
            auto featureKind = item.geometry().type();
            tmp["geometry"]["type"] = getFeatureType(featureKind);
            if(featureKind == utils::visualization::proto_visualizer_FeatureType_POINT)
            {
                for(const auto& coordinates : item.geometry().coordinates())
                {
                    tmp["geometry"]["coordinates"] = coordinates.internal_cordinates();
                }
            }
            else if(featureKind == utils::visualization::proto_visualizer_FeatureType_LINESTRING)
            {
                for(const auto& coordinates : item.geometry().coordinates())
                {
                    tmp["geometry"]["coordinates"].push_back(coordinates.internal_cordinates());
                }
            }
            tmp["properties"] ={};
            for(const auto &property : item.properties())
            {
                tmp["properties"][property.first] = property.second;
            }
            geoJsonFeatures.push_back(tmp);
        }
        myJson["features"] = geoJsonFeatures;
#else
        std::string jsonString;
        google::protobuf::util::JsonPrintOptions options;
        options.add_whitespace = true;
        options.always_print_primitive_fields = true;
        google::protobuf::util::MessageToJsonString(protoVisualizer, &jsonString);

        nlohmann::json myJson = nlohmann::json::parse(jsonString);
        auto newFeatures = nlohmann::json::array();
        for (auto& el : myJson["features"].items())
        {
            auto feature = el.value();
            auto myArray = nlohmann::json::array();
            if(feature["geometry"]["type"] == "LineString")
            {
                for(const auto& iter : feature["geometry"]["coordinates"].items())
                {
                    myArray.push_back(iter.value()["internalCordinates"]);
                }
            }
            else
            {
                for(const auto& iter : feature["geometry"]["coordinates"].items())
                {
                    for(const auto& iter1 : iter.value()["internalCordinates"].items())
                    {
                        myArray.push_back(iter1.value());
                    }
                }
            }
            feature["geometry"]["coordinates"] = myArray;
            newFeatures.push_back(feature);
        }
        myJson["features"].clear();
        myJson["features"] = newFeatures;
#endif
        std::fstream of(outputFile.c_str(),std::ios::out | std::ios::trunc);
        of << myJson;
        google::protobuf::ShutdownProtobufLibrary();
    }

    catch(const std::exception& mainException)
    {
        std::cout << "Caught exception " << mainException.what() << std::endl;
    }
    return 0;
}