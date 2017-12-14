/// Created by Marci on 2017. 12. 14.

#include "ListItem.h"
#include "Text.h"


ListItem::ListItem() : Node("li") {}

ListItem::ListItem(const std::string & text) : ListItem() {
    newChild<Text>(text);
}