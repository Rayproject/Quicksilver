//
// Created by Nikolay Yakovets on 2018-02-01.
//

#include "SimpleGraph.h"
#include "SimpleEstimator.h"

uint32_t length;
uint32_t labelCount[];
uint32_t sol;

SimpleEstimator::SimpleEstimator(std::shared_ptr<SimpleGraph> &g){

    // works only with SimpleGraph
    graph = g;


}

void SimpleEstimator::prepare() {
    length = graph.get()->getNoLabels();
    labelCount = new uint32_t[length];
    sol = 0;

    for(uint32_t i = 0; i < length; i ++) {
        labelCount[i] = 0;
    }

    for(uint32_t i = 0; i < length; i ++) {
        for(std::pair p: graph.get()->adj[i]) {
            labelCount[p.first] ++;
        };
    }

    for(uint32_t i = 0; i < length; i ++) {
        sol = sol + labelCount[i];
    }
    sol = sol / length;
}

cardStat SimpleEstimator::estimate(RPQTree *q) {

    return cardStat {sol, sol, sol};
}