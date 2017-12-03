/// Created by Marci on 2017. 12. 01.
#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <experimental/optional>
#include "Attribute.h"



class Node {

  private:

    std::string tagName;
    std::vector<std::shared_ptr<Node>> children;
    std::vector<Attribute> attributes;
    std::weak_ptr<Node> parentNode;

  protected:
    // TODO explicit?
    //Node(std::string tagName) : tagName(std::move(tagName)) {}
    explicit Node(std::string tagName) : tagName{std::move(tagName)} {}

    // TODO std::move?
    Node(std::string tagName, const std::shared_ptr<Node> & parentNode)
            : tagName{std::move(tagName)}, parentNode{parentNode} {
        parentNode->addChild(std::shared_ptr<Node>{this}); // TODO itt van baj
    }

    void addChild(std::shared_ptr<Node> node) {
        // TODO add attributes to ID map
        children.emplace_back(node);
    }


  public:

    template <class NodeT, typename... ArgsT, typename = std::enable_if_t<std::is_base_of<Node,NodeT>::value>>
    auto newChild(ArgsT && ... args) {
        // TODO itt megint nem látja a base Node a saját smart pointer-jét... :'(
        // TODO megoldás: a newChild legyen static és vegye át a base Node smartPtr-jét is paramként
        // TODO             vagy valahogy a base Node tárolja el a saját smartPtr-jét
        // TODO             pl. úgy, hogy lenne egy make_node függvény, ami létrehoz egy node-ot, és a smart pointerjét belepakolja
        // TODO             és a make_node legyen friend
        auto newSharedPtr = std::shared_ptr<NodeT>{new NodeT{std::forward<ArgsT>(args)...}};
        addChild(newSharedPtr);
        return newSharedPtr;
    }

    /*
     *           /attrName\            /attrValue\
     * std::map< std::string, std::map<std::string, NodeSharedPtr> >
     *
     * A)
     *   1. subnode.addAttribute
     *   2. root->addChild(subnode)
     *              \-> foreach attribute: attrMap[attrName][attrValue] = subnode
     * B)
     *   1. root->addChild(subnode)
     *   2. subnode.addAttribute
     *   3.
     */

    void addAttribute(const Attribute & attribute) {
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

    // TODO InfoC++ ::experimental::4
    // TODO kell ez egyáltalán?
    const std::experimental::optional<std::string> getID() const {
        // TODO STL
        for (const Attribute & attribute : attributes)
            if (attribute.getName() == "id")
                return std::experimental::optional<std::string>{attribute.getValue()};
        return {};
    }



    // TODO getElementById

    // TODO begin
    // TODO end

    // TODO prototype

    // TODO static fromHtmlString ??



    //using NodeSharedPtr = std::shared_ptr<Node>;
    //using NodeWeakPtr = std::weak_ptr<Node>;
    //typedef std::shared_ptr<Node> NodeSharedPtr;
    //typedef std::weak_ptr<Node> NodeWeakPtr;

    virtual ~Node() {
        std::cout << "destructor\n";
    }

};

