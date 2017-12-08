#include <iostream>
#include <memory>
#include <sstream>
#include "Body.h"
#include "HtmlRoot.h"
#include "Paragraph.h"
#include "Text.h"
#include "UnorderedList.h"
#include "ListItem.h"


#define CGI



int main() {

    //setlocale(LC_ALL, "");

#ifdef CGI
    std::cout << "Content-type: text/html; charset=utf-8" << std::endl << std::endl;
#endif
    // TODO encoding

    auto htmlRoot = Node::make_node<HtmlRoot>();

    auto body = htmlRoot->newChild<Body>();
    auto p1 = body->newChild<Paragraph>();
    auto p1text = p1->newChild<Text>("Szöveg szöveg szöveg szöveg.");
    auto ul = p1->newChild<UnorderedList>();
    ul->addAttribute({"id","mylist"});
    auto li1 = ul->newChild<ListItem>();
    auto li1text = li1->newChild<Text>("Felsorolás 1");
    auto li2 = ul->newChild<ListItem>();
    auto li2text = li2->newChild<Text>("Felsorolás 2");
    auto p2 = body->newChild<Paragraph>();
    auto p2text = p2->newChild<Text>("Szöveg szöveg.");

    auto ul_sublist = ul->newChild<UnorderedList>();

    int n;
#ifdef CGI
    n = 5;
#else
    std::cout<<"Szia! Hány listaelemet kérsz? ";
    std::cin >> n;
#endif
    std::stringstream ss;

    for (int i = 1; i <= n; ++i) {
        ss.str("");
        ss << i << '.';
        ul_sublist->newChild<ListItem>()->newChild<Text>(ss.str());
        auto ul_subsublist = ul_sublist->newChild<UnorderedList>();
        for (int j = 1; j <= 5; ++j) {
            ss.str("");
            auto lili = ul_subsublist->newChild<ListItem>();
            ss << j << '.';
            lili->newChild<Text>(ss.str());
        }
    }





    /*
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

     */


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


    //Attribute ulAttr("id", "mylist");
    //ul->addAttribute(ulAttr);

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