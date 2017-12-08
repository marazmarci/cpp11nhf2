/// Created by Marci on 2017. 12. 08.

#include "Text.h"


void Text::print(std::ostream & os, size_t indent) const {
    printIndents(os, indent);
    os << text << std::endl;
}
