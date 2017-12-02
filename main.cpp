#include <iostream>
#include <memory>
#include "Body.h"
#include "Paragraph.h"
#include "UnorderedList.h"
#include "ListItem.h"
#include "Text.h"


int main() {

    //setlocale(LC_ALL, "");

    auto body = std::make_shared<Body>();
    auto p1 = std::make_shared<Paragraph>();
    auto p1text = std::make_shared<Text>("Szöveg szöveg szöveg szöveg.");
    auto ul = std::make_shared<UnorderedList>();
    auto li1 = std::make_shared<ListItem>();
    auto li1text = std::make_shared<Text>("Felsorolás 1");
    auto li2 = std::make_shared<ListItem>();
    auto li2text = std::make_shared<Text>("Felsorolás 2");
    auto p2 = std::make_shared<Paragraph>();
    auto p2text = std::make_shared<Text>("Szöveg szöveg.");

    Attribute ulAttr("id", "mylist");
    ul->addAttribute(ulAttr);

    body->addChild(p1);
    body->addChild(ul);
    body->addChild(p2);
    p1->addChild(p1text);
    ul->addChild(li1);
    ul->addChild(li2);
    li1->addChild(li1text);
    li2->addChild(li2text);
    p2->addChild(p2text);


    body->print(std::cout);

    /*
     *  <body>
     *  <p>Szöveg szöveg szöveg szöveg.</p>
     *  <ul id="mylist">
     *      <li>Felsorolás 1</li>
     *      <li>Felsorolás 2</li>
     *  </ul>
     *  <p>Szöveg szöveg.</p>
     *  </body>
     */

    return 0;
}