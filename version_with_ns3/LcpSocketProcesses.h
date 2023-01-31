

#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/lte-module.h"
#include "ns3/tcp-westwood.h"


using namespace ns3;
using namespace std;


/**
 * Sample simulation script for LTE+EPC+TCP. It instantiates several eNodeBs,
 * attaches one UE per eNodeB starts a flow for each UE to and from a remote host.
 * It also starts another flow between each UE pair.
 */

NS_LOG_COMPONENT_DEFINE ("TCPSocketProcesses");


 class TCPSocketProcesses {

public:

       ns3::EventId m_sendEvent;
       uint32_t totalTxBytes = 2000;
       uint32_t currentTxBytes = 0;
       // Perform series of 1040 byte writes (this is a multiple of 26 since
       // we want to detect data splicing in the output stream)
       static const uint32_t writeSize = 1472;
       static const uint32_t MTU = 1472;
       uint32_t servPort;
       uint8_t data[writeSize];
       Ptr<Packet> packet; // to identify received packet
       Ptr<Node> senderNode;
       Ptr<Node> receiverNode;
       Ptr<ns3::Socket> senderSocket;
       Ptr<ns3::Socket> receiverSocket;
       Ipv4Address receiverAddress;
       virtual ~TCPSocketProcesses();
       TCPSocketProcesses ( Ptr<Node> senderNode, Ptr<Node> receiverNode,Ipv4Address receiverAddress, uint16_t servPort);
       TCPSocketProcesses ( );
       void SetReceiverSocket();
       void SetSenderSocket();
       virtual void ReceivePacket (Ptr<Socket> socket);
       virtual void StartFlow ();
       virtual void WriteUntilBufferFull (Ptr<Socket> localSocket, uint32_t txSpace);
       void conFail(Ptr<Socket> socket);
       void ConAccept(Ptr<Socket> socket,const ns3::Address& from);

};
TCPSocketProcesses::TCPSocketProcesses( )
      {
  
          
    
      }

TCPSocketProcesses::TCPSocketProcesses( Ptr<Node> senderNode, Ptr<Node> receiverNode,Ipv4Address receiverAddress, uint16_t servPort)
      {
  
          this->senderNode = senderNode;
          this->receiverNode = receiverNode;
          this->servPort = servPort;
          this->receiverAddress = receiverAddress;
          Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (1472));
          TypeId tcpTid;
          std::string tcpVariant = "TcpNewReno"; 
          tcpVariant = std::string ("ns3::") + tcpVariant;    
          NS_ABORT_MSG_UNLESS (TypeId::LookupByNameFailSafe (tcpVariant, &tcpTid), "TypeId " << tcpVariant << " not found");
          Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant)));
    
      }
TCPSocketProcesses::~TCPSocketProcesses() {

}

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
   
   //receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId ());
   //InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), servPort);
   //cout<<"Receiver node listen adress"<<receiverAddress<<" port"<<servPort<<endl;
   //receiverSocket->SetAcceptCallback (MakeNullCallback<bool, Ptr<Socket>, const Address &> (), MakeCallback(&TCPSocketProcesses::ConAccept,this));
   //receiverSocket->SetRecvCallback (MakeCallback (&TCPSocketProcesses::ReceivePacket, this));
   //receiverSocket->Bind ();
   //receiverSocket->Listen();

  std::string tcpVariant = "TcpNewReno";  
  tcpVariant = std::string ("ns3::") + tcpVariant;
  TypeId tid = TypeId::LookupByName (tcpVariant);  // Elif hocanın eklediği satır
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant)));
  receiverSocket = Socket::CreateSocket(receiverNode, TcpSocketFactory::GetTypeId ());
  // Benim eklediğim kısım
  //servPort = 5000 + receiverNode->GetId();
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), servPort);
  cout << "receiverSocket->GetNode()->GetId() in TCPSocketProcesses::SetReceiverSocket before ConAccept: " << receiverSocket->GetNode()->GetId() << endl;
  receiverSocket->SetAcceptCallback (MakeNullCallback<bool, Ptr<Socket>, const Address &> (), MakeCallback(&TCPSocketProcesses::ConAccept,this));
  receiverSocket->Bind (local);
  receiverSocket->Listen();

}

void TCPSocketProcesses::SetSenderSocket()
{
    //senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
     //senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect
    // cout<<"\nSenderNode connect to  receiverAdress"<<receiverAddress<<"port"<<servPort<<endl;
  std::string tcpVariant = "TcpNewReno";  
  tcpVariant = std::string ("ns3::") + tcpVariant; 
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant)));

  TypeId tid = TypeId::LookupByName (tcpVariant);
  senderSocket = Socket::CreateSocket (senderNode, TcpSocketFactory::GetTypeId ());
  //senderSocket->Bind();

  // Benim eklediğim kısım
  //Ptr<Ipv4> ipv4 = senderSocket->GetNode()->GetObject<Ipv4> ();
  //Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
  //senderAddress =iaddr.GetLocal ();
  //servPort = 5000 + senderNode->GetId();

  // Ipv4Address tempAddress = senderAddress;
  // senderAddress = receiverAddress;
  // receiverAddress = tempAddress;

  senderSocket->Connect (InetSocketAddress (receiverAddress, servPort));



}

 void TCPSocketProcesses::ReceivePacket (Ptr<Socket> socket){
     Ptr<Packet> packet;
     //uint32_t nodeIdr=socket->GetNode()->GetId();
     printf("Received packet by Node %d\n",socket->GetNode()->GetId());
     while ((packet = socket->Recv ()))
     {
        //uint8_t buf[1300];
        //packet->CopyData(buf , packet->GetSize());
        //std::cout<<"Data, "<<buf<< ", SimulatorTime, "<<Simulator::Now().GetSeconds()<<" NodeIDR "<<nodeIdr<<std::endl;
    }}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//begin implementation of starting flow

void TCPSocketProcesses::StartFlow ()
{
  NS_LOG_LOGIC ("rStarting flow at time " <<  Simulator::Now ().GetSeconds ());
  printf ("RRStarting flow at time %f \n",  Simulator::Now ().GetSeconds ());
  //senderSocket->Connect (InetSocketAddress (receiverAddress, servPort)); //connect

  // tell the tcp implementation to call WriteUntilBufferFull again
  // if we blocked and new tx buffer space becomes available
  senderSocket->SetSendCallback (MakeCallback (&TCPSocketProcesses::WriteUntilBufferFull,this));
  //WriteUntilBufferFull (senderSocket, senderSocket->GetTxAvailable ());
}

void TCPSocketProcesses::WriteUntilBufferFull (Ptr<Socket> senderSocket, uint32_t txSpace)
{
  while (currentTxBytes < totalTxBytes && senderSocket->GetTxAvailable () > 0) 
    {
      uint32_t left = totalTxBytes - currentTxBytes;
      uint32_t dataOffset = currentTxBytes % writeSize;
      uint32_t toWrite = writeSize - dataOffset;
      toWrite = std::min (toWrite, left);
      toWrite = std::min (toWrite, senderSocket->GetTxAvailable ());
      int amountSent = senderSocket->Send (&data[dataOffset], toWrite, 0);
      if(amountSent < 0)
        {
          // we will be called again when new tx space becomes available.
          cout<<"Not send"<<endl;
          return;
        }
      currentTxBytes += amountSent;
      printf ("Sent %d, localSocket->GetTxAvailable () : %d ",  currentTxBytes,senderSocket->GetTxAvailable ());
    }
   // receiverSocket->Close();

    //localSocket->Close ();
  if (currentTxBytes >= totalTxBytes)
    {
      //receiverSocket->Close();

      //localSocket->Close ();
      //if (m_sendEvent.IsRunning()) {
        //ns3::Simulator::Cancel(m_sendEvent);
    //}
    }
}
void TCPSocketProcesses::conFail(Ptr<Socket> socket)
{
  
  NS_LOG_UNCOND ("Reader: Error : Connection to the portal Failed ");
  std::cout<<"Reader: Error : Connection to the portal Failed "<< std::endl;
  exit(-1);
}
void TCPSocketProcesses::ConAccept(Ptr<Socket> socket,const ns3::Address& from)
{
            
    std::cout<<"Connection accepted by"<< "   " <<socket->GetRxAvailable() << "socket->GetRxAvailable()"<<socket->GetRxAvailable()<<std::endl;
    if (socket->GetRxAvailable()>0)
      ReceivePacket(socket);
    
    else
      socket->SetRecvCallback (MakeCallback(&TCPSocketProcesses::ReceivePacket,this));
    //std::cout<<"Received connection "<<from<< std::endl;
    //ns3::MakeCallback(&ReceivePacket, socket); 
   // NS_LOG_UNCOND ("Connection succeeded ");
    
}


