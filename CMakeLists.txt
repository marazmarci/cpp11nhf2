cmake_minimum_required(VERSION 3.9)
project(C__11_NHF2)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Werror -Wextra -pedantic -O0)

add_executable(C__11_NHF2 main.cpp Node.h Body.h Text.h Paragraph.h UnorderedList.h ListItem.h HtmlRoot.h Head.h Text.cpp Node.cpp Link.cpp Link.h Image.cpp Image.h Title.cpp Paragraph.cpp ListItem.cpp)