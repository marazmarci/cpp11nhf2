/// Created by Marci on 2017. 12. 01.
#pragma once

#include "Node.h"


class Paragraph : public Node {
  public:
    Paragraph(const std::shared_ptr<Node> & parentNode) : Node("p", parentNode) {}
};

