#include "userDefinedFunctions.h"
#include <vector>
#include <iostream>

using namespace std;

typedef struct departureReturns Struct;

Struct processDeparture(int departureNodeIndex, std::vector<struct ns> nodeStr, int counter, std::vector<int> allDepartureNodes, int counterLeavingNodes, std::vector<int> leavingNodes, int numberofLDPCStorageNodes, std::vector<int> sortedDepartureNodeIndexes, std::vector<int> aliveLDPCStorageNodes, int numberofLostNodesforInterval)
{
	Struct drLocal;
	cout << "We are here in loop 5_1 in processDeparture" << endl;
	// SETTING isLive PROPERTY OF THE LEAVING NODE
	nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].isLive = 0;
	// allDepartureNodes[counter] = sortedDepartureNodeIndexes[departureNodeIndex];
	// leavingNodes[counterLeavingNodes] = sortedDepartureNodeIndexes[departureNodeIndex];
	allDepartureNodes.push_back(sortedDepartureNodeIndexes[departureNodeIndex]); 
	leavingNodes.push_back(sortedDepartureNodeIndexes[departureNodeIndex]); 
	if (nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].encodingType == 1)
	{
		numberofLDPCStorageNodes = numberofLDPCStorageNodes - 1;
		aliveLDPCStorageNodes[nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].logicalNodeID] = -1;
	}
	numberofLostNodesforInterval = numberofLostNodesforInterval + 1;
	cout << "We are here in loop 5_2 in processDeparture" << endl;

	drLocal.nodeStr = nodeStr;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].nodeID = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].nodeID;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].logicalNodeID = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].logicalNodeID;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].fileName = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].fileName;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].arrivalTime = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].arrivalTime;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].serviceTime = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].serviceTime;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].departureTime = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].departureTime;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].isLive = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].isLive;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].encodingType = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].encodingType;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].repairedNodeID = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].repairedNodeID;
	// drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].fileSize = nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].fileSize;

	//cout << "We are here in loop 5_2_1 in processDeparture" << endl;
	drLocal.leavingNodes = leavingNodes;
	//cout << "We are here in loop 5_2_2 in processDeparture" << endl;
	drLocal.numberofLDPCStorageNodes = numberofLDPCStorageNodes;
	//cout << "We are here in loop 5_2_3 in processDeparture" << endl;
	drLocal.allDepartureNodes = allDepartureNodes;
	//cout << "We are here in loop 5_2_4 in processDeparture" << endl;
	drLocal.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	//cout << "We are here in loop 5_2_5 in processDeparture" << endl;
	drLocal.numberofLostNodesforInterval = numberofLostNodesforInterval;
	cout << "We are here in loop 5_3 in processDeparture" << endl;
	// cout << "counter: " << counter << endl;
	// cout << "size of leavingNodes: " << leavingNodes.size() << endl; 
	// cout << "numberofLDPCStorageNodes: " << numberofLDPCStorageNodes << endl; 
	// cout << "size of allDepartureNodes: " << allDepartureNodes.size() << endl; 
	// cout << "size of aliveLDPCStorageNodes: " << aliveLDPCStorageNodes.size() << endl; 
	// cout << "numberofLostNodesforInterval: " << numberofLostNodesforInterval << endl; 
	// cout << "departureNodeIndex: " << departureNodeIndex << endl;
	// cout << "sortedDepartureNodeIndexes[departureNodeIndex]: " << sortedDepartureNodeIndexes[departureNodeIndex]<< endl;
	// cout << "nodeID of nodeStr: " << nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].nodeID << endl; 
	// cout << "---" << endl;
	// cout << "nodeID of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].nodeID << endl; 
	// cout << "logicalNodeID of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].logicalNodeID << endl; 
	// cout << "fileName of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].fileName << endl; 
	// cout << "arrivalTime of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].arrivalTime << endl;
	// cout << "serviceTime of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].serviceTime << endl;
	// cout << "departureTime of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].departureTime << endl;
	// cout << "isLive of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].isLive << endl; 
	// cout << "encodingType of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].encodingType << endl;
	// cout << "repairedNodeID of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].repairedNodeID << endl;
	// cout << "fileSize of drLocal.nodeStr: " << drLocal.nodeStr[sortedDepartureNodeIndexes[departureNodeIndex]].fileSize << endl;
	cout << "We are here in processDeparture" << endl;
	return drLocal;
}