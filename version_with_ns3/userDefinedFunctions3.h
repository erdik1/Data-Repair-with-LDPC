#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "NewComerNodeApp.h"
#include "UENodeApp.h"
#include "BSApp.h"

//#include "HandleMessages.h"
struct singleRepairAlgorithmV1Returns
{
	std::vector<std::string> totalHelperFiles;
	std::vector<struct ns> nodeStr;
	struct strP strParameters;
	std::vector<int> aliveLDPCStorageNodes;
	NewComerNodeApp* newcomerapp;
	UENodeApp** ueapps;
};

struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1NodeContainer(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<struct ns>, std::vector<int>, struct strP, int, std::vector<int>, double, int, NodeContainer, NodeContainer, int, int, InternetStackHelper, Ptr<Node>, MobilityHelper, Ipv4AddressHelper, Ipv4InterfaceContainer, Ipv4InterfaceContainer, Ptr<Node>, WifiHelper, std::string, int, int);