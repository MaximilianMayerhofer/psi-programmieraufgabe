#include "node.h"
#include <iostream>

DAG::Node::Node(DAG::Data dataIn)
{
    std::cout << "Node created." << std::endl; // Debug
    data = dataIn;
}

DAG::Node::~Node()
{
    std::cout << "Node deleted." << std::endl; // Debug
}

int DAG::Node::getId()
{
    return data.id;
}

std::string DAG::Node::getName()
{
    return data.name;
}

// returns a complete list of all following nodes, from this node on that calls the method getSuccessorNodesDeep()
std::vector<std::weak_ptr<DAG::Node>> DAG::Node::getSuccessorNodesDeep()
{

    std::vector<std::weak_ptr<Node>> listPtrs; // generate empty list of weak pointers

    for (unsigned int i = 0; i < _successors.size(); i++)
    { // throughgo all direct successors
        {
            listPtrs.push_back(_successors[i]); // add their weak pointer

            std::vector<std::weak_ptr<Node>> listSuccessor; // generate empty list of weak pointers for successors of one successor

            auto successorShared = _successors[i].lock();             // make weak pointer shared before usage (doesn't work oherwise)
            listSuccessor = successorShared->getSuccessorNodesDeep(); // let them recursively give their successors weak pointers and their own

            listPtrs.insert(listPtrs.end(), listSuccessor.begin(), listSuccessor.end()); // add the pointers to list
        }
    }

    return listPtrs;
}

// checks whether the given node is already part of the following nodes, starting from this nodes that calls the method checkWetherNodeInFurtherGraph()
bool DAG::Node::checkWetherNodeInFurtherGraph(std::weak_ptr<Node> edgeToBeTested)
{
    bool cyclic = 0;                                    // initialize
    std::vector<std::weak_ptr<Node>> listPtrsToCompare; // generate empty list
    listPtrsToCompare = getSuccessorNodesDeep();        // fill it with all pointers to compare
    for (unsigned int i = 0; i < listPtrsToCompare.size(); i++)
    { // throughgo the list
        if (edgeToBeTested.lock() == listPtrsToCompare[i].lock())
        {               // check for equality of the strings
            cyclic = 1; // if yes, the potential precessor is successor at the same time, the graph would lose its acyclicity
        }
        else
        {
        } // just for completeness
    }
    return cyclic;
}

// adds a Node to an already existing Graph
bool DAG::Node::addNode(std::shared_ptr<DAG::Node> node)
{ // generate edge to already existing node

    bool flagError = 0; // initialize
    
    if (node->checkWetherNodeInFurtherGraph(node) == 1)
    { // check if graph would become cyclic
        flagError = 1;
    }
    for (unsigned int i = 0; i < _successors.size(); i++)
    { // throughgo existing edges
        if (node == _successors[i].lock())
        { // check if new edge would be identical to existing one
            flagError = 1;
        }
    }

    if (flagError == 0)
    {
        std::weak_ptr<DAG::Node> newSuccessor = node; // create weak pointer on new successor
        _successors.push_back(newSuccessor);          // add it to successors list
    }
    else
    {
    } // edge is not allowed or already present

    return flagError;
}

// removes an Edge from Graph
void DAG::Node::clearEdge(std::shared_ptr<Node> node)
{
    for (unsigned int i = 0; i < _successors.size(); i++)
    { // throughgo list of successors
        if (node == _successors[i].lock())
        {                                               // check for equality
            _successors.erase(_successors.begin() + i); // clear the desired successor
            break;
        }
        else
        {
        } // just for completeness, desired successor was not existent and had not to be deleted
    }
}

// removes an Edge from Graph
std::vector<std::weak_ptr<DAG::Node>> DAG::Node::getSuccessorNodes()
{
    clearInactiveEdges(); // clear the edges, that point on deleted nodes
    return _successors;   // return list of successors (as weak pointers to not cause problems, if nodes are deleted)
}

//remove Edges from Graph that lead to Nodes, that are not longer part of the Graph
void DAG::Node::clearInactiveEdges()
{
    for (unsigned int i = 0; i < _successors.size(); i++)
    { // throughgo all successors
        if (_successors[i].expired() == true)
        {                                               // check if node was deleted
            _successors.erase(_successors.begin() + i); // clear the inactive pointer out of the list
            i--;                                        // step one counter back, because the size of the vector has reduced
        }
    }
}