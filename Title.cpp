/// Created by Marci on 2017. 12. 08.
#include "Title.h"
#include "Text.h"


Title::Title(const std::string & text) : Node("title") {
    newChild<Text>(text);
}
