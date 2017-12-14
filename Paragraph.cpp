/// Created by Marci on 2017. 12. 14.

#include "Paragraph.h"
#include "Text.h"


Paragraph::Paragraph() : Node("p") {}

Paragraph::Paragraph(const std::string & text) : Paragraph() {
    newChild<Text>(text);
}