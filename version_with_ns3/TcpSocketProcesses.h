#ifndef TCPSocketProcesses_H
#define TCPSocketProcesses_H

//#include <string>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/lte-module.h"

#include "userDefinedFunctions.h"
#include "messages.h"

using namespace ns3;
using namespace std;

// Elif hocanın eklediği kısım
class HandleMessages;
static int finishStateCounter;

NS_LOG_COMPONENT_DEFINE ("TCPSocketProcesses");


class TCPSocketProcesses //: public SimpleRefCount<OutputStreamWrapper>
{
  public:
        uint32_t totalTxBytes = 2000000;
        uint32_t currentTxBytes = 0;
        // Perform series of 1040 byte writes (this is a multiple of 26 since
        // we want to detect data splicing in the output stream)
        static const uint32_t writeSize = 536;
        uint32_t MTU = 536;
        // static const uint32_t writeSize = 1000; //The MTU defaults to 1500 bytes in the CsmaNetDevice.
        // uint32_t MTU = 1000;
        uint16_t servPort;
        uint8_t data[writeSize];
        Ptr<Packet> packet; // to identify received packet

        Ptr<Node> senderNode;
        Ptr<Node> receiverNode;
        Ptr<ns3::Socket> senderSocket;
        Ptr<ns3::Socket> receiverSocket;
        Ipv4Address senderAddress;
        Ipv4Address receiverAddress;

        // Elif hocanın eklediği kısım
        Ptr<ns3::Socket> newComerRelpySocket;
        Ptr<ns3::Socket> helperReplySocket;

        
        int foundOne;
        std::string repairedFile;
        std::vector<std::string>  totalHelperFiles;
        int cols;
        std::vector<struct ns> nodeStr;
        Ipv4InterfaceContainer ueIpIface;
        std::vector<std::string> inputFiles;
        int selectedEmptyNodeIndex;
        int selectedLogicalHelperNodeIndex;
        int quotient;
        std::string tempUsedEmptyNodeforRepair;
        std::string baseStation;
        std::vector<int> failedSymbolIDsForRepairFromBS;
        int maxColLength;
        std::vector<std::vector<int>> R1;
        std::vector<std::vector<int>> R2;
        std::vector<int> L;
        std::vector<int> helperNodes;
        int numberofRoundforBuffer;
        std::vector<int> currentLostLDPCChunkSymbols;
        struct strP strParameters;
        std::vector<int> unrepairedSymbolsfromNodes;
        std::vector<int> unrepairedSymbolsfromBS;
        std::vector<std::vector<int>> allEquationsR2;
        NodeContainer ueNodes;
        Ptr<Node> remoteHost;
        Ipv4InterfaceContainer internetIpIfaces;
        std::vector<int> aliveLDPCStorageNodes;
        std::vector<int> allHelperNodeIndexes;

        int selectedHelperNodeIndex;
        int selectedEmptyNodeLogicalIndex;

         virtual ~TCPSocketProcesses();
         TCPSocketProcesses(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string>  totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex, int selectedLogicalHelperNodeIndex);
         TCPSocketProcesses(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string>  totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int selectedHelperNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex, int selectedLogicalHelperNodeIndex);
         TCPSocketProcesses();
         void SetReceiverSocket();
         void SetSenderSocket();
         virtual void ReceivePacket (Ptr<Socket> socket);
         // virtual void StartFlow ();
         // virtual void WriteUntilBufferFull (Ptr<Socket> localSocket, uint32_t txSpace);
         void conFail(Ptr<Socket> socket);
         void ConAccept(Ptr<Socket> socket,const ns3::Address& from);
         //void StartSignalPacketwithParameters(enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<int> currentHelperNodeIndexes, std::vector<std::string> inputFiles, int selectedHelperNodeIndex, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, std::vector<int> aliveLDPCStorageNodes, Ipv4InterfaceContainer internetIpIfaces);
         //void SendSignalPacketwithParameters(Ptr<Socket> senderSocket, enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<int> currentHelperNodeIndexes, std::vector<std::string> inputFiles, int selectedHelperNodeIndex, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, std::vector<int> aliveLDPCStorageNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces);

         // Elif hocanın eklediği fonksiyonlar
         void SetSenderSocketForReply();
         void SetReceiverSocketForGettingReply();
         void conSuc(Ptr<Socket> socket);
         void conSucHelper(Ptr<Socket> socket);
         virtual  void StartSignalPacketwithParameters(enum MType MESSAGETYPE,Ptr<Socket> socket);
         virtual void WriteUntilBufferFullFromHelperNodes(Ptr<Socket> socket, uint32_t txSpace);
         virtual void WriteUntilBufferFullFromBS(Ptr<Socket> socket, uint32_t txSpace);
};

TCPSocketProcesses::TCPSocketProcesses()
{

}

TCPSocketProcesses::TCPSocketProcesses(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string>  totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex,int selectedLogicalHelperNodeIndex)
{
  this->senderNode = senderNode;
  this->receiverNode = receiverNode;
  this->senderAddress = senderAddress;
  this->receiverAddress = receiverAddress;
  this->servPort = servPort;

  this->foundOne = foundOne;
  this->repairedFile = repairedFile;
  this->totalHelperFiles = totalHelperFiles;
  this->cols = cols;
  this->nodeStr = nodeStr;
  this->ueIpIface = ueIpIface;
  this->inputFiles = inputFiles;
  this->selectedEmptyNodeIndex = selectedEmptyNodeIndex;
  this->quotient = quotient;
  this->tempUsedEmptyNodeforRepair = tempUsedEmptyNodeforRepair;
  this->baseStation = baseStation;
  this->failedSymbolIDsForRepairFromBS = failedSymbolIDsForRepairFromBS;
  this->maxColLength = maxColLength;
  this->R1 = R1;
  this->R2 = R2;
  this->L = L;
  this->helperNodes = helperNodes;
  this->numberofRoundforBuffer = numberofRoundforBuffer;
  this->currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
  this->strParameters = strParameters;
  this->unrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
  this->unrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
  this->allEquationsR2 = allEquationsR2;
  this->ueNodes = ueNodes;
  this->remoteHost = remoteHost;
  this->internetIpIfaces = internetIpIfaces;
  this->aliveLDPCStorageNodes = aliveLDPCStorageNodes;
  this->allHelperNodeIndexes = allHelperNodeIndexes;
  this->selectedEmptyNodeLogicalIndex = selectedEmptyNodeLogicalIndex;
  this->selectedLogicalHelperNodeIndex=selectedLogicalHelperNodeIndex;
}

TCPSocketProcesses::TCPSocketProcesses(Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string>  totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedEmptyNodeIndex, int selectedHelperNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, NodeContainer ueNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> aliveLDPCStorageNodes, std::vector<int> allHelperNodeIndexes, int selectedEmptyNodeLogicalIndex,int selectedLogicalHelperNodeIndex)
{
  this->senderNode = senderNode;
  this->receiverNode = receiverNode;
  this->senderAddress = senderAddress;
  this->receiverAddress = receiverAddress;
  this->servPort = servPort;

  this->foundOne = foundOne;
  this->repairedFile = repairedFile;
  this->totalHelperFiles = totalHelperFiles;
  this->cols = cols;
  this->nodeStr = nodeStr;
  this->ueIpIface = ueIpIface;
  this->inputFiles = inputFiles;
  this->selectedEmptyNodeIndex = selectedEmptyNodeIndex;
  this->selectedHelperNodeIndex = selectedHelperNodeIndex;
  this->quotient = quotient;
  this->tempUsedEmptyNodeforRepair = tempUsedEmptyNodeforRepair;
  this->baseStation = baseStation;
  this->failedSymbolIDsForRepairFromBS = failedSymbolIDsForRepairFromBS;
  this->maxColLength = maxColLength;
  this->R1 = R1;
  this->R2 = R2;
  this->L = L;
  this->helperNodes = helperNodes;
  this->numberofRoundforBuffer = numberofRoundforBuffer;
  this->currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
  this->strParameters = strParameters;
  this->unrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
  this->unrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
  this->allEquationsR2 = allEquationsR2;
  this->ueNodes = ueNodes;
  this->remoteHost = remoteHost;
  this->internetIpIfaces = internetIpIfaces;
  this->aliveLDPCStorageNodes = aliveLDPCStorageNodes;
  this->allHelperNodeIndexes = allHelperNodeIndexes;
  this->selectedEmptyNodeLogicalIndex = selectedEmptyNodeLogicalIndex;
  this->selectedLogicalHelperNodeIndex =selectedLogicalHelperNodeIndex;
}

TCPSocketProcesses::~TCPSocketProcesses() 
{

}

void TCPSocketProcesses::SetReceiverSocketForGettingReply()
{

  std::string tcpVariant = "TcpNewReno";  
  tcpVariant = std::string ("ns3::") + tcpVariant;
   // Elif hocanın eklediği satır
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant))); 
  newComerRelpySocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
  
  // Benim eklediğim kısım
  //servPort = 5000 + senderNode->GetId();
  //newComerRelpySocket->Connect (InetSocketAddress (senderAdress, servPort));
   InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), servPort+1000);
  //InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), servPort);

  newComerRelpySocket->SetAcceptCallback (MakeNullCallback<bool, Ptr<Socket>, const Address &> (), MakeCallback(&TCPSocketProcesses::ConAccept,this));
  cout << "In TCPSocketProcesses::SetReceiverSocketForGettingReply, ConAccept is called." << endl;
  newComerRelpySocket->Bind (local);
  newComerRelpySocket->Listen();

  Ptr<Ipv4> ipv4 = senderNode->GetObject<Ipv4> ();
  Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 

  // cout<<"In TCPSocketProcesses::SetReceiverSocketForGettingReply, Hello  NODE ID (sender node): "<<senderNode->GetId()<<" with adress "<<iaddr.GetLocal ()<<" started listenning port "<<servPort+1000<<"\n";
  cout<<"In TCPSocketProcesses::SetReceiverSocketForGettingReply, Hello  NODE ID (old sender node = new receiver node): "<<senderNode->GetId()<<" with adress "<<iaddr.GetLocal ()<<" started listenning port "<<servPort+1000<<"\n";  
    
     //InetSocketAddress local = InetSocketAddress (receiverAddress, servPort);
     //senderSocket->SetAcceptCallback (MakeNullCallback<bool, Ptr<Socket>, const Address &> (), MakeCallback(&TCPSocketProcesses::ConAccept,this));
     //senderSocket->Bind (local);
     //senderSocket->Listen();
     //cout<<"Newcomer Node:"<<senderNode->GetId()<< " started to listen packets from"<<receiverAddress<<" with port"<<servPort<<"\n" ;
}

void TCPSocketProcesses::SetSenderSocketForReply()
{
      std::string tcpVariant = "TcpNewReno";  
      tcpVariant = std::string ("ns3::") + tcpVariant;
    // Elif hocanın eklediği satır
    Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant)));
     helperReplySocket = Socket::CreateSocket (receiverNode, TcpSocketFactory::GetTypeId ());

     // Benim eklediğim kısım
     //servPort = 5000 + receiverNode->GetId();
    helperReplySocket->Connect (InetSocketAddress (senderAddress, servPort+1000));
    

     // helperReplySocket->Connect (InetSocketAddress (senderAddress, servPort));
    // helperReplySocket->Connect (InetSocketAddress (senderAddress, servPort+1000));
     cout << "NODE ID"<<receiverNode->GetId()<<" In TCPSocketProcesses::SetSenderSocketForReply, conSucHelper is called." << endl;
    helperReplySocket->SetConnectCallback (MakeCallback (&TCPSocketProcesses::conSucHelper,this),MakeCallback(&TCPSocketProcesses::conFail,this));
   //StartSignalPacketwithParameters(DUMMY, helperReplySocket);
}

void TCPSocketProcesses::StartSignalPacketwithParameters(enum MType MESSAGETYPE,Ptr<Socket> socket)
{

} 

void TCPSocketProcesses::WriteUntilBufferFullFromBS(Ptr<Socket> socket, uint32_t txSpace)
{

}

void TCPSocketProcesses::WriteUntilBufferFullFromHelperNodes(Ptr<Socket> socket, uint32_t txSpace)
{

}
// Elif hocanın eklediği kısım bitiş

// These are for starting the writing process, and handling the sending 
// socket's notification upcalls (events).  These two together more or less
// implement a sending "Application", although not a proper ns3::Application
// subclass.

//void StartFlow (Ptr<Socket>, Ipv4Address, uint16_t);
//void WriteUntilBufferFull (Ptr<Socket>, uint32_t);
//void ReceivePacket (Ptr<Socket> socket);
//void conFail(Ptr<Socket> socket);
//void conSuc(Ptr<Socket> socket);
//void ConAccept(Ptr<Socket> socket,const ns3::Address& from);

void TCPSocketProcesses::SetReceiverSocket()
{   
  std::string tcpVariant = "TcpNewReno";  
  tcpVariant = std::string ("ns3::") + tcpVariant;
  //TypeId tid = TypeId::LookupByName (tcpVariant);  // Elif hocanın eklediği satır
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant)));
  TypeId tid = TypeId::LookupByName ("ns3::TcpSocketFactory");  // Elif hocanın eklediği satır
  receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId ());
  // Benim eklediğim kısım
  //servPort = 5000 + receiverNode->GetId();
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), servPort);
  cout << "receiverSocket->GetNode()->GetId() in TCPSocketProcesses::SetReceiverSocket before ConAccept: " << receiverSocket->GetNode()->GetId() << endl;
  receiverSocket->SetAcceptCallback (MakeNullCallback<bool, Ptr<Socket>, const Address &> (), MakeCallback(&TCPSocketProcesses::ConAccept,this));
  receiverSocket->Bind (local);
  receiverSocket->Listen();

  // Elif hocanın eklediği bölüm
  Ptr<Ipv4> ipv4 = receiverSocket->GetNode()->GetObject<Ipv4> ();
  Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
  // Benim eklediğim kısım
  cout<<"!! receiverAddress"<<receiverAddress<<endl;
  receiverAddress =iaddr.GetLocal ();
  
  cout<<"In TCPSocketProcesses::SetReceiverSocket, NODE ID (receiver node): "<<receiverNode->GetId()<<" with adress "<<iaddr.GetLocal ()<<" started listenning port "<<servPort<<"\n";
  cout << "In TCPSocketProcesses::SetReceiverSocket, receiverSocket: " << receiverSocket << endl;
  cout << "In TCPSocketProcesses::SetReceiverSocket, receiverSocket->GetNode()->GetId(): " << receiverSocket->GetNode()->GetId() << endl;
  // cout << "senderSocket: " << senderSocket << endl;
  // cout << "senderSocket->GetNode()->GetId(): " << senderSocket->GetNode()->GetId() << endl;
}

void TCPSocketProcesses::SetSenderSocket()
{

   std::string tcpVariant = "TcpNewReno";  
  tcpVariant = std::string ("ns3::") + tcpVariant;
 // Elif hocanın eklediği satır
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant)));
  // Elif hocanın eklediği kısım
  TypeId tid = TypeId::LookupByName ("ns3::TcpSocketFactory");
  senderSocket = Socket::CreateSocket (senderNode, tid);
  //senderSocket->Bind();
  cout <<"Here SetSenderSocket 0" <<endl;
  // Benim eklediğim kısım
  Ptr<Ipv4> ipv4 = senderSocket->GetNode()->GetObject<Ipv4> ();
  cout <<"Here SetSenderSocket 1" <<endl;
  Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
  senderAddress =iaddr.GetLocal ();
  cout <<"Here SetSenderSocket 2 receiverAddress"<<receiverAddress <<endl;
  //servPort = 5000 + senderNode->GetId();
  cout <<"servPort"<<servPort<<"senderSocket"<<senderSocket<<endl;
  // Ipv4Address tempAddress = senderAddress;
  // senderAddress = receiverAddress;
  // receiverAddress = tempAddress;

  
  cout <<"Here SetSenderSocket 3" <<endl;
  
  //senderSocket->Connect (InetSocketAddress (senderAddress, servPort));
  cout << "In TCPSocketProcesses::SetSenderSocket, senderAddress: " << senderAddress << endl;
  cout << "In TCPSocketProcesses::SetSenderSocket, senderSocket->GetNode()->GetId(): " << senderSocket->GetNode()->GetId() << endl;
  cout << "In TCPSocketProcesses::SetSenderSocket, senderNode->GetId(): " << senderNode->GetId() << endl;
  cout << "In TCPSocketProcesses::SetSenderSocket, receiverAddress: " << receiverAddress << endl;
  cout << "In TCPSocketProcesses::SetSenderSocket, receiverNode " << receiverNode->GetId() << endl;
  // cout << "In TCPSocketProcesses::SetSenderSocket, receiverNode->GetId(): " << receiverNode->GetId() << endl;
  cout << "In TCPSocketProcesses::SetSenderSocket, servPort: " << servPort << endl;
  senderSocket->Connect (InetSocketAddress (receiverAddress, servPort));
  senderSocket->SetConnectCallback (MakeCallback (&TCPSocketProcesses::conSuc,this),MakeCallback(&TCPSocketProcesses::conFail,this));
  cout << "In TCPSocketProcesses::SetSenderSocket, conSuc is called.with receiverAddress"<<receiverAddress<<" with servPort"<<servPort << endl;
// senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ()); // kapatılan kısım
  // senderSocket->SetSendCallback (MakeCallback (&TCPSocketProcesses::conSuc,this));
  // senderSocket->SetSendCallback (MakeCallback (&TCPSocketProcesses::conSuc,this));
  // StartSignalPacketwithParameters(DUMMY, senderSocket);
}

void TCPSocketProcesses::ReceivePacket (Ptr<Socket> socket)
{
  Ptr<Packet> packet;
  //uint32_t nodeIdr=socket->GetNode()->GetId();
  printf("In TCPSocketProcesses::ReceivePacket, packet is received by Node %d\n",socket->GetNode()->GetId());
  while((packet = socket->Recv ()))
  {
    //uint8_t buf[1300];
    //packet->CopyData(buf , packet->GetSize());
    // std::cout<<"Data, "<<buf<< ", SimulatorTime, "<<Simulator::Now().GetSeconds()<<" NodeIDR "<<nodeIdr<<std::endl;
    std::cout<<"TCPSocketProcesses::ReceivePacket, Data"<< ", SimulatorTime, "<<Simulator::Now().GetSeconds()<<" NodeIDR "<<"\n"; // Elif hocanın eklediği bölüm
  }
}

void TCPSocketProcesses::conFail(Ptr<Socket> socket)
{  
  NS_LOG_UNCOND("In TCPSocketProcesses::conFail, Reader: Error : Connection to the portal Failed ");
  std::cout << "In TCPSocketProcesses::conFail, Reader: Error : Connection to the portal Failed " << std::endl;
  exit(-1);
}

void TCPSocketProcesses::ConAccept(Ptr<Socket> socket, const ns3::Address& from)
{  
  // Elif hocanın eklediği bölüm
  std::cout<<"In TCPSocketProcesses::ConAccept, Connection accepted by"<< "   " <<socket->GetNode()->GetId() <<"\n" <<std::endl;

  // std::cout << "Connection accepted by" << " " << socket->GetRxAvailable() << std::endl;
  cout << "In TCPSocketProcesses::ConAccept, socket->GetRxAvailable(): " << socket->GetRxAvailable() << endl;
  if(socket->GetRxAvailable() > 0)
    ReceivePacket(socket);
  else
    socket->SetRecvCallback(MakeCallback(&TCPSocketProcesses::ReceivePacket,this));
  std::cout<<"In TCPSocketProcesses::ConAccept, Received connection "<<from<< std::endl;
  //ns3::MakeCallback(&ReceivePacket, socket); 
  // NS_LOG_UNCOND ("Connection succeeded ");
}

// Elif hocanın eklediği kısım başlangıç
void TCPSocketProcesses::conSucHelper(Ptr<Socket> socket)
{
    //StartSignalPacketwithParameters(REQUESTREPAIRFROMUE,socket ) ;      
  //Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
 // double delay = 0.0;//((double)(x->GetInteger ()%3));
  //Time tNext (Seconds (delay));
  //messageType = REQUESTREPAIRFROMUE; 
  //HandleMessages* handleObj = reinterpret_cast<HandleMessages*>(socket);
  //Simulator::Schedule(tNext, &NewComerNodeApp::StartSignalPacketwithParameters,this,REQUESTREPAIRFROMUE,socket);
  std::cout<<"CONSUCHELPER In TCPSocketProcesses::conSucHelper, Connection succeeded received by helper 2"<<std::endl;
  //StartSignalPacketwithParameters(DUMMY, socket);//(enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort);
  if(receiverNode != remoteHost)
  {
    WriteUntilBufferFullFromHelperNodes(socket, 0);
  }
  else
  {
    cout<<"BS WriteUntilBufferFullFromBS is started"<<endl;
    WriteUntilBufferFullFromBS(socket, 0);
  }
  //NS_LOG_UNCOND ("Node id %d Connection succeeded ",socket->GetNode()->GetId());
    
}
void TCPSocketProcesses::conSuc(Ptr<Socket> socket)
{
    //StartSignalPacketwithParameters(REQUESTREPAIRFROMUE,socket ) ;      
  //Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
 // double delay = 0.0;//((double)(x->GetInteger ()%3));
  //Time tNext (Seconds (delay));
  //messageType = REQUESTREPAIRFROMUE; 
  //HandleMessages* handleObj = reinterpret_cast<HandleMessages*>(socket);
  //Simulator::Schedule(tNext, &NewComerNodeApp::StartSignalPacketwithParameters,this,REQUESTREPAIRFROMUE,socket);
  std::cout<<"In TCPSocketProcesses::conSuc, Connection succeeded received newcomer 1 by "<<receiverNode->GetId()<<std::endl;
  if (receiverNode != remoteHost)
    StartSignalPacketwithParameters(REQUESTREPAIRFROMUE, socket);//(enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort);
  else
  {
    StartSignalPacketwithParameters(REQUESTREPAIRFROMBS, socket);
  }    
}
//Soket bağlantısının doğru olduğunu gösteren fonksiyon

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// void TCPSocketProcesses::StartSignalPacketwithParameters(enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<int> currentHelperNodeIndexes, std::vector<std::string> inputFiles, int selectedHelperNodeIndex, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, std::vector<int> aliveLDPCStorageNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> allHelperNodeIndexes)
// {
//   NS_LOG_LOGIC ("Starting flow at time " <<  Simulator::Now ().GetSeconds ());
//   printf ("Starting flow at time %f \n",  Simulator::Now ().GetSeconds ());
//   senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

//   // tell the tcp implementation to call WriteUntilBufferFull again
//   // if we blocked and new tx buffer space becomes available
//   senderSocket->SetSendCallback (MakeCallback (&TCPSocketProcesses::SendSignalPacketwithParameters,this));
//   SendSignalPacketwithParameters(senderSocket, MESSAGETYPE, senderNode, receiverNode, senderAddress, receiverAddress, servPort, foundOne, repairedFile, totalHelperFiles, cols, nodeStr, ueIpIface, inputFiles, selectedHelperNodeIndex, selectedEmptyNodeIndex, quotient, tempUsedEmptyNodeforRepair, baseStation, failedSymbolIDsForRepairFromBS, maxColLength, R1, R2, L, helperNodes, numberofRoundforBuffer, currentLostLDPCChunkSymbols, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, aliveLDPCStorageNodes, remoteHost, internetIpIfaces, allHelperNodeIndexes);
// }


// void TCPSocketProcesses::SendSignalPacketwithParameters(Ptr<Socket> senderSocket, enum MType MESSAGETYPE, Ptr<Node> senderNode, Ptr<Node> receiverNode, Ipv4Address senderAddress, Ipv4Address receiverAddress, uint16_t servPort, int foundOne, std::string repairedFile, std::vector<std::string> totalHelperFiles, int cols, std::vector<struct ns> nodeStr, Ipv4InterfaceContainer ueIpIface, std::vector<std::string> inputFiles, int selectedHelperNodeIndex, int selectedEmptyNodeIndex, int quotient, std::string tempUsedEmptyNodeforRepair, std::string baseStation, std::vector<int> failedSymbolIDsForRepairFromBS, int maxColLength, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, std::vector<int> L, std::vector<int> helperNodes, int numberofRoundforBuffer, std::vector<int> currentLostLDPCChunkSymbols, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, std::vector<int> aliveLDPCStorageNodes, Ptr<Node> remoteHost, Ipv4InterfaceContainer internetIpIfaces, std::vector<int> allHelperNodeIndexes)
// {
//   struct fileParameters fP;
  
//   fP.MESSAGETYPE = MESSAGETYPE;
//   fP.senderNode = senderNode; 
//   fP.receiverNode = receiverNode;
//   fP.senderAddress = senderAddress;
//   fP.receiverAddress = receiverAddress;
//   fP.servPort = servPort;
//   fP.ueIpIface = ueIpIface; 
//   fP.allHelperNodeIndexes = allHelperNodeIndexes; 
//   fP.inputFiles = inputFiles;
//   fP.selectedHelperNodeIndex = selectedHelperNodeIndex;
//   fP.selectedEmptyNodeIndex = selectedEmptyNodeIndex;
//   fP.quotient = quotient;
//   //fP.tempUsedEmptyNodeforRepair = quotient; 
//   fP.baseStation = baseStation;
//   fP.failedSymbolIDsForRepairFromBS = failedSymbolIDsForRepairFromBS; 
//   fP.maxColLength = maxColLength;

//   fP.R1 = R1;
//   fP.R2 = R2;
//   fP.L = L;
//   fP.helperNodes = helperNodes;
//   fP.tempUsedEmptyNodeforRepair = tempUsedEmptyNodeforRepair;
//   fP.numberofRoundforBuffer = numberofRoundforBuffer;
//   fP.currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
//   fP.strParameters = strParameters;
//   fP.unrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
//   fP.unrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
//   fP.allEquationsR2 = allEquationsR2;

//   fP.foundOne = foundOne;
//   fP.repairedFile = repairedFile;
//   fP.totalHelperFiles = totalHelperFiles;
//   fP.cols = cols;
//   fP.nodeStr = nodeStr;
//   fP.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
//   fP.remoteHost = remoteHost;
//   fP.internetIpIfaces = internetIpIfaces;

//   uint8_t *bufferStruct = (uint8_t *)(malloc(fP));
//   memcpy(bufferStruct, &fP, sizeof(fP));
//   Ptr <Packet> pkt1 = Create<Packet>(bufferStruct, sizeof(fP));
//   [[maybe_unused]] int res = senderSocket->Send(pkt1);

// }

#endif 