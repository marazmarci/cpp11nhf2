#include <iostream>
#include <memory>
#include "Body.h"
#include "Paragraph.h"
#include "UnorderedList.h"


int main() {

    auto body = std::make_shared<Body>();
    auto p1 = std::make_shared<Paragraph>();
    auto p2 = std::make_shared<Paragraph>();
    auto ul = std::make_shared<UnorderedList>();


    return 0;
}