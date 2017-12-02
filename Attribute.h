/// Created by Marci on 2017. 12. 01.
#pragma once

#include <string>
#include <utility>


class Attribute {
    const std::string name;
    const std::string value;
  public:
    Attribute(std::string name, std::string value) : name{std::move(name)}, value{std::move(value)} {}
    const inline std::string & getName() const {
        return name;
    }
    const inline std::string & getValue() const {
        return value;
    }
};

