/// Created by Marci on 2017. 12. 08.

#include "Node.h"


void Node::print(std::ostream & os) {
    print(os, 0);
}

void Node::setID(const std::string & id) {
    addAttribute("id", id);
}

void Node::pushIDsUpInTree() {
    auto parent = parentNode.lock();
    if (parent) {
        parent->addIDs(idMap.begin(), idMap.end());
        parent->pushIDsUpInTree();
    }
}

void Node::setParent(const std::weak_ptr<Node> & parent) {
    this->parentNode = parent;
    pushIDsUpInTree();
}

void Node::printIndents(std::ostream & os, size_t n, char indentChar) {
    for (size_t i = 0; i < n; ++i)
        os << indentChar;
}

void Node::print(std::ostream & os, size_t indent) const {
    // TODO for helyett vmi STL függvény?

    printIndents(os, indent);

    // nyitó tag
    os << '<' << tagName;
    // nyitó tag-en belüli attribútumok
    for (const auto & attr : attributes)
        os << ' ' << attr.first << "=\"" << attr.second << '"';

    if (children.empty()) {
        // rövidített záró tag, ha nincs gyerekelem
        os << " />" << std::endl;
    } else {
        os << '>' << std::endl;

        // gyerekelemek kiírása
        for (const std::shared_ptr<Node> & childPtr : children)
            childPtr.get()->print(os, indent + 4);
        printIndents(os, indent);

        // záró tag
        os << "</" << tagName << '>' << std::endl;
    }
}

void Node::adoptChild(std::shared_ptr<Node> childNode) {
    children.emplace_back(childNode);
    childNode->setParent(thisWeakPtr);
}

void Node::addAttribute(const std::string & key, const std::string & value) {
    //attributes.emplace_back(attribute);
    //attributes.insert(key, value);
    attributes[key] = value;
    if (key == "id") {
        //idMap[value] = thisWeakPtr.lock();
        pushIDsUpInTree();
    }
}

const std::vector<std::shared_ptr<Node>> & Node::getChildren() const {
    return children;
}

const std::experimental::optional<std::shared_ptr<Node>> Node::getElementById(const std::string & id) const {
    //return getElementWithAttr("id", id);
    if (idMap.count(id))
        return {idMap.at(id)};
    return {};
}

const std::experimental::optional<std::shared_ptr<Node>>
Node::getElementWithAttr(const std::string & key, const std::string & value) const {
    // BFS algoritmussal működik
    for (const auto & child : children)
        for (const auto & attribute : child->attributes)
            if (attribute.first == key && attribute.second == value)
                return child;
    for (const auto & child : children) {
        auto found = child->getElementWithAttr(key, value);
        if (found)
            return found;
    }
    return {};
}
