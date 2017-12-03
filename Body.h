/// Created by Marci on 2017. 12. 01.
#pragma once

#include "Node.h"


class Body : public Node {
  public:
    Body() : Node{"body"} {}
    Body(const std::shared_ptr<Node> & parentNode) : Node("body", parentNode) {}
};

