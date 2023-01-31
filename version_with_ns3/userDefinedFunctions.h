#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-helper.h"
#include "ns3/mobility-helper.h"
//#include "NewComerNodeApp.h"
//#include "UENodeApp.h"
//#include "BSApp.h" 

#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <random>
#include <list>
#include <iostream>




using namespace std;
using namespace ns3;

#ifndef USERDEFINEDFUNCTIONS_H
#define USERDEFINEDFUNCTIONS_H



//class NewComerNodeApp;

//class BSApp;
class MyApp : public Application
{
public:
  MyApp ();
  virtual ~MyApp ();

  /**
   * Register this type.
   * \return The TypeId.
   */
  static TypeId GetTypeId (void);
  //void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, MobilityHelper mobility, InternetStackHelper internet);
  //void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, InternetStackHelper internet);
  //void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);
  void Setup ();

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  //uint32_t        m_packetSize;
  //uint32_t        m_nPackets;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  //uint32_t        m_packetsSent;

  NodeContainer m_gNbNodes;
  NetDeviceContainer m_gNbNetDev; 
  InternetStackHelper m_internet;
};

struct strP {
	int numberofReadedSymbolsfromBSforLDPCRepair = 0;
	int numberofReadedSymbolsfromNodesforLDPCRepair = 0;
	int numberofLDPCHelpers = 0;
	double startTimeLDPCRepair = 0.0;
	double endTimeLDPCRepair = 0.0;
	double startTimeLDPCEncoding = 0.0;
	double endTimeLDPCEncoding = 0.0;
	int numberofLDPCRepairswithBaseStation = 0;
	int numberofLDPCRepairswithoutBaseStation = 0;
	int numberofLDPCRepairswithOnlyBaseStation = 0;
	double repairTimeforRemainderSymbols = 0.0;
	std::vector<std::string> usedNodes{};
};

struct ns {
	int nodeID = 0;
	int logicalNodeID = 0;
	std::string fileName = "";
	double arrivalTime = 0;
	double serviceTime = 0;
	double departureTime = 0;
	int isLive = 0;
	int encodingType = 0;
	int repairedNodeID = 0;
	double fileSize = 0;
};

struct departureReturns
{
	std::vector<struct ns> nodeStr;
	std::vector<int> leavingNodes;
	int numberofLDPCStorageNodes;
	std::vector<int> allDepartureNodes;
	std::vector<int> aliveLDPCStorageNodes;
	int numberofLostNodesforInterval;
};

struct repairReturns
{
	int isMultipleRepair;
	std::vector<struct ns> nodeStr;
	int numberofLDPCStorageNodes;
	struct strP strParameters;
	struct strP strParameters2;
	std::vector<int> leavingLDPCStorageNodes;
	std::vector<int> aliveLDPCStorageNodes;
};

struct encodingReturns
{
	int blockSize;
	std::vector<int> aliveLDPCStorageNodes;
	int totalEncodedData;
	std::vector<int> ldpcFileSizes;
	std::vector<struct ns> nodeStr;
};



struct singleRepairAlgorithmV1Returnsex 
{
	std::vector<std::string> totalHelperFiles;
	std::vector<struct ns> nodeStr;
	struct strP strParameters;
	std::vector<int> aliveLDPCStorageNodes;
};

struct generateHelpersReturns
{
	std::vector<int> helperSymbolIndexes;
	std::vector<std::vector<int>> allEquationsR2;
};

struct firstPhaseReturns
{
	//struct strP strParameters;
	std::vector<std::vector<uint8_t>> encodedData;
	std::vector<int> L;
	std::vector<int> currentLostLDPCChunkSymbols;
	std::vector<std::vector<int>> R2;
	std::vector<std::vector<int>> R2ReducedCopy;
	std::vector<int> unrepairedSymbolsfromNodes;
	std::vector<int> unrepairedSymbolsfromBS;
	std::vector<int> usedHelpers;
};

struct fakeFirstPhaseReturns
{
	//struct strP strParameters;
	std::vector<int> tempUsedHelpers{};
	std::vector<int> helperNodes;
	std::vector<int> currentHelperNodeIndexes{};
	// int currentColumnIndex;
	//std::vector<std::vector<uint8_t>> encodedData;
	std::vector<int> usedHelpers;
	std::vector<int> tempL;
	std::vector<std::vector<int>> R2ReducedCopy;
};

struct secondPhaseReturns
{
	//struct strP strParameters;
	std::vector<std::vector<uint8_t>> encodedData;
	int currentColumnIndex;
	std::vector<int> helperNodes;
	std::vector<int> currentHelperNodeIndexes{};
	int stopState;
};

struct fakeSecondPhaseReturns
{
	//struct strP strParameters;
	// std::vector<std::vector<uint8_t>> encodedData;
	// int currentColumnIndex;
	std::vector<int> helperNodes;
	int stopState;
	std::vector<int> failedSymbolIDsForRepairFromBS{};
	std::vector<int> currentHelperNodeIndexes{};
};

struct updateRecoveryEquationsReturns
{
	std::vector<int> selectedEquation;
	std::vector<int> selectedEquationReduced;
};

// class LDPCSingleRepairAlgorithmApp : public Application
// {
// public:
//   LDPCSingleRepairAlgorithmApp ();
//   virtual ~LDPCSingleRepairAlgorithmApp ();

//   /**
//    * Register this type.
//    * \return The TypeId.
//    */
//   static TypeId GetTypeId (void);
//   //void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate, int foundOne, std::string repairedFile, std::vector<int> currentLostSymbols, std::vector<string> totalHelperFiles, int cols, int quotient, std::vector<std::vector<int>> Hsys, std::vector<ns> nodeStr, std::vector<int> lostLDPCChunkSymbols, struct strP strParameters, int numberofRoundforBuffer, std::vector<int> aliveLDPCStorageNodes, double blockSize, int maxColLength, NodeContainer gNbNodes, NodeContainer ueNodes, int selectedLostNodeIndex, int selectedEmptyNodeIndex, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, MobilityHelper mobility, InternetStackHelper internet);
//   void Setup (Ptr<Socket> socket, Address defaultAddress, uint32_t packetSize, uint32_t nPackets, DataRate dataRate, int foundOne, std::string repairedFile, std::vector<int> currentLostSymbols, std::vector<string> totalHelperFiles, int cols, int quotient, std::vector<std::vector<int>> Hsys, std::vector<ns> nodeStr, std::vector<int> lostLDPCChunkSymbols, struct strP strParameters, int numberofRoundforBuffer, std::vector<int> aliveLDPCStorageNodes, double blockSize, int maxColLength, NodeContainer gNbNodes, NodeContainer ueNodes, int selectedLostNodeIndex, int selectedEmptyNodeIndex, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, InternetStackHelper internet, uint16_t servPort, Ptr<Node> apWifiNode, MobilityHelper mobility, Ipv4AddressHelper address, Ipv4InterfaceContainer ueIpIface, Ptr<Node> remoteHost, WifiHelper wifiHelper);

// private:
//   virtual void StartApplication (void);
//   virtual void StopApplication (void);

//   // void ScheduleTx (void);
//   //void SendPacket (void);
//   void LocalSendPacket (Ptr<NetDevice> device, Address& addr, uint32_t packetSize, std::vector<uint8_t> buffer2);

//   Ptr<Socket>     m_socket;
//   Address         m_peer;
//   uint32_t        m_packetSize;
//   uint32_t        m_nPackets;
//   DataRate        m_dataRate;
//   EventId         m_sendEvent;
//   bool            m_running;
//   uint32_t        m_packetsSent;

//   int 						m_foundOne;
//   std::string 		m_repairedFile;
//   std::vector<int> m_currentLostSymbols;
//   std::vector<std::string> m_totalHelperFiles;
//   int 						m_cols;
//   int 						m_quotient;
//   std::vector<std::vector<int>> m_Hsys;
//   std::vector<ns> m_nodeStr;
//   std::vector<int> m_lostLDPCChunkSymbols;
//   struct strP 		m_strParameters;
//   int 						m_numberofRoundforBuffer;
//   std::vector<int> m_aliveLDPCStorageNodes;
//   double 					m_blockSize;
//   int 						m_maxColLength;

//   NodeContainer m_gNbNodes;
//   NodeContainer m_ueNodes;
//   int m_selectedLostNodeIndex;
//   int m_selectedEmptyNodeIndex;
//   NetDeviceContainer m_gNbNetDev; 
//   NetDeviceContainer m_ueNetDev;
//   //MobilityHelper m_mobility;
//   InternetStackHelper m_internet;
//   uint16_t m_servPort;
//   Ptr<Node> m_apWifiNode; 
//   MobilityHelper m_mobility;
//   Ipv4AddressHelper m_address;
//   Ipv4InterfaceContainer m_ueIpIface;
//   Ptr<Node> m_remoteHost;
//   WifiHelper m_wifiHelper;
// };

// class NewComerNodeApp {
//   public:
//     Ptr<Socket> m_socket;
//     // //Address m_peer (),
//     // m_packetSize (0),
//     // m_nPackets (0),
//     // DataRate  m_dataRate (0),
//     EventId m_sendEvent; // Eventid of pending "send packet" event
//     bool m_running = false;
//     // m_packetsSent (0), 

//     Ptr<Node> m_senderNode;
//     Ptr<Node> m_receiverNode;
//     Ipv4Address m_senderAddress;
//     Ipv4Address m_receiverAddress;
//     uint16_t m_servPort;

//     int m_foundOne;
//     std::string m_repairedFile;
//     std::vector<std::string>  m_totalHelperFiles;
//     int m_cols;
//     std::vector<struct ns> m_nodeStr;
//     Ipv4InterfaceContainer m_ueIpIface;
//     //std::vector<int> m_currentHelperNodeIndexes;
//     std::vector<std::string> m_inputFiles;
//     //m_selectedHelperNodeIndex(),
//     int m_selectedEmptyNodeIndex;
//     int m_quotient;
//     std::string m_tempUsedEmptyNodeforRepair;
//     std::string m_baseStation;
//     std::vector<int> m_failedSymbolIDsForRepairFromBS;
//     int m_maxColLength;
//     std::vector<std::vector<int>> m_R1;
//     std::vector<std::vector<int>> m_R2;
//     std::vector<int> m_L;
//     std::vector<int> m_helperNodes;
//     int m_numberofRoundforBuffer;
//     std::vector<int> m_currentLostLDPCChunkSymbols;
//     struct strP m_strParameters;
//     std::vector<int> m_unrepairedSymbolsfromNodes;
//     std::vector<int> m_unrepairedSymbolsfromBS;
//     std::vector<std::vector<int>> m_allEquationsR2;

//     NodeContainer m_ueNodes;
//     Ptr<Node> m_remoteHost;
//     Ipv4InterfaceContainer m_internetIpIfaces;

//     std::vector<int> m_aliveLDPCStorageNodes;
//     std::vector<int> m_allHelperNodeIndexes;

//     virtual ~NewComerNodeApp();
//     TypeId GetTypeId ();
//     void Setup (int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<int> currentHelperNodeIndexes, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes);
//     void StartApplication ();
//     void StopApplication ();
// };

// class UENodeApp {
//   public:
//     Ptr<Socket> m_socket;
//     EventId m_sendEvent;  // Eventid of pending "send packet" event
//     bool m_running = false;
//     //Address m_peer (),
//     // m_packetSize (0),
//     // m_nPackets (0),
//     // DataRate m_dataRate (0),
//     // m_packetsSent (0), 

//     Ptr<Node> m_senderNode;
//     Ptr<Node> m_receiverNode;
//     Ipv4Address m_receiverAddress;
//     uint16_t m_servPort;

//     virtual ~UENodeApp();
//     TypeId GetTypeId ();
//     void Setup (Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address receiverAddress, uint16_t servPort);
//     void StartApplication ();
//     void StopApplication ();

// };

// class BSApp {
//   public:
//     Ptr<Socket> m_socket;
//     EventId m_sendEvent;  // Eventid of pending "send packet" event
//     bool m_running = false;
//     //Address m_peer (),
//     // m_packetSize (0),
//     // m_nPackets (0),
//     // DataRate m_dataRate (0),
//     // m_packetsSent (0), 

//     Ptr<Node> m_senderNode;
//     Ptr<Node> m_receiverNode;
//     Ipv4Address m_receiverAddress;
//     uint16_t m_servPort;

//     virtual ~BSApp();
//     TypeId GetTypeId ();
//     void Setup (Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address receiverAddress, uint16_t servPort);
//     void StartApplication ();
//     void StopApplication ();

// };

//void display2DVector(std::vector<std::vector<int>>);

//void display1DVector(std::vector<int>);

//void hildegardVonBingen(std::vector<std::vector<int>>, std::vector<std::vector<int>>, int, int, int, int, int, double, std::string, int, int, int, int, std::string, std::string, Ptr<Socket>, Address, NodeContainer, NodeContainer, NetDeviceContainer, NetDeviceContainer, InternetStackHelper, Ipv4InterfaceContainer);
void hildegardVonBingen(std::vector<std::vector<int>>, std::vector<std::vector<int>>, int, int, int, int, int, double, std::string, int, int, int, int, std::string, std::string);

struct encodingReturns ldpcEncodingforArrrayLDPC(std::vector<std::vector<int>>, int, std::string, std::string, int, int, int, int, std::vector<struct ns>);

std::vector<struct ns> processArrival(int, std::vector<struct ns>, std::vector<double>, std::vector<double>);

struct departureReturns processDeparture(int, std::vector<struct ns>, int, std::vector<int>, int, std::vector<int>, int, std::vector<int>, std::vector<int>, int);

//struct repairReturns processRepair(std::vector<std::vector<int>>, std::vector<struct ns>, int, std::vector<int>, int, int, double, std::vector<int>, struct strP, struct strP, int, double, std::vector<int>, Ptr<Socket>, Address, NodeContainer, NodeContainer, NetDeviceContainer, NetDeviceContainer, InternetStackHelper, Ipv4InterfaceContainer);
//struct repairReturns processRepair(std::vector<std::vector<int>>, std::vector<struct ns>, int, std::vector<int>, int, int, double, std::vector<int>, struct strP, struct strP, int, double, std::vector<int>, NodeContainer, NodeContainer, NetDeviceContainer, NetDeviceContainer, InternetStackHelper, Ptr<Node>, MobilityHelper, Ipv4AddressHelper, WifiHelper, Ipv4InterfaceContainer, Ipv4InterfaceContainer, Ptr<Node>);

//struct repairReturns processRepair(std::vector<std::vector<int>>, std::vector<struct ns>, int, std::vector<int>, int, int, double, std::vector<int>, struct strP, struct strP, int, double, std::vector<int>);
struct repairReturns processRepair(std::vector<std::vector<int>>, std::vector<struct ns>, int, std::vector<int>, int, int, double, std::vector<int>, struct strP, struct strP, int, double, std::vector<int>, NodeContainer, NodeContainer, InternetStackHelper, Ptr<Node>, MobilityHelper, Ipv4AddressHelper, WifiHelper, Ipv4InterfaceContainer, Ipv4InterfaceContainer, Ptr<Node>);

//struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<ns> nodeStr, std::vector<int>, struct strP, int, std::vector<int>, double, int);

//struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1NodeContainer(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<ns> nodeStr, std::vector<int>, struct strP, int, std::vector<int>, double, int, NodeContainer, NodeContainer, int, int, NetDeviceContainer, NetDeviceContainer, InternetStackHelper);
//struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1NodeContainer(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<struct ns>, std::vector<int>, struct strP, int, std::vector<int>, double, int, NodeContainer, NodeContainer, int, int, NetDeviceContainer, NetDeviceContainer, InternetStackHelper, Ptr<Node>, MobilityHelper, Ipv4AddressHelper, Ipv4InterfaceContainer, Ipv4InterfaceContainer, Ptr<Node>, WifiHelper, std::string, int);

//struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1NodeContainer(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<struct ns>, std::vector<int>, struct strP, int, std::vector<int>, double, int);
//struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1NodeContainer(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<struct ns>, std::vector<int>, struct strP, int, std::vector<int>, double, int, NodeContainer, NodeContainer, int, int, InternetStackHelper, Ptr<Node>, MobilityHelper, Ipv4AddressHelper, Ipv4InterfaceContainer, Ipv4InterfaceContainer, Ptr<Node>, WifiHelper, std::string, int, int);
//struct singleRepairAlgorithmV1Returnsex LDPCSingleRepairAlgorithmV1NodeContainer(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<struct ns>, std::vector<int>, struct strP, int, std::vector<int>, double, int, NodeContainer, NodeContainer, int, int, InternetStackHelper, Ptr<Node>, MobilityHelper, Ipv4AddressHelper, Ipv4InterfaceContainer, Ipv4InterfaceContainer, Ptr<Node>, WifiHelper, std::string, int, int);
void runLDPCSims();
std::vector<std::vector<int>> callHildegard(int, int, int, int, int, std::string, std::string);
std::vector<std::vector<int>> generateH_Array_LDPC(int, int, int);

struct generateHelpersReturns GenerateHelpers(std::vector<std::vector<int>>, int, std::vector<int>, std::vector<std::vector<int>>);
struct updateRecoveryEquationsReturns updateRecoveryEquations(int, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>);
struct fakeFirstPhaseReturns FakeFirstPhaseV2(std::vector<int>, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>, struct strP, std::vector<int>, std::vector<int>, std::vector<std::vector<int>>, int, std::vector<int>);
struct fakeSecondPhaseReturns FakeSecondPhaseV2(std::vector<int>, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>, struct strP, std::vector<std::vector<uint8_t>>, int, int, int, int, int, std::vector<int>);

struct firstPhaseReturns FirstPhaseV2(std::vector<int>, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>, struct strP, std::vector<int>, std::vector<int>, std::vector<std::vector<uint8_t>>, std::vector<std::vector<int>>);
struct secondPhaseReturns SecondPhaseV2(std::vector<int>, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>, struct strP, std::vector<std::vector<uint8_t>>, int, int, int);

#endif /* USERDEFINEDFUNCTIONS_H */
