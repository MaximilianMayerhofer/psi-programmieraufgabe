#include "utility.h"


/* printGraph(Node, int) is a rekursive method that gives back an string, that includes all nodes of the Graph (in a formaly structured way)
/  it takes one Node (rootNode in the begining) as input and throughgoes the whole Graph
*/
std::string DAG::printGraph(std::shared_ptr<DAG::Node> currentNode, int depth)
{
    std::string oss;

    for (int i = 0; i < depth; i++)
    {
        oss.append("\t");
    }
    oss.append("-> Id: ");
    oss.append(std::to_string(currentNode->getId()));
    oss.append(", Name: ");
    oss.append(currentNode->getName());
    oss.append("\n");

    std::vector<std::weak_ptr<DAG::Node>> vectorOfNodes; // new vector of nodes (for successors)
    vectorOfNodes = currentNode->getSuccessorNodes();    // fill vector (may stay empty if no successor)

    for (int i = 0; i < vectorOfNodes.size(); i++)
    { // throughgo all successors (if is at least one)
        {
            auto nextNode = vectorOfNodes[i].lock();     // lock the weak_ptr
            oss.append(printGraph(nextNode, depth + 1)); // recursively call printGraph
        }
    }
    return oss;
}

/* printGraph(randomPath) is a method that gives back an string, that includes all nodes of the given Path (in a formaly structured way)
/  it takes a List of Nodes as input, that represents a valid Path of a Graph
*/
std::string DAG::printGraph(std::vector<std::weak_ptr<DAG::Node>> randomPath)
{
    std::string oss;

    for (int depth = 0; depth < randomPath.size(); depth++)
    {
        for (int i = 0; i < depth; i++)
        {
            oss.append("\t");
        }
        oss.append("-> Id: ");
        oss.append(std::to_string(randomPath[depth].lock()->getId()));
        oss.append(", Name: ");
        oss.append(randomPath[depth].lock()->getName());
        oss.append("\n");
    }
    return oss;
}

// generateRandomPath() chooses a valid Path through the given Graph (defined through Root Node)
std::vector<std::weak_ptr<DAG::Node>> DAG::generateRandomPath(std::shared_ptr<DAG::Node> root)
{
    std::srand(std::time(nullptr));
    std::vector<std::weak_ptr<DAG::Node>> randomPath;
    randomPath.push_back(root);
    std::vector<std::weak_ptr<DAG::Node>> successorList; // generate empty list
    while (1)
    {
        unsigned int size = randomPath.size();
        successorList = randomPath.back().lock()->getSuccessorNodes();
        if (successorList.size() > 0)
        {
            randomPath.push_back(successorList[std::rand() / ((RAND_MAX + 1u) / successorList.size())]);
        }
        else
        {
            break;
        }
    }
    return randomPath;
}