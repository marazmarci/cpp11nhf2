/// Created by Marci on 2017. 12. 01.
#pragma once

#include "Node.h"


struct Paragraph : public Node {
    Paragraph();
    explicit Paragraph(const std::string & text);
};

