//
// Created by Nikolay Yakovets on 2018-02-01.
//

#include "SimpleGraph.h"
#include "SimpleEstimator.h"

uint32_t numLabels;
uint32_t numVertices;
//uint32_t** twoPaths;
//uint32_t** forksSplits;
cardStat* labelData;
uint32_t** inPaths;
uint32_t** outPaths;
std::vector<uint32_t> queryVector;


SimpleEstimator::SimpleEstimator(std::shared_ptr<SimpleGraph> &g){

    // works only with SimpleGraph
    graph = g;


}

void SimpleEstimator::prepare() {
    numLabels = graph.get()->getNoLabels();
    numVertices = graph.get()->getNoVertices();
//    twoPaths = new uint32_t*[numLabels];
//    forksSplits = new uint32_t*[numLabels];
//
//    auto * dups = new uint32_t[numLabels];
//
//    for(auto i = 0; i < numLabels; i ++) {
//        twoPaths[i] = new uint32_t[numLabels];
//        forksSplits[i] = new uint32_t[numLabels];
//        for(auto j = 0; j < numLabels; j ++) {
//            twoPaths[i][j] = 0;
//            forksSplits[i][j] = 0;
//        }
//    }
//
//    for(auto i = 0; i < numVertices; i ++) {
//        for(auto p1: graph.get()->adj[i]) {
//            for(auto j = 0; j < numLabels; j ++) {
//                dups[j] = 0;
//            }
//            for(auto p2: graph.get()->adj[p1.second]) {
//                dups[p2.first] ++;
//                if(dups[p2.first] > 1) {
//                    forksSplits[p1.first][p2.first] ++;
//                }
//                twoPaths[p1.first][p2.first] ++;
//            }
//        }
//    }
//
//    for(auto i = 0; i < numLabels; i ++) {
//        for(auto p1: graph.get()->reverse_adj[i]) {
//            for(auto j = 0; j < numLabels; j ++) {
//                dups[j] = 0;
//            }
//            for(auto p2: graph.get()->reverse_adj[p1.second]) {
//                dups[p2.first] ++;
//                if(dups[p2.first] > 1) {
//                    forksSplits[p2.first][p1.first] --;
//                }
//            }
//        }
//    }

    inPaths = new uint32_t*[numLabels];
    outPaths = new uint32_t*[numLabels];
    labelData = new cardStat[numLabels];
    for(auto i = 0; i < numLabels; i ++) {
        inPaths[i] = new uint32_t[numVertices];
        outPaths[i] = new uint32_t[numVertices];
        for(auto j = 0; j < numVertices; j ++) {
            inPaths[i][j] = 0;
            outPaths[i][j] = 0;
        }
    }

    for(auto i = 0; i < numVertices; i ++) {
        for(auto p: graph.get()->adj[i]) {
            inPaths[p.first][i] ++;
            outPaths[p.first][p.second] ++;
        }
    }

    uint32_t numPaths = 0;
    uint32_t numIn = 0;
    uint32_t numOut = 0;
    for(auto i = 0; i < numLabels; i ++) {
        for(auto j = 0; j < numVertices; j ++) {
            numPaths += inPaths[i][j];
            if(inPaths[i][j] > 0)
                numIn ++;
            if(outPaths[i][j] > 0)
                numOut ++;

        }
        labelData[i] = {numOut, numPaths, numIn};
    }
}

void treeToList(RPQTree* q) {
    if(q->isConcat()) {
        treeToList(q->left);
        treeToList(q->right);
    }
    else if(q->isLeaf()) {
        auto label = q->data.at(0);
        uint32_t labelInt = label - '0';
        if(q->data.at(1) == '+') {
            queryVector.push_back(labelInt);
        }
        else queryVector.push_back(-labelInt);
    }
}

cardStat reverse(cardStat c) {
    return {c.noIn, c.noPaths, c.noOut};
}

cardStat SimpleEstimator::estimate(RPQTree *q) {
    // treeToList takes tree q and adds all of the nodes in the global variable queryVector. Basically you now have
    // the query as a vector. You can access
    // the first value in the query with queryVector[0], the next with queryVector[1] etc.
    treeToList(q);

    // All of the cardStat objects that you wanted for every label are in labelData. If you want to access the cardStat
    // for label i then use labelData[i]. MAKE SURE to check if labels in queryVector are negative (it means that
    // you need the reversed edges of the label). If value j is negative, then you can access its cardStat with
    // reverse(labelData[-i]). Ask me on Skype if you have any questions.




    //your code here

    queryVector.clear();
    return cardStat {0, 0, 0};
}