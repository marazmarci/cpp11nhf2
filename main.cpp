#include <iostream>
#include <memory>
#include <sstream>
#include "Body.h"
#include "HtmlRoot.h"
#include "Paragraph.h"
#include "Text.h"
#include "UnorderedList.h"
#include "ListItem.h"
#include "Link.h"
#include "Image.h"
#include "Head.h"
#include "Meta.h"
#include "LineBreak.h"
#include "Title.h"


#define CGI
// #define JUST_HTML


// CGI && ! JUST_HTML
// Ha csak a CGI define van engedélyezve, akkor ezt a programot lefordított formájában lehet használni Common Gateway Interface script-ként.
// A program stdin bemenetként megkapja a HTTP request header-jeit, és a program stdout-ja fog visszaküldődni a kliens-böngészőnek.
// pl. egy Apache webszerveren a megfelelő ".htaccess" fájllal konfigurálva. Mellékeltem egy ilyet, amivel nekem működik.
//   A lefordított programmal egy könyvtárba kell tenni az Apache egyik publikus mappájába. Utána pl így lehet elérni: http://marci.hu/cpp11.exe

// ! CGI && JUST_HTML
// Ha csak a JUST_HTML define van engedélyezve, akkor a program kimenete egy az egyben pl. egy console pipe-pal fájlba írható, és egy böngészőben megnézhető

// ! CGI && ! JUST_HTML
// Ha egyik sincs engedélyezve, akkor pedig egy normál, "felhasználóbarát", konzolos programként fordul.

// CGI && JUST_HTML
// Ha mindegyik engedélyezve van, az ugyanolyan, mintha csak a CGI lenne.

#ifdef JUST_HTML
#define CGI
#endif


int main() {

#ifdef CGI
#ifndef JUST_HTML
    std::cout << "Content-type: text/html; charset=utf-8" << std::endl << std::endl;
#endif
#endif

#ifndef CGI
    std::cout << "Szia! A main.cpp elején lévő define-okkal tudod különböző módokban lefordítani a programot." << std::endl;
    std::cout << "Leírás a main.cpp elején a kommentekben!" << std::endl << std::endl;
#endif

    auto htmlRoot = Node::make_node<HtmlRoot>();

    auto head = htmlRoot->newChild<Head>();
    auto meta = head->newChild<Meta>();
    meta->addAttribute("charset","UTF-8"); // sajnos Windows-on nem tudtam elérni, hogy fájlba pipe-olva is jó legyen a karakterkódolás, pedig többel is próbálkoztam :(
    auto title = head->newChild<Title>("C++11 NHF2");
    auto body = htmlRoot->newChild<Body>();
    auto p1 = body->newChild<Paragraph>("Szöveg szöveg szöveg szöveg.");
    auto ul = p1->newChild<UnorderedList>();
    ul->setID("mylist");
    auto li1 = ul->newChild<ListItem>("Felsorolás 1");
    auto li2 = ul->newChild<ListItem>("Felsorolás 2");
    auto p2 = body->newChild<Paragraph>("Szöveg szöveg.");
    auto ul_sublist = ul->newChild<UnorderedList>();
    auto link = body->newChild<Link>("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    link->newChild<Text>("Ez egy link");
    body->newChild<LineBreak>();
    body->newChild<LineBreak>();
    body->newChild<Image>("http://abstrusegoose.com/strips/ars_longa_vita_brevis.png");

    int n;
#ifdef CGI
    n = 5;
#else
    std::cout<<"Hány listaelemet kérsz? ";
    std::cin >> n;
#endif
    std::stringstream ss;

    for (int i = 1; i <= n; ++i) {
        ss.str("");
        ss << i << '.';
        ul_sublist->newChild<ListItem>()->newChild<Text>(ss.str());
    }

    htmlRoot->print(std::cout);


#ifndef CGI

    auto mylist = htmlRoot->getElementById("mylist");
    std::cout << std::endl << std::endl << "htmlRoot->getElementById(\"mylist\")" << std::endl << std::endl;
    if (mylist)
        (*mylist)->print(std::cout);
    else
        std::cout << "nem találtam meg a mylist id-vel rendelkező tag-et! :(" << std::endl;

#endif

}