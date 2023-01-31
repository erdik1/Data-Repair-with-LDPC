#ifndef NewComerNodeApp_H
#define NewComerNodeApp_H

#include "userDefinedFunctions.h"
// #include "messages.h"
#include "HandleMessages.h"

using namespace ns3;
using namespace std;

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


class NewComerNodeApp : public Application
{
  public:
    Ptr<Socket> m_socket;
    // //Address m_peer (),
    // m_packetSize (0),
    // m_nPackets (0),
    // DataRate  m_dataRate (0),
    EventId m_sendEvent; // Eventid of pending "send packet" event
    bool m_running = false;
    // m_packetsSent (0), 

    Ptr<Node> m_senderNode;
    Ptr<Node> m_receiverNode;
    Ipv4Address m_senderAddress;
    Ipv4Address m_receiverAddress;
    uint16_t m_servPort;

    // Elif hocanın eklediği kısım
    HandleMessages** helperNodeObject;//Node devam ederken bu referanslara ihtiyaç var
    HandleMessages** handleReplies;

    int m_foundOne;
    std::string m_repairedFile;
    std::vector<std::string>  m_totalHelperFiles;
    int m_cols;
    std::vector<struct ns> m_nodeStr;
    Ipv4InterfaceContainer m_ueIpIface;
    //std::vector<int> m_currentHelperNodeIndexes;
    std::vector<std::string> m_inputFiles;
    //m_selectedHelperNodeIndex(),
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
   
    NewComerNodeApp();
    virtual ~NewComerNodeApp();
    TypeId GetTypeId();
    void Setup(int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex);
    void StartApplication();
    void StopApplication();

    // Elif hocanın eklediği kısım
    void conSuc(Ptr<Socket> socket);
    void conFail(Ptr<Socket> socket);
    void DataSend(ns3::Ptr<ns3::Socket>, uint32_t);
};

NewComerNodeApp::NewComerNodeApp()
{

}

NewComerNodeApp::~NewComerNodeApp ()
{
  m_socket = 0;
}

/* static */
TypeId NewComerNodeApp::GetTypeId (void)
{
  // static TypeId tid = TypeId ("NewComerNodeApp").SetParent<Application> ().SetGroupName ("Tutorial").AddConstructor<NewComerNodeApp> ();
  static TypeId tid = TypeId ("NewComerNodeApp").SetParent<Application> ().SetGroupName ("Applications").AddConstructor<NewComerNodeApp> ();
  return tid;
}

//void NewComerNodeApp::Setup (Ptr<Socket> socket, Address defaultAddress, uint32_t packetSize, uint32_t nPackets, DataRate dataRate, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<string> totalHelperFiles, int cols, std::vector<ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<int> currentHelperNodeIndexes, std::vector<std::string> inputFiles, int selectedHelperNodeIndex, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2)
void NewComerNodeApp::Setup(int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex )
{
  // m_socket = socket;
  // m_peer = defaultAddress;
  // m_packetSize = packetSize;
  // m_nPackets = nPackets;
  // m_dataRate = dataRate;

  // m_senderNode = senderNode;
  // m_receiverNode = receiverNode;
  // m_receiverAddress = receiverAddress;
  // m_servPort = servPort;

  m_foundOne = foundOne; 
  m_repairedFile = repairedFile; 
  m_totalHelperFiles = totalHelperFiles;
  m_cols = cols; 
  m_nodeStr = nodeStr;
  m_ueIpIface = ueIpIface;
  //m_currentHelperNodeIndexes = currentHelperNodeIndexes; 
  m_inputFiles = inputFiles;
  //m_selectedHelperNodeIndex = selectedHelperNodeIndex; 
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

// Elif hocanın eklediği fonksiyonlar
void NewComerNodeApp::DataSend(ns3::Ptr<ns3::Socket>, uint32_t)
{
    //if (m_connected) {          // Only send new data if the connection has completed
        //ns3::Simulator::ScheduleNow(&UnlimitedRateApp::SendData, this);
    //}
}
void NewComerNodeApp::conSuc(Ptr<Socket> socket)
{
  // StartSignalPacketwithParameters(REQUESTREPAIRFROMUE,socket ) ;      
  //Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
  //double delay = 0.0;//((double)(x->GetInteger ()%3));
 // Time tNext (Seconds (delay));
  //messageType = REQUESTREPAIRFROMUE; 
  //HandleMessages* handleObj = reinterpret_cast<HandleMessages*>(socket);
  //Simulator::Schedule(tNext, &NewComerNodeApp::StartSignalPacketwithParameters,this,REQUESTREPAIRFROMUE,socket);
  //std::cout<<"Connection succeeded by helper x"<<std::endl;
  //NS_LOG_UNCOND ("Node id %d Connection succeeded ",socket->GetNode()->GetId());
   /*  */
}
//Soket bağlantısının doğru olduğunu gösteren fonksiyon
void NewComerNodeApp::conFail(Ptr<Socket> socket)
{
  
  NS_LOG_UNCOND (" Error : Connection to the por Failed ");
  std::cout<<"Reader: Error : Connection to the por Failed "<< std::endl;
  exit(-1);
}

void NewComerNodeApp::StartApplication (void)
{
  //cout << "We are in StartApplication" << endl;
  m_running = true;
  // m_packetsSent = 0;
  // m_socket->Bind ();
  // m_socket->Connect (m_peer);

  [[maybe_unused]] enum MType messageType;
  uint16_t servPort = 5000;
  //Ptr<HandleMessages> helperNodeObject[m_helperNodes.size()];

  // Elif hocanın eklediği kısım
  helperNodeObject = (HandleMessages**)malloc(sizeof(HandleMessages*) * ((m_helperNodes.size()+1)));//new HandleMessages[m_helperNodes.size()];
  handleReplies = (HandleMessages**)malloc(sizeof(HandleMessages*) * m_helperNodes.size());//new HandleMessages[m_helperNodes.size()];
  // HandleMessages* helperNodeObject[m_helperNodes.size()];

  int m_selectedHelperNodeIndex;
  //std::vector<int> currentHelperNodeIndexes;
  //cout << "We are in StartApplication 1 in NewComerNodeApp" << endl;
  cout << "\nNode ID (this->GetNode()->GetId()): " << this->GetNode()->GetId() << " started in NewComerNodeApp::StartApplication. m_helperNodes.size()"<<m_helperNodes.size()<<endl;
  cout << endl;
  for (size_t h = 0; h < m_helperNodes.size(); h++)
  {
    m_selectedHelperNodeIndex = m_aliveLDPCStorageNodes[m_helperNodes[h]];

    // m_senderNode = m_ueNodes.Get(m_selectedEmptyNodeIndex);  // senderNode
    m_senderNode = m_ueNodes.Get(m_selectedEmptyNodeLogicalIndex);  // senderNode
    m_receiverNode = m_ueNodes.Get(h);  //  receiverNode

    // Elif hocanın eklediği kısım
    // Ptr<Ipv4> ipv4 = m_ueNodes.Get(m_selectedEmptyNodeIndex)->GetObject<Ipv4> ();//????
    // Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
    // // cout<<"NODE ID:"<<receiverNode->GetId()<<"with adress"<<iaddr.GetLocal ();
    // m_receiverAddress =iaddr.GetLocal ();
    // m_senderAddress = m_ueIpIface.GetAddress (m_selectedEmptyNodeIndex);
    // m_servPort = servPort + this->GetNode()->GetId();

    // Benim eklediğim kısım başlangıç
    //Ptr<Ipv4> ipv4 = m_ueNodes.Get(m_selectedHelperNodeIndex)->GetObject<Ipv4> ();//????
    Ptr<Ipv4> ipv4 = m_ueNodes.Get(h)->GetObject<Ipv4> ();
    Ipv4InterfaceAddress iaddr = ipv4->GetAddress (2,0); 
    m_receiverAddress =iaddr.GetLocal ();
    // m_senderAddress = m_ueIpIface.GetAddress (m_selectedEmptyNodeIndex);
    cout << "We are in NewComerNodeApp::StartApplication" << endl;
    cout << "m_selectedEmptyNodeLogicalIndex: " << m_selectedEmptyNodeLogicalIndex << endl;
    cout << "size of m_ueIpIface: " << m_ueIpIface.GetN() << endl;
    cout <<" NewComer node "<<this->GetNode()->GetId()<<"\n";
    cout<<"m_ueNodes.GetN(): "<<m_ueNodes.GetN()<<endl;
    cout<<"!! m_receiverAddress "<<m_receiverAddress << "m_receiverNode "<<m_receiverNode->GetId()<<"\n";
    Ptr<Ipv4> ipv4forSender = m_ueNodes.Get(m_selectedEmptyNodeLogicalIndex)->GetObject<Ipv4> ();
    Ipv4InterfaceAddress iaddrforSender = ipv4->GetAddress (2,0); 
    m_senderAddress =iaddrforSender.GetLocal ();
    // m_senderAddress = m_ueIpIface.GetAddress (m_selectedEmptyNodeLogicalIndex);

    // m_servPort = servPort + this->GetNode()->GetId();
    m_servPort = servPort + m_ueNodes.Get(h)->GetId()+m_ueNodes.Get(m_selectedEmptyNodeLogicalIndex)->GetId();
    // Benim eklediğim kısım son

    // m_senderAddress = m_ueIpIface.GetAddress (m_selectedEmptyNodeIndex);
    // m_receiverAddress = m_ueIpIface.GetAddress (m_selectedHelperNodeIndex);
    // m_servPort = servPort;
    // servPort = servPort + 1;

    //helperNodeObject[h] = new HandleMessages(m_senderNode, m_receiverNode, m_receiverAddress, m_servPort);
    helperNodeObject[h] = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedEmptyNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_ueNodes, m_remoteHost, m_internetIpIfaces, m_aliveLDPCStorageNodes, m_allHelperNodeIndexes, m_selectedEmptyNodeLogicalIndex,-1);

    // helperNodeObject[h]->SetReceiverSocket(); // Elif hocanın versiyonunda bu kısım kapalı

    // Elif hocanın eklediği kısım
    helperNodeObject[h]->SetReceiverSocketForGettingReply();
    helperNodeObject[h]->SetSenderSocket();
    //cout << "We are here 3 in StartApplication in NewComerNodeApp after SetSenderSocket" << endl;
    messageType = REQUESTREPAIRFROMUE; 
    //helperNodeObject[h]->StartSignalPacketwithParameters(messageType, m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedHelperNodeIndex, m_selectedEmptyNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_aliveLDPCStorageNodes, m_remoteHost, m_internetIpIfaces, m_allHelperNodeIndexes);
    //helperNodeObject[h]->StartSignalPacketwithParameters(messageType,helperNodeObject[h]->senderSocket);
    cout << "StartSignalPacketwithParameters of helperNodeObject[h] in NewComerNodeApp::StartApplication" << endl;
    cout << "h: " << h << endl;
    cout << "Sender Node ID (NewComerNode) in NewComerNodeApp::StartApplication: " << m_senderNode->GetId() << endl;
    cout << "Receiver Node ID in (HelperNode) NewComerNodeApp::StartApplication: " << m_receiverNode->GetId() << endl;
    
    // helperNodeObject[h]->StartSignalPacketwithParameters(messageType, m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort);
    // break;

    //Simulator::ScheduleNow (&NewComerNodeApp::StartApplication, newComerNodeApp);
    // Simulator::Schedule (Seconds(Simulator::Now().GetSeconds() + 10.0), helperNodeObject[h]->StartSignalPacketwithParameters, messageType, m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort);
    // Simulator::Schedule (Seconds (10.0), &ExampleFunction, &model);

    // Simulator::Schedule(Seconds(Simulator::Now().GetSeconds() + 10.0), &HandleMessages::StartSignalPacketwithParameters(messageType, m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort), helperNodeObject[h]);
    // Simulator::Schedule(Seconds(Simulator::Now().GetSeconds() + 10.0), &HandleMessages::StartSignalPacketwithParameters, messageType, m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, helperNodeObject[h]);
    // Simulator::Schedule(Seconds (10.0), &HandleMessages::StartSignalPacketwithParameters, helperNodeObject[h]);
  } 
  
  if(m_failedSymbolIDsForRepairFromBS.size() > 0)
  {
    messageType = REQUESTREPAIRFROMBS; 
    m_receiverNode = m_remoteHost;  //  receiverNode

    // Benim eklediğim kısım
    cout<<"Newcomer bs 1"<<"\n";
    Ptr<Ipv4> ipv4 = m_receiverNode->GetObject<Ipv4> ();//????
    Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
    m_receiverAddress =iaddr.GetLocal ();
    // m_receiverAddress = m_internetIpIfaces.GetAddress(0);
    m_servPort = servPort + m_remoteHost->GetId()+m_ueNodes.Get(m_selectedEmptyNodeLogicalIndex)->GetId();
    // m_senderNode = m_ueNodes.Get(m_selectedEmptyNodeIndex);  // senderNode
    // m_senderAddress = m_ueIpIface.GetAddress (m_selectedEmptyNodeIndex);
    cout<<"Newcomer bs 2"<<"\n";
    m_senderNode = m_ueNodes.Get(m_selectedEmptyNodeLogicalIndex);  // senderNode

    Ptr<Ipv4> ipv4forSender = m_ueNodes.Get(m_selectedEmptyNodeLogicalIndex)->GetObject<Ipv4> ();
    Ipv4InterfaceAddress iaddrforSender = ipv4->GetAddress (1,0); 
    m_senderAddress =iaddrforSender.GetLocal ();
    // m_senderAddress = m_ueIpIface.GetAddress (m_selectedEmptyNodeLogicalIndex);
    // Benim eklediğim kısım son
    cout<<"Newcomer bs 3"<<"\n";
    //Ptr<HandleMessages> BSObject = new HandleMessages(m_senderNode, m_receiverNode, m_receiverAddress, m_servPort);
    //Ptr<HandleMessages> BSObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedEmptyNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_ueNodes, m_remoteHost, m_internetIpIfaces, m_aliveLDPCStorageNodes, m_allHelperNodeIndexes);
    HandleMessages* BSObject = new HandleMessages(m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedEmptyNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_ueNodes, m_remoteHost, m_internetIpIfaces, m_aliveLDPCStorageNodes, m_allHelperNodeIndexes, m_selectedEmptyNodeLogicalIndex,-1);
    //BSObject->StartSignalPacketwithParameters(messageType, m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort, m_foundOne, m_repairedFile, m_totalHelperFiles, m_cols, m_nodeStr, m_ueIpIface, m_inputFiles, m_selectedHelperNodeIndex, m_selectedEmptyNodeIndex, m_quotient, m_tempUsedEmptyNodeforRepair, m_baseStation, m_failedSymbolIDsForRepairFromBS, m_maxColLength, m_R1, m_R2, m_L, m_helperNodes, m_numberofRoundforBuffer, m_currentLostLDPCChunkSymbols, m_strParameters, m_unrepairedSymbolsfromNodes, m_unrepairedSymbolsfromBS, m_allEquationsR2, m_aliveLDPCStorageNodes, m_remoteHost, m_internetIpIfaces, m_allHelperNodeIndexes);
    //cout << "We are in StartApplication 3 in NewComerNodeApp after HandleMessages" << endl;
    cout << "----------------------------------------------------------------------------------------------------\n";
    cout << "\n\n\n***BS NewComerNodeApp StartSignalPacketwithParameters of BSObject in NewComerNodeApp" << endl;
    cout << "***BS NewComerNodeApp Sender Node ID (NewComerNode) in NewComerNodeApp::StartApplication: " << m_senderNode->GetId() << endl;
    cout << "***BS NewComerNodeApp Receiver Node ID (BS) in NewComerNodeApp::StartApplication: " << m_receiverNode->GetId() << endl<<"\n\n\n";
    
    // Benim eklediğim kısım 12.01.2022
    BSObject->SetReceiverSocketForGettingReply(); 
    BSObject->SetSenderSocket();
  
    // BSObject->StartSignalPacketwithParameters(messageType, m_senderNode, m_receiverNode, m_senderAddress, m_receiverAddress, m_servPort);
    //cout << "We are in StartApplication 4 in NewComerNodeApp after StartSignalPacketwithParameters" << endl;
  }
  else
    cout << "There is no need for BS." << endl;

  //cout << endl;
}

void NewComerNodeApp::StopApplication (void)
{
  cout << "StopApplication in NewComerNodeApp" << endl;
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