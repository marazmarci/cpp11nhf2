/// Created by Marci on 2017. 12. 01.
#pragma once

#include "Node.h"


struct ListItem : public Node {
    ListItem();
    explicit ListItem(const std::string & text);
};