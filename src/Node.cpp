#include "Node.hpp"
#include <pybind11/stl.h>

Node::Node(const std::string &type, const std::vector<std::vector<int>> &sourcepos)
    : _type(type), _sourcepos(sourcepos), _level(0) {}

void Node::appendChild(std::shared_ptr<Node> child)
{
    child->unlink();
    child->_parent = shared_from_this();
    if (_lastChild)
    {
        _lastChild->_next = child;
        child->_prev = _lastChild;
        _lastChild = child;
    }
    else
    {
        _firstChild = child;
        _lastChild = child;
    }
}

void Node::prependChild(std::shared_ptr<Node> child)
{
    child->unlink();
    child->_parent = shared_from_this();
    if (_firstChild)
    {
        _firstChild->_prev = child;
        child->_next = _firstChild;
        _firstChild = child;
    }
    else
    {
        _firstChild = child;
        _lastChild = child;
    }
}

void Node::unlink()
{
    if (_prev)
    {
        _prev->_next = _next;
    }
    else if (_parent)
    {
        _parent->_firstChild = _next;
    }
    if (_next)
    {
        _next->_prev = _prev;
    }
    else if (_parent)
    {
        _parent->_lastChild = _prev;
    }
    _parent = nullptr;
    _next = nullptr;
    _prev = nullptr;
}

void Node::insertAfter(std::shared_ptr<Node> sibling)
{
    sibling->unlink();
    sibling->_next = _next;
    if (sibling->_next)
    {
        sibling->_next->_prev = sibling;
    }
    sibling->_prev = shared_from_this();
    _next = sibling;
    sibling->_parent = _parent;
    if (!sibling->_next)
    {
        sibling->_parent->_lastChild = sibling;
    }
}

void Node::insertBefore(std::shared_ptr<Node> sibling)
{
    sibling->unlink();
    sibling->_prev = _prev;
    if (sibling->_prev)
    {
        sibling->_prev->_next = sibling;
    }
    sibling->_next = shared_from_this();
    _prev = sibling;
    sibling->_parent = _parent;
    if (!sibling->_prev)
    {
        sibling->_parent->_firstChild = sibling;
    }
}

std::string Node::getType() const { return _type; }
std::shared_ptr<Node> Node::getFirstChild() const { return _firstChild; }
std::shared_ptr<Node> Node::getLastChild() const { return _lastChild; }
std::shared_ptr<Node> Node::getNext() const { return _next; }
std::shared_ptr<Node> Node::getPrev() const { return _prev; }
std::shared_ptr<Node> Node::getParent() const { return _parent; }
std::vector<std::vector<int>> Node::getSourcepos() const { return _sourcepos; }
std::string Node::getLiteral() const { return _literal; }
void Node::setLiteral(const std::string &s) { _literal = s; }
std::string Node::getDestination() const { return _destination; }
void Node::setDestination(const std::string &s) { _destination = s; }
std::string Node::getTitle() const { return _title; }
void Node::setTitle(const std::string &s) { _title = s; }
std::string Node::getInfo() const { return _info; }
void Node::setInfo(const std::string &s) { _info = s; }
int Node::getLevel() const { return _level; }
void Node::setLevel(int s) { _level = s; }
bool Node::isContainer() const { return true; }

std::unique_ptr<NodeWalker> Node::walker()
{
    return std::make_unique<NodeWalker>(shared_from_this());
}

void Node::bind_node(pybind11::module &m)
{
    static bool registered = false; // Prevent re-registering
    if (registered)
        return;
    registered = true;

    pybind11::class_<Node, std::shared_ptr<Node>>(m, "Node")
        .def(pybind11::init<const std::string &, const std::vector<std::vector<int>> &>())
        .def("append_child", &Node::appendChild)
        .def("prepend_child", &Node::prependChild)
        .def("unlink", &Node::unlink)
        .def("insert_after", &Node::insertAfter)
        .def("insert_before", &Node::insertBefore)
        .def("get_type", &Node::getType)
        .def("get_first_child", &Node::getFirstChild)
        .def("get_last_child", &Node::getLastChild)
        .def("get_next", &Node::getNext)
        .def("get_prev", &Node::getPrev)
        .def("get_parent", &Node::getParent)
        .def("get_sourcepos", &Node::getSourcepos)
        .def("get_literal", &Node::getLiteral)
        .def("set_literal", &Node::setLiteral)
        .def("get_destination", &Node::getDestination)
        .def("set_destination", &Node::setDestination)
        .def("get_title", &Node::getTitle)
        .def("set_title", &Node::setTitle)
        .def("get_info", &Node::getInfo)
        .def("set_info", &Node::setInfo)
        .def("get_level", &Node::getLevel)
        .def("set_level", &Node::setLevel)
        .def("is_container", &Node::isContainer)
        .def("walker", &Node::walker);
}
