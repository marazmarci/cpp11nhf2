/// Created by Marci on 2017. 12. 01.
#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <optional>
#include "Attribute.h"


class Node {

    std::string tagName;
    std::vector<std::shared_ptr<Node>> children;
    std::vector<Attribute> attributes;

  public:

    // TODO explicit?
    explicit Node(std::string tagName) : tagName{std::move(tagName)} {}

    void addChild(std::shared_ptr<Node> nodePtr) {
        children.emplace_back(nodePtr);
    }

    void addAttribute(Attribute attribute) {
        attributes.emplace_back(attribute);
    }

    virtual void print(std::ostream & os) const {
        // TODO for helyett vmi STL függvény?
        // TODO <tagName /> syntax
        os << '<' << tagName;
        for (const Attribute & attr : attributes) // |name="value" |
            os << ' ' << attr.getName() << "=\"" << attr.getValue() << '"';
        os << '>';
        for (const std::shared_ptr<Node> & childPtr : children)
            childPtr.get()->print(os);
        os << "</" << tagName << '>';
    }

    const std::vector<std::shared_ptr<Node>> & getChildren() const {
        return children;
    }

    // TODO InfoC++ ::experimental::
    const std::experimental::optional<std::string> getID() const {
        // TODO STL
        for (const Attribute & attribute : attributes)
            if (attribute.getName() == "id")
                return std::experimental::optional<std::string>{attribute.getValue()};
        return {};
    }

    // TODO begin
    // TODO end

    // TODO prototype

    // TODO static fromHtmlString ??


};

