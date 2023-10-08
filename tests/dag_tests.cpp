#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells doctest to provide a main() - only do this in one cpp file

#include "iostream"
#include "doctest.h"
#include "node.cpp"
#include "utility.cpp"
#include "data.cpp"

// tests if first Node of Graph is properly initialized
TEST_CASE("Initialize node")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});

    CHECK(rootNode.get() != 0);
}

// tests if ID of Node ist saved and returned correctly
TEST_CASE("Get ID from Node")
{
    auto node = std::make_shared<DAG::Node>(DAG::Data{1234, "A"});

    CHECK(node->getId() == 1234);
}

// tests if an Edge between nodes is properly added
TEST_CASE("Adding an Edge between Nodes")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});
    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    rootNode->addNode(node2);

    std::vector<std::weak_ptr<DAG::Node>> successorsList;
    successorsList = rootNode->getSuccessorNodes();

    CHECK(node2 == successorsList[0].lock());
}

// tests if an Edge is properly deleted
TEST_CASE("Delete an Edge between Nodes")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});
    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    rootNode->addNode(node2);
    rootNode->clearEdge(node2);

    std::vector<std::weak_ptr<DAG::Node>> successorsList;
    successorsList = rootNode->getSuccessorNodes();

    CHECK(successorsList.empty());
}

// test if a cyclic Graph is detected
TEST_CASE("Cyclic Graph")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});
    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    rootNode->addNode(node2);
    auto node3 = std::make_shared<DAG::Node>(DAG::Data{3, "C"});
    node2->addNode(node3);

    std::weak_ptr<DAG::Node> edgeToBeTested;
    edgeToBeTested = node3;

    CHECK(rootNode->checkWetherNodeInFurtherGraph(edgeToBeTested.lock().get()) == 1);
}

// test if an acyclic Graph is recognized as such
TEST_CASE("Acyclic Graph")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});
    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    rootNode->addNode(node2);
    auto node3 = std::make_shared<DAG::Node>(DAG::Data{3, "C"});

    std::weak_ptr<DAG::Node> edgeToBeTested;
    edgeToBeTested = node3;

    CHECK(rootNode->checkWetherNodeInFurtherGraph(edgeToBeTested.lock().get()) == 0);
}

// test if a cyclic Graph is prevented during build up
TEST_CASE("Prohibit cyclic graph"){
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});
    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    auto node3 = std::make_shared<DAG::Node>(DAG::Data{3, "C"});

    rootNode->addNode(node2);
    node2->addNode(node3);
    node3->addNode(rootNode);

    CHECK(node3->checkWetherNodeInFurtherGraph(rootNode.get()) == 0);
}

// test if an inactive Edge is removed from Graph, when the coresponding Node was removed
TEST_CASE("Clear inactive Edge")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});
    std::vector<std::weak_ptr<DAG::Node>> successorsListBeforDeleting;
    int sizeBeforDeleting;
    {
        auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
        rootNode->addNode(node2);

        successorsListBeforDeleting = rootNode->getSuccessorNodes();
        sizeBeforDeleting = successorsListBeforDeleting.size();
    }
    rootNode->clearInactiveEdges();

    std::vector<std::weak_ptr<DAG::Node>> successorsListAfterDeleting;
    successorsListAfterDeleting = rootNode->getSuccessorNodes();
    int sizeAfterDeleting = successorsListAfterDeleting.size();

    CHECK(sizeAfterDeleting < sizeBeforDeleting);
}

// test if the Graph is properly printed out, with only the Root Node as input to printGraph()
TEST_CASE("Print graph")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});

    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    rootNode->addNode(node2);
    auto node3 = std::make_shared<DAG::Node>(DAG::Data{3, "C"});
    node2->addNode(node3);
    auto node4 = std::make_shared<DAG::Node>(DAG::Data{4, "D"});
    node2->addNode(node4);

    std::string oss;
    oss = DAG::printGraph(rootNode, 0);
    std::cout << oss;
    CHECK(oss == "-> Id: 1, Name: A\n\t-> Id: 2, Name: B\n\t\t-> Id: 3, Name: C\n\t\t-> Id: 4, Name: D\n");
}

// test if a Path is proberly printed, when all Nodes are given as input to printGraph()
TEST_CASE("Print Path")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});

    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    rootNode->addNode(node2);
    auto node3 = std::make_shared<DAG::Node>(DAG::Data{3, "C"});
    node2->addNode(node3);
    auto node4 = std::make_shared<DAG::Node>(DAG::Data{4, "D"});
    node3->addNode(node4);

    std::vector<std::weak_ptr<DAG::Node>> successorsList;
    successorsList = DAG::generateRandomPath(rootNode);

    std::string oss;
    oss = DAG::printGraph(successorsList);
    std::cout << oss;
    CHECK(oss == "-> Id: 1, Name: A\n\t-> Id: 2, Name: B\n\t\t-> Id: 3, Name: C\n\t\t\t-> Id: 4, Name: D\n");
}

// test if generateRandomPath() returns the correct Path, if the Graph has only one Path to choose from
TEST_CASE("Get random Path")
{
    auto rootNode = std::make_shared<DAG::Node>(DAG::Data{1, "A"});

    auto node2 = std::make_shared<DAG::Node>(DAG::Data{2, "B"});
    rootNode->addNode(node2);
    auto node3 = std::make_shared<DAG::Node>(DAG::Data{3, "C"});
    node2->addNode(node3);

    std::vector<std::weak_ptr<DAG::Node>> successorsList;
    successorsList = rootNode->getSuccessorNodes();

    std::vector<std::weak_ptr<DAG::Node>> randomPath;
    randomPath = DAG::generateRandomPath(rootNode);

    bool differenceFound;
    for (int i; i < successorsList.size(); i++)
    {
        if (successorsList[i].lock() != randomPath[i].lock())
        {
            differenceFound = 1;
        };
    }

    CHECK(differenceFound);
}

// 2021.07.16: All test execute correctly and succeed