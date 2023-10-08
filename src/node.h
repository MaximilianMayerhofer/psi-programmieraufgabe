#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <vector>
#include <memory>
#include "data.h"

namespace DAG
{
    class Node
    {
    public:
        // construct node with data
        Node(Data data);

        // destruct node
        ~Node();

        // add a successor node
        bool addNode(std::shared_ptr<Node> node); // node exists, only edge is generated

        // get id
        int getId();

        // get name
        std::string getName();

        // clear edge
        void clearEdge(std::shared_ptr<Node> node);

        // get successor nodes
        std::vector<std::weak_ptr<Node>> getSuccessorNodes();

        // clear the weak pointers to the deleted nodes
        void clearInactiveEdges();

        // check wether id (of potential precessor) is contained in chain of successors (and the node, shall point on, itself)
        bool checkWetherNodeInFurtherGraph(std::weak_ptr<Node> edgeToBeTested);

    private:
        Data data;

        // edges that point to other nodes
        std::vector<std::weak_ptr<Node>> _successors;

        // get all ids from the nodes the graph goes to from here
        std::vector<std::weak_ptr<Node>> getSuccessorNodesDeep();
    };

}

#endif //ALB_NODE_H