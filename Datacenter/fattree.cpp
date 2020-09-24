//
//  fattree.cpp
//  VNFPlacement
//
//  Created by Milad Ghaznavi on 5/2/15.
//  Copyright (c) 2015 Milad Ghaznavi. All rights reserved.
//

#include "fattree.h"
#include <stdexcept>

void KAryFatTree::connectCoreLevelToAggLevel_() {
    int pods          = podNum();
    int aggStartIndex = coreSwitchNum();
    int coreSwitches  = coreSwitchNum();
    
    for (int i = 0; i < coreSwitches; i++) {
        Identifier coreSwitchId = i;
        for (int port = 0; port < 22; port++) {
            Identifier aggSwitchId = coreSwitchNum()+port;
            this->addEdge(nodeFromId(coreSwitchId), nodeFromId(aggSwitchId));
        }//for
    }//for
}

void KAryFatTree::connectAggLevelToEdgeLevel_() {
    int aggStartIndex  = coreSwitchNum(); //12
    int edgeStartIndex = coreSwitchNum() + aggSwitchNum(); //12+22
    int aggSwitches    = aggSwitchNum(); // 22
    for (int i = 0; i < aggSwitches; i++) {
        Identifier aggSwitchId = aggStartIndex + i;
        for (int port = 0; port < 2; port++) {
            Identifier edgeSwitchId = edgeStartIndex + port + (i / 2) * 2;
            this->addEdge(nodeFromId(aggSwitchId), nodeFromId(edgeSwitchId));
        }//for
    }//for
}

void KAryFatTree::connectEdgeLevelToHosts_() {
    int edgeStartIndex = coreSwitchNum() + aggSwitchNum();
    int hostStartIndex = coreSwitchNum() + aggSwitchNum() + edgeSwitchNum();
    int edgeSwitches   = edgeSwitchNum();
    for (int i = 0; i < edgeSwitches; i++) {
        Identifier edgeSwitchId = edgeStartIndex + i;
        for (int port = 0; port < 2; port++) {
            Identifier hostId = hostStartIndex + i * (2) + port;
            this->addEdge(nodeFromId(edgeSwitchId), nodeFromId(hostId));
        }//for
    }//for
}

void KAryFatTree::init_(int k) {
    _k = 4;
    
    //Generate all nodes
    int nodes_count = coreSwitchNum() +
    aggSwitchNum () +
    edgeSwitchNum() +
    hostNum       ();
    
    for (int i = 0; i < nodes_count; i++)
        this->addNode();
    
    //Connect nodes to generate levels
    connectCoreLevelToAggLevel_();
    connectAggLevelToEdgeLevel_();
    connectEdgeLevelToHosts_();
}

KAryFatTree::KAryFatTree (int k) {
    if (k % 2 != 0){
        stringstream ss;
        ss << "K should be even! k is " << k << "!";
        throw std::invalid_argument(ss.str());
    }//if
    
    init_(k);
}

int KAryFatTree::k() {
    return _k;
}

int KAryFatTree::coreSwitchNum() {
    return 12;
    //return (k() / 2) * (k() / 2);
}

int KAryFatTree::aggSwitchNum() {
    return 22;
    //return k() * k() / 2;
}

int KAryFatTree::edgeSwitchNum() {
    return 22;
    //return k() * k() / 2;
}

int KAryFatTree::hostNum() {
    return 44;
    //return edgeSwitchNum() * (k() / 2);
}

int KAryFatTree::podNum() {
    return 12;
    //return k();
}

int KAryFatTree::coreLinkNum() {
    return 132;
    //return coreSwitchNum() * k();
}

int KAryFatTree::aggLinkNum() {
    return  200;
    //return aggSwitchNum() * (k() / 2);
}

int KAryFatTree::edgeLinkNum() {
    return 200;
    //return edgeSwitchNum() * (k() / 2);
}

KAryFatTree::NodeRangeIt KAryFatTree::coreSwitchIt() {
    return NodeRangeIt(*this,
                       this->nodeFromId(coreSwitchNum() - 1),
                       Node(Invalid()));
}

KAryFatTree::NodeRangeIt KAryFatTree::aggSwitchIt() {
    return NodeRangeIt(*this,
                       this->nodeFromId(coreSwitchNum() + aggSwitchNum() - 1),
                       this->nodeFromId(coreSwitchNum() - 1));
}

KAryFatTree::NodeRangeIt KAryFatTree::edgeSwitchIt() {
    return NodeRangeIt(*this,
                       this->nodeFromId(coreSwitchNum() + aggSwitchNum() + edgeSwitchNum() - 1),
                       this->nodeFromId(coreSwitchNum() + aggSwitchNum() - 1));
}

KAryFatTree::NodeRangeIt KAryFatTree::hostIt() {
    return NodeRangeIt(*this,
                       this->nodeFromId(coreSwitchNum() + aggSwitchNum() + edgeSwitchNum() + hostNum() - 1),
                       this->nodeFromId(coreSwitchNum() + aggSwitchNum() + edgeSwitchNum() - 1));
}

Node KAryFatTree::firstHost() {
    return nodeFromId(coreSwitchNum() + aggSwitchNum() + edgeSwitchNum());
}

Node KAryFatTree::lastHost() {
    return nodeFromId(nodeNum() - 1);
}

void KAryFatTree::copyTo(KAryFatTree& graph) {
    graph.clear();
    int n = nodeNum();
    int m = edgeNum();
    for (int i = 0; i < n; i++)
        graph.addNode();
    for (int i = 0; i < m; i++) {
        auto e = edgeFromId(i);
        graph.addEdge(u(e), v(e));
    }//for
    graph._k = _k;
}
