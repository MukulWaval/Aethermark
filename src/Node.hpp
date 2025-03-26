#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <string>
#include <pybind11/pybind11.h>
#include "NodeWalker.hpp"

class Node : public std::enable_shared_from_this<Node>
{
public:
    Node(const std::string &type, const std::vector<std::vector<int>> &sourcepos = {});

    void appendChild(std::shared_ptr<Node> child);
    void prependChild(std::shared_ptr<Node> child);
    void unlink();
    void insertAfter(std::shared_ptr<Node> sibling);
    void insertBefore(std::shared_ptr<Node> sibling);

    // getters and setters
    std::string getType() const;
    std::shared_ptr<Node> getFirstChild() const;
    std::shared_ptr<Node> getLastChild() const;
    std::shared_ptr<Node> getNext() const;
    std::shared_ptr<Node> getPrev() const;
    std::shared_ptr<Node> getParent() const;
    std::vector<std::vector<int>> getSourcepos() const;
    std::string getLiteral() const;
    void setLiteral(const std::string &s);
    std::string getDestination() const;
    void setDestination(const std::string &s);
    std::string getTitle() const;
    void setTitle(const std::string &s);
    std::string getInfo() const;
    void setInfo(const std::string &s);
    int getLevel() const;
    void setLevel(int s);
    bool isContainer() const;

    // node walker
    std::unique_ptr<NodeWalker> walker();

    // Pybind11 binding method
    static void bind_node(pybind11::module &m);

private:
    std::string _type;
    std::vector<std::vector<int>> _sourcepos;
    std::string _literal;
    std::string _destination;
    std::string _title;
    std::string _info;
    int _level;

    std::shared_ptr<Node> _parent;
    std::shared_ptr<Node> _firstChild;
    std::shared_ptr<Node> _lastChild;
    std::shared_ptr<Node> _prev;
    std::shared_ptr<Node> _next;
};

#endif
