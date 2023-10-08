#ifndef DAG_UTILITY_H
#define DAG_UTILITY_H

#include "node.h"
#include <memory>
#include <iostream>
#include <random>

namespace DAG
{
    // print whole graph
    std::string printGraph(std::shared_ptr<DAG::Node> currentNode, int depth); 

    // print one Path of Graph
    std::string printGraph(std::vector<std::weak_ptr<DAG::Node>> randomPath);  
    
    // generate a randomly chosen, valid Path through Graph
    std::vector<std::weak_ptr<DAG::Node>> generateRandomPath(std::shared_ptr<DAG::Node> root);

};

#endif //ALB_UTILITY_H
