//
// Created by Nikolay Yakovets on 2018-02-01.
//

#include "SimpleGraph.h"
#include "SimpleEstimator.h"

SimpleEstimator::SimpleEstimator(std::shared_ptr<SimpleGraph> &g){
    uint32_t length = graph.getNoLabels();
    uint32_t labelCount[length];
    uint32_t sol = 0;
    // works only with SimpleGraph
    graph = g;
}

void SimpleEstimator::prepare() {

    for(uint32_t i = 0; i < length; i ++) {
        labelCount[i] = 0;
    }

    for(i = 0; i < length; i ++) {
        for(std::pair p: graph.adj[i]) {
            labelCount[p.first] ++;
        };
    }

    for(i = 0; i < length; i ++) {
        sol = sol + labelCount[i];
    }
    sol = sol / length;
}

cardStat SimpleEstimator::estimate(RPQTree *q) {

    return cardStat {sol, sol, sol};
}