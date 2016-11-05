#pragma once

#include <iostream>
#include <string>
#include <utility>

#include <boost/foreach.hpp>
#include <yaml-cpp/yaml.h>

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
        YAML::Node node;
        node["status"] = "ok";
        node["message"] = p_message;

        message(node);
    }

    static void respondSucceed(const YAML::Node& p_node)
    {
        YAML::Node rootNode;
        rootNode["status"] = "ok";
        rootNode["data"] = p_node;

        message(rootNode);
    }

    static void respondFailed(int code, const std::string& p_message)
    {
        YAML::Node rootNode;
        rootNode["status"] = "error";
        rootNode["code"] = code;
        rootNode["message"] = p_message;

        message(rootNode);
    }

private:

    static void message(const YAML::Node& p_node)
    {
        using namespace std;
        cout << p_node << endl << "#=end" << endl;
    }

    
};