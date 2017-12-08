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
    std::map<std::string, std::string> attributes;
    std::weak_ptr<Node> parentNode;
    std::weak_ptr<Node> thisWeakPtr;
    std::map<std::string, std::shared_ptr<Node>> idMap;

    void setParent(const std::weak_ptr<Node> & parent);
    void pushIDsUpInTree();

    template <typename Iterator>
    void addIDs(Iterator begin, Iterator end) {
        idMap.insert(begin, end);
    }

  protected:

    explicit Node(std::string tagName) : tagName{std::move(tagName)} { }
    static void printIndents(std::ostream & os, size_t n, char indentChar = ' ');
    virtual void print(std::ostream & os, size_t indent) const;

  public:

    void adoptChild(std::shared_ptr<Node> childNode);
    void addAttribute(const std::string & key, const std::string & value);
    void setID(const std::string & id);
    void print(std::ostream & os);
    const std::vector<std::shared_ptr<Node>> & getChildren() const;
    const std::experimental::optional<std::shared_ptr<Node>> getElementById(const std::string & id) const;
    const std::experimental::optional<std::shared_ptr<Node>> getElementWithAttr(const std::string & key, const std::string & value) const;

    template <class NodeT, typename... ArgsT, typename = std::enable_if_t<std::is_base_of<Node,NodeT>::value>>
    static std::shared_ptr<NodeT> make_node(ArgsT && ... args) {
        auto newSharedPtr = std::make_shared<NodeT>(std::forward<ArgsT>(args)...);
        newSharedPtr->thisWeakPtr = newSharedPtr;
        return newSharedPtr;
    }

    template <class NodeT, typename... ArgsT, typename = std::enable_if_t<std::is_base_of<Node,NodeT>::value>>
    std::shared_ptr<NodeT> newChild(ArgsT && ... args) {
        auto newSharedPtr = make_node<NodeT>(std::forward<ArgsT>(args)...);
        this->adoptChild(newSharedPtr);
        return newSharedPtr;
    }

    // egyszer majd:
    // TODO begin
    // TODO end
    // TODO prototype
    // TODO static fromHtmlString

    virtual ~Node() = default;
    // csináltam számlálós ellenőrzést, és mindegyik Node példány "destruktálódott"

};