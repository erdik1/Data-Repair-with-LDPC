#include "userDefinedFunctions.h"
#include <vector>
#include <iostream>

using namespace std;

typedef struct departureReturns Struct;

Struct processDeparture(int departureNodeIndex, std::vector<struct ns> nodeStr, int counter, std::vector<int> allDepartureNodes, int counterLeavingNodes, std::vector<int> leavingNodes, int numberofLDPCStorageNodes, std::vector<int> sortedDepartureNodeIndexes, std::vector<int> aliveLDPCStorageNodes, int numberofLostNodesforInterval)
{
	Struct drLocal;
	
	// SETTING isLive PROPERTY OF THE LEAVING NODE
	nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].isLive = 0;

	allDepartureNodes.push_back(sortedDepartureNodeIndexes[departureNodeIndex]); 
	leavingNodes.push_back(sortedDepartureNodeIndexes[departureNodeIndex]); 
	if (nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].encodingType == 1)
	{
		numberofLDPCStorageNodes = numberofLDPCStorageNodes - 1;
		aliveLDPCStorageNodes[nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].logicalNodeID] = -1;
	}
	numberofLostNodesforInterval = numberofLostNodesforInterval + 1;

	drLocal.nodeStr = nodeStr;
	drLocal.leavingNodes = leavingNodes;
	drLocal.numberofLDPCStorageNodes = numberofLDPCStorageNodes;
	drLocal.allDepartureNodes = allDepartureNodes;
	drLocal.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	drLocal.numberofLostNodesforInterval = numberofLostNodesforInterval;

	return drLocal;
}