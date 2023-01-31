#ifndef BSApp_H
#define BSApp_H

#include "userDefinedFunctions.h"
// #include "messages.h"
#include "HandleMessages.h"
using namespace std;
using namespace ns3;

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/eps-bearer-tag.h"

#include "ns3/address.h"
#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/data-rate.h"
#include "ns3/traced-callback.h"
#include "ns3/application.h"


class BSApp : public Application
{
  public:
    Ptr<Socket> m_socket;
    EventId m_sendEvent;  // Eventid of pending "send packet" event
    bool m_running = false;
    //Address m_peer (),
    // m_packetSize (0),
    // m_nPackets (0),
    // DataRate m_dataRate (0),
    // m_packetsSent (0), 

    Ptr<Node> m_senderNode;
    Ptr<Node> m_receiverNode;
    Ipv4Address m_senderAddress;
    Ipv4Address m_receiverAddress;
    uint16_t m_servPort;

    int m_foundOne;
    std::string m_repairedFile;
    std::vector<std::string>  m_totalHelperFiles;
    int m_cols;
    std::vector<struct ns> m_nodeStr;
    Ipv4InterfaceContainer m_ueIpIface;
    //std::vector<int> m_currentHelperNodeIndexes;
    std::vector<std::string> m_inputFiles;
    int m_selectedHelperNodeIndex;
    int m_selectedEmptyNodeIndex;
    int m_quotient;
    std::string m_tempUsedEmptyNodeforRepair;
    std::string m_baseStation;
    std::vector<int> m_failedSymbolIDsForRepairFromBS;
    int m_maxColLength;
    std::vector<std::vector<int>> m_R1;
    std::vector<std::vector<int>> m_R2;
    std::vector<int> m_L;
    std::vector<int> m_helperNodes;
    int m_numberofRoundforBuffer;
    std::vector<int> m_currentLostLDPCChunkSymbols;
    struct strP m_strParameters;
    std::vector<int> m_unrepairedSymbolsfromNodes;
    std::vector<int> m_unrepairedSymbolsfromBS;
    std::vector<std::vector<int>> m_allEquationsR2;
    NodeContainer m_ueNodes;
    Ptr<Node> m_remoteHost;
    Ipv4InterfaceContainer m_internetIpIfaces;
    std::vector<int> m_aliveLDPCStorageNodes;
    std::vector<int> m_allHelperNodeIndexes;
    int m_selectedEmptyNodeLogicalIndex;

    BSApp();
    virtual ~BSApp();
    TypeId GetTypeId ();
    //void Setup(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address receiverAddress, uint16_t servPort);
    void Setup(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string>  totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int selectedHelperNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex);
    void StartApplication ();
    void StopApplication ();

};

BSApp::BSApp()
{

}

BSApp::~BSApp ()
{
  m_socket = 0;
}

/* static */
TypeId BSApp::GetTypeId (void)
{
  // static TypeId tid = TypeId ("BSApp").SetParent<Application> ().SetGroupName ("Tutorial").AddConstructor<BSApp> ();
  static TypeId tid = TypeId ("BSApp").SetParent<Application> ().SetGroupName ("Applications").AddConstructor<BSApp> ();
  return tid;
}

void BSApp::Setup(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int selectedHelperNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex)
{
  //m_socket = socket;
  // m_peer = defaultAddress;
  // m_packetSize = packetSize;
  // m_nPackets = nPackets;
  // m_dataRate = dataRate;

  m_senderNode = senderNode;
  m_receiverNode = receiverNode;
  m_senderAddress = senderAddress;
  m_receiverAddress = receiverAddress;
  m_servPort = servPort;

  m_foundOne = foundOne; 
  m_repairedFile = repairedFile; 
  m_totalHelperFiles = totalHelperFiles;
  m_cols = cols; 
  m_nodeStr = nodeStr;
  m_ueIpIface = ueIpIface;
  //m_currentHelperNodeIndexes = currentHelperNodeIndexes; 
  m_inputFiles = inputFiles;
  m_selectedHelperNodeIndex = selectedHelperNodeIndex; 
  m_selectedEmptyNodeIndex = selectedEmptyNodeIndex;
  m_quotient = quotient; 
  m_tempUsedEmptyNodeforRepair = tempUsedEmptyNodeforRepair; 
  m_baseStation = baseStation; 
  m_failedSymbolIDsForRepairFromBS = failedSymbolIDsForRepairFromBS; 
  m_maxColLength = maxColLength;
  m_R1 = R1; 
  m_R2 = R2; 
  m_L = L;  
  m_helperNodes = helperNodes; 
  m_numberofRoundforBuffer = numberofRoundforBuffer; 
  m_currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
  m_strParameters = strParameters; 
  m_unrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes; 
  m_unrepairedSymbolsfromBS = unrepairedSymbolsfromBS; 
  m_allEquationsR2 = allEquationsR2;
  m_ueNodes = ueNodes;
  m_remoteHost = remoteHost;
  m_internetIpIfaces = internetIpIfaces;
  m_aliveLDPCStorageNodes = aliveLDPCStorageNodes;
  m_allHelperNodeIndexes = allHelperNodeIndexes;
  m_selectedEmptyNodeLogicalIndex = selectedEmptyNodeLogicalIndex;
}

void BSApp::StartApplication (void)
{
  m_running = true;
  // m_packetsSent = 0;
  // m_socket->Bind ();
  // m_socket->Connect (m_peer);

  // m_servPort = servPort + this->GetNode()->GetId();

  //cout << "We are in StartApplication of BSApp" << endl;
  cout << "\n\n\n BS Node ID (this->GetNode()->GetId()): " << this->GetNode()->GetId() <<" started in BSApp::StartApplication."<<endl;
  cout << "Sender Node ID (NewComerNode) in BSApp::StartApplication: " << m_senderNode->GetId() << endl;
  cout << "Receiver Node ID (BS) in BSApp::StartApplication: " << m_receiverNode->GetId() << endl;

  //Ptr<HandleMessages> BSNodeObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort);
  //Ptr<HandleMessages> BSNodeObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedEmptyNodeIndex, m_selectedHelperNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_ueNodes, m_remoteHost, m_internetIpIfaces, m_aliveLDPCStorageNodes, m_allHelperNodeIndexes);
  HandleMessages* BSNodeObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedEmptyNodeIndex, m_selectedHelperNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_ueNodes, m_remoteHost, m_internetIpIfaces, m_aliveLDPCStorageNodes, m_allHelperNodeIndexes, m_selectedEmptyNodeLogicalIndex,-1);
  //cout << "We are in StartApplication of BSApp after HandleMessages" << endl;
  BSNodeObject->SetReceiverSocket();
  //cout << "We are in StartApplication of BSApp after SetReceiverSocket" << endl;
  // BSNodeObject->SetSenderSocket(); // Ben kapattım
  //cout << "We are in StartApplication of BSApp after SetSenderSocket" << endl;
}


void BSApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  // if (m_socket)
  //   {
  //     m_socket->Close ();
  //   }
}

#endif 