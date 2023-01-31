#include "userDefinedFunctions.h"

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/eps-bearer-tag.h"

using namespace ns3;

MyApp::MyApp ()
  : m_socket (0),
    m_peer (),
   // m_packetSize (0),
   // m_nPackets (0),
    m_dataRate (0),
    m_sendEvent (),
    m_running (false),
    //m_packetsSent (0),
    m_gNbNodes(),
    m_gNbNetDev(),
    m_internet()
{
}

MyApp::~MyApp ()
{
  m_socket = 0;
}

/* static */
TypeId MyApp::GetTypeId (void)
{
  static TypeId tid = TypeId ("MyApp")
    .SetParent<Application> ()
    .SetGroupName ("Tutorial")
    .AddConstructor<MyApp> ()
    ;
  return tid;
}

//void MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, MobilityHelper mobility, InternetStackHelper internet)
//void MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, InternetStackHelper internet)
// void MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
// {
//   m_socket = socket;
//   m_peer = address;
//   m_packetSize = packetSize;
//   m_nPackets = nPackets;
//   m_dataRate = dataRate;
//   // m_gNbNodes = gNbNodes;
//   // m_ueNodes = ueNodes;
//   // m_gNbNetDev = gNbNetDev; 
//   // m_ueNetDev = ueNetDev;
//   // //m_mobility = mobility;
//   // m_internet = internet;
// }

void MyApp::Setup ()
{
}

void MyApp::StartApplication (void)
{
  //createTopology();
  runLDPCSims(); 
}

void MyApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}