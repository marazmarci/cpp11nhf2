/// Created by Marci on 2017. 12. 01.
#pragma once

#include "Node.h"


class UnorderedList : public Node {
    // TODO csak *li* gyerekei lehessenek
  public:
    UnorderedList() : Node{"ul"} {}
};

