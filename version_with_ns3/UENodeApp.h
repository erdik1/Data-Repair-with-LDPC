#ifndef UENodeApp_H
#define UENodeApp_H

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



class UENodeApp : public Application
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

    // Elif hocanın eklediği bölüm
    HandleMessages* helperNodeObject; 

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
    int m_selectedHelperNodeLogicalIndex;

    UENodeApp();
    virtual ~UENodeApp();
    TypeId GetTypeId ();
    //void Setup(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address receiverAddress, uint16_t servPort);
    void Setup(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string>  totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int selectedHelperNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex, int m_selectedHelperNodeLogicalIndex);
    void StartApplication ();
    void StopApplication ();

};

UENodeApp::UENodeApp()
{

}

UENodeApp::~UENodeApp ()
{
  m_socket = 0;
}

/* static */
TypeId UENodeApp::GetTypeId (void)
{
  // static TypeId tid = TypeId ("UENodeApp").SetParent<Application> ().SetGroupName ("Tutorial").AddConstructor<UENodeApp> ();
  static TypeId tid = TypeId ("UENodeApp").SetParent<Application> ().SetGroupName("Applications").AddConstructor<UENodeApp> ();
  return tid;
}

void UENodeApp::Setup(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string>  totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int selectedHelperNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex,int selectedHelperNodeLogicalIndex)
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
  m_selectedHelperNodeLogicalIndex = selectedHelperNodeLogicalIndex;
}

void UENodeApp::StartApplication (void)
{
  m_running = true;
  //m_packetsSent = 0;
  // m_socket->Bind ();
  // m_socket->Connect (m_peer);

  // m_servPort = servPort + this->GetNode()->GetId();

  //cout << "We are here in StartApplication of UENodeApp" << endl;
  cout<< "\n\nUENodeApp Node ID (this->GetNode()->GetId()): " << this->GetNode()->GetId()  <<" started in UENodeApp::StartApplication. m_servPort: "<<m_servPort <<endl;
  cout << " UENodeAppSender Node ID in UENodeApp: " << m_senderNode->GetId() << endl;
  cout << "UENodeApp Receiver Node ID in UENodeApp: " << m_receiverNode->GetId() << endl;

  // Elif hocanın eklediği bölüm
  cout << "UENodeApp (Receiver Node) Helper Node ID in UENodeApp::StartApplication: " << this->GetNode()->GetId() <<". m_receiverAddress: "<<m_receiverAddress<< endl;
  // cout << "(Receiver Node) Helper Node ID in UENodeApp::StartApplication: " << m_receiverNode->GetId() << endl;
  cout << "UENodeApp (Sender Node) NewComerNode ID in UENodeApp::StartApplication: " << m_senderNode->GetId() << endl;

  //m_senderAddress = m_ueIpIface.GetAddress (m_selectedEmptyNodeIndex);

  //Ptr<HandleMessages> helperNodeObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort);
  //Ptr<HandleMessages> helperNodeObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedEmptyNodeIndex, m_selectedHelperNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_ueNodes, m_remoteHost, m_internetIpIfaces, m_aliveLDPCStorageNodes, m_allHelperNodeIndexes);
  helperNodeObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedEmptyNodeIndex, m_selectedHelperNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_ueNodes, m_remoteHost, m_internetIpIfaces, m_aliveLDPCStorageNodes, m_allHelperNodeIndexes, m_selectedEmptyNodeLogicalIndex,m_selectedHelperNodeLogicalIndex);
  //cout << "We are here in StartApplication of UENodeApp after HandleMessages" << endl;
  helperNodeObject->SetReceiverSocket();

  // Elif hocanın kapattığı kısım
  // helperNodeObject->SetSenderSocket(); // Burasını sadece kendisi göndereceği zaman ayarlayacak
}

void UENodeApp::StopApplication (void)
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