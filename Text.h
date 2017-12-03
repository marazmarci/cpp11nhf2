/// Created by Marci on 2017. 12. 01.
#pragma once

#include <utility>

#include "Node.h"


class Text : public Node {
    const std::string text;
  public:
    Text(const std::shared_ptr<Node> & parentNode, std::string text) : Node("", parentNode), text(std::move(text)) {}

    ///Text(std::string text) : Node{""}, text{std::move(text)} {}
    void print(std::ostream &os) const override {
        os << text;
    }
};

