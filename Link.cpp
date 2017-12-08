/// Created by Marci on 2017. 12. 08.
#include "Link.h"


Link::Link(const std::string & href) : Node("a") {
    addAttribute("href", href);
}