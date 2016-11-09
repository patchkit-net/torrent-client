#pragma once

#include <iostream>
#include <string>
#include <utility>

#include <boost/foreach.hpp>

#if defined(USE_YAML)
#include <yaml-cpp/yaml.h>
#elif defined(USE_JSON)
#include "json.hpp"
using json = nlohmann::json;
#endif

class Messages
{
public:
    static std::ostream& global()
    {
        std::cout << "G ";
        return std::cout;
    }

    static std::ostream& debug()
    {
        std::cout << "#=debug ";
        return std::cout;
    }

    static void respondSucceed(const std::string& p_message)
    {
#if defined(USE_YAML)
        YAML::Node node;
#elif defined(USE_JSON)
        json node;
#endif 
        node["status"] = "ok";
        node["message"] = p_message;

        message(node);
    }

    static void respondSucceed(
#if defined(USE_YAML)
        const YAML::Node& p_node
#elif defined(USE_JSON)
        const json& p_node
#endif
    )
    {
#if defined(USE_YAML)
        YAML::Node rootNode;
#elif defined(USE_JSON)
        json rootNode;
#endif 
        rootNode["status"] = "ok";
        rootNode["data"] = p_node;

        message(rootNode);
    }

    static void respondFailed(int code, const std::string& p_message)
    {
#if defined(USE_YAML)
        YAML::Node rootNode;
#elif defined(USE_JSON)
        json rootNode;
#endif 
        rootNode["status"] = "error";
        rootNode["code"] = code;
        rootNode["message"] = p_message;

        message(rootNode);
    }

private:

    static void message(
#if defined(USE_YAML)
        const YAML::Node& p_node
#elif defined(USE_JSON)
        const json& p_node
#endif
    )
    {
        using namespace std;
        cout << p_node << endl << "#=end" << endl;
    }

    
};