/// Created by Marci on 2017. 12. 08.
#include "Image.h"


Image::Image(const std::string & src) : Node("img") {
    addAttribute("src", src);
}