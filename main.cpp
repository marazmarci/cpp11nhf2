#include <iostream>
#include <memory>
#include "Body.h"
#include "Paragraph.h"
#include "UnorderedList.h"
#include "ListItem.h"
#include "Text.h"
#include "HtmlRoot.h"


int main() {

    //setlocale(LC_ALL, "");

    auto htmlRoot = std::make_shared<HtmlRoot>();
    auto body = std::make_shared<Body>(htmlRoot);
    auto p1 = std::make_shared<Paragraph>(body);
    auto p1text = std::make_shared<Text>(p1, "Szöveg szöveg szöveg szöveg.");
    auto ul = std::make_shared<UnorderedList>(body);
    auto li1 = std::make_shared<ListItem>(ul);
    auto li1text = std::make_shared<Text>(li1, "Felsorolás 1");
    auto li2 = std::make_shared<ListItem>(ul);
    auto li2text = std::make_shared<Text>(li2, "Felsorolás 2");
    auto p2 = std::make_shared<Paragraph>(body);
    auto p2text = std::make_shared<Text>(p2, "Szöveg szöveg.");

    htmlRoot->newChild<Body>();

    Node::newChild()


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


    Attribute ulAttr("id", "mylist");
    ul->addAttribute(ulAttr);

    /*body->addChild(p1);
    body->addChild(ul);
    body->addChild(p2);
    p1->addChild(p1text);
    ul->addChild(li1);
    ul->addChild(li2);
    li1->addChild(li1text);
    li2->addChild(li2text);
    p2->addChild(p2text);*/


    htmlRoot->print(std::cout);



    return 0;
}