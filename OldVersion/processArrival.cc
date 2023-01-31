#include "userDefinedFunctions.h"
#include <vector>

using namespace std;


std::vector<struct ns> processArrival(int arrivalNodeIndex, std::vector<struct ns> nodeStr, std::vector<double> arrivalTimes, std::vector<double> serviceTimes)
{
	// CREATING A NEW NODE STRUCT AS EMPTY
	struct ns newNodeStr = {};
	newNodeStr.nodeID = arrivalNodeIndex;
	newNodeStr.logicalNodeID = arrivalNodeIndex;
	newNodeStr.fileName = "";
	newNodeStr.arrivalTime = arrivalTimes.front();
	newNodeStr.serviceTime = serviceTimes.front();
	newNodeStr.departureTime = arrivalTimes.front() + serviceTimes.front();
	newNodeStr.isLive = 1;
	newNodeStr.encodingType = 0;
	newNodeStr.repairedNodeID = arrivalNodeIndex;
	newNodeStr.fileSize = 0;

	nodeStr.push_back(newNodeStr);

	return nodeStr;
}