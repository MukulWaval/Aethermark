#include "NodeWalker.hpp"
#include "Node.hpp"

NodeWalker::NodeWalker(std::shared_ptr<Node> root)
    : current(root), root(root), entering(true) {}

std::pair<bool, std::shared_ptr<Node>> NodeWalker::next()
{
    if (!current)
        return {false, nullptr};

    std::shared_ptr<Node> cur = current;
    bool wasEntering = entering; // Capture entering status before updating

    if (entering)
    {
        // If entering and container, move to first child
        if (cur->isContainer() && cur->getFirstChild())
        {
            current = cur->getFirstChild();
        }
        else
        {
            entering = false;
        }
    }
    else if (cur == root)
    {
        // If exiting the root, end traversal
        current = nullptr;
    }
    else if (!cur->getNext())
    {
        // Move to parent when no next sibling
        current = cur->getParent();
        entering = false;
    }
    else
    {
        // Move to next sibling
        current = cur->getNext();
        entering = true;
    }

    return {wasEntering, cur};
}

void NodeWalker::resumeAt(std::shared_ptr<Node> node, bool enteringState)
{
    current = node;
    entering = enteringState;
}

void NodeWalker::bind_node_walker(pybind11::module &m)
{
    static bool registered = false; // Prevent re-registering
    if (registered)
        return;
    registered = true;

    pybind11::class_<NodeWalker>(m, "NodeWalker")
        .def(pybind11::init<std::shared_ptr<Node>>())
        .def("next", &NodeWalker::next)
        .def("resume_at", &NodeWalker::resumeAt);
}