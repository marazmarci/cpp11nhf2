/// Created by Marci on 2017. 12. 01.
#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <experimental/optional>
#include <map>


class Node {

  private:

    std::string tagName;
    std::vector<std::shared_ptr<Node>> children;
    //std::vector<Attribute> attributes;
    std::map<std::string, std::string> attributes;
    std::weak_ptr<Node> parentNode;
    std::weak_ptr<Node> thisWeakPtr;

    std::map<std::string, std::shared_ptr<Node>> idMap;

    //       /attrName\            /attrValue\  //
    //std::map<std::string, std::map<std::string, std::shared_ptr<Node>>> attributeMap

    /*
     * A)
     *   1. subnode.addAttribute
     *   2. root->addChild(subnode)
     *              \-> foreach attribute: attrMap[attrName][attrValue] = subnode
     * B)
     *   1. root->addChild(subnode)
     *   2. subnode.addAttribute
     *   3.
     */



  protected:
    // TODO explicit?
    explicit Node(std::string tagName) : tagName{std::move(tagName)} {}

    void printIndents(std::ostream & os, size_t n, char indentChar = ' ') const {
        for (size_t i = 0; i < n; ++i)
            os << indentChar;
    }

    virtual void print(std::ostream & os, size_t indent) const {
        // TODO for helyett vmi STL függvény?
        // TODO <tagName /> syntax
        printIndents(os, indent);
        os << '<' << tagName;
        //for (const Attribute & attr : attributes) // |name="value" |
            //os << ' ' << attr.getName() << "=\"" << attr.getValue() << '"';
        for (const auto & attr : attributes)
            os << ' ' << attr.first << "=\"" << attr.second << '"';
        os << '>' << std::endl;
        for (const std::shared_ptr<Node> & childPtr : children)
            childPtr.get()->print(os, indent + 4);
        printIndents(os, indent);
        os << "</" << tagName << '>' << std::endl;
    }


  public:

    /*
    template <class NodeT, typename... ArgsT, typename = std::enable_if_t<std::is_base_of<Node,NodeT>::value>>
    auto newChild(ArgsT && ... args) {

        // TODO itt megint nem látja a base Node a saját smart pointer-jét... :'(
        // TODO megoldás: a newChild legyen static és vegye át a base Node smartPtr-jét is paramként
        // TODO             vagy valahogy a base Node tárolja el a saját smartPtr-jét
        // TODO             pl. úgy, hogy lenne egy make_node függvény, ami létrehoz egy node-ot, és a smart pointerjét belepakolja
        // TODO             és a make_node legyen friend

        // TODO Vagy esetleg:
        // TODO minden Node magától hozzon létre okospointert. (pl. getSmartPtr)

        // TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // TODO ASSZEM LEGJOBB megoldás: static factory method: make_node<NodeT>(...)
        // TODO                            és ez belerakja az új objektumba a smart ptr-jét.
        // TODO                          ezután már könnyű lessz a node-okat hierarchiába pakolni
        // TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


        auto newSharedPtr = std::shared_ptr<NodeT>{new NodeT{std::forward<ArgsT>(args)...}};
        addChild(newSharedPtr);
        return newSharedPtr;
    }
    */


    template <class NodeT, typename... ArgsT, typename = std::enable_if_t<std::is_base_of<Node,NodeT>::value>>
    static std::shared_ptr<NodeT> make_node(ArgsT && ... args) {
        auto newSharedPtr = std::make_shared<NodeT>(std::forward<ArgsT>(args)...);
        //auto newSharedPtr = std::make_shared<NodeT>(args...);
        newSharedPtr->thisWeakPtr = newSharedPtr;
        return newSharedPtr;
    }


    template <class NodeT, typename... ArgsT, typename = std::enable_if_t<std::is_base_of<Node,NodeT>::value>>
    std::shared_ptr<NodeT> newChild(ArgsT && ... args) {
        auto newSharedPtr = make_node<NodeT>(std::forward<ArgsT>(args)...);
        this->addChild(newSharedPtr);
        return newSharedPtr;
    }


    void addChild(std::shared_ptr<Node> childNode) {
        // TODO add attributes to ID map
        children.emplace_back(childNode);
        childNode->parentNode = thisWeakPtr;
    }

    void addAttribute(const std::string & key, const std::string & value) {
        //attributes.emplace_back(attribute);
        //attributes.insert(key, value);
        attributes[key] = value;
    }

    void setID(const std::string & id) {
        idMap[id] = thisWeakPtr.lock();
        addAttribute("id", id);
    }

    std::string

    /*const std::vector<Attribute> & getAttributes() const {
        return attributes;
    }*/

    void print(std::ostream & os) {
        print(os, 0);
    }

    const std::vector<std::shared_ptr<Node>> & getChildren() const {
        return children;
    }

    // TODO InfoC++ ::experimental::  !

    const std::experimental::optional<std::shared_ptr<Node>> getElementById(const std::string & id) const {
        return getElementWithAttr("id", id);
    }

    const std::experimental::optional<std::shared_ptr<Node>> getElementWithAttr(const std::string & key, const std::string & value) const {
        // BFS (asszem)
        // TODO STL
        for (const auto & child : children)
            for (const auto & attribute : child->attributes)
                if (attribute.getName() == key && attribute.getValue() == value)
                    return child;
        for (const auto & child : children) {
            auto found = child->getElementWithAttr(key, value);
            if (found)
                return found;
        }
        return {};
    }

    // TODO begin
    // TODO end

    // TODO prototype

    // TODO static fromHtmlString ??



    //using NodeSharedPtr = std::shared_ptr<Node>;
    //using NodeWeakPtr = std::weak_ptr<Node>;
    //typedef std::shared_ptr<Node> NodeSharedPtr;
    //typedef std::weak_ptr<Node> NodeWeakPtr;

};