/// Created by Marci on 2017. 12. 01.
#pragma once

#include "Node.h"


class ListItem : public Node {
  public:
    ListItem(const std::shared_ptr<UnorderedList> & parentNode) : Node("li", parentNode) {}
};

