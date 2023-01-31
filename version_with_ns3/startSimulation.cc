#include "userDefinedFunctions.h"

/*using namespace std;
using namespace ns3;*/

#include "ns3/core-module.h"
#include "ns3/config-store.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/nr-module.h"
#include "ns3/config-store-module.h"
#include "ns3/antenna-module.h"
#include "ns3/eps-bearer-tag.h"

int main (int argc, char *argv[])
{
  // NodeContainer starterNode;
  // starterNode.Create (1);

  // MobilityHelper mobility;
  // mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  // Ptr<ListPositionAllocator> bsPositionAlloc = CreateObject<ListPositionAllocator> ();
  // const double gNbHeight = 10;
  // mobility.Install (starterNode);
  // bsPositionAlloc->Add (Vector (0.0, 0.0, gNbHeight));
  // mobility.SetPositionAllocator (bsPositionAlloc);
  // mobility.Install (starterNode);

  // // // Install nr net devices
  // // NetDeviceContainer gNbNetDev = nrHelper->InstallGnbDevice (starterNode, allBwps);
  // // int64_t randomStream = 1;
  // // randomStream += nrHelper->AssignStreams (gNbNetDev, randomStream);

  // // // When all the configuration is done, explicitly call UpdateConfig ()
  // // for (auto it = gNbNetDev.Begin (); it != gNbNetDev.End (); ++it)
  // // {
  // //   DynamicCast<NrGnbNetDevice> (*it)->UpdateConfig ();
  // // }

  // // Ptr<Socket> ns3TcpSocket = Socket::CreateSocket(starterNode.Get(0), TcpSocketFactory::GetTypeId ());
  // // Address sinkAddress = starterNode.Get(0)->GetAddress();
  // Ptr<MyApp> app = CreateObject<MyApp> ();
  // //app->Setup (ns3TcpSocket, sinkAddress, 8, 1000, DataRate ("1Mbps"), gNbNodes, ueNodes, gNbNetDev, ueNetDev, mobility, internet);
  // //app->Setup (ns3TcpSocket, sinkAddress, 8, 1000, DataRate ("1Mbps"));
  // app->Setup ();
  // starterNode.Get(0)->AddApplication(app);
  // app->SetStartTime (Seconds (1.));
  // app->SetStopTime (Seconds (20.));

  // Simulator::Stop(Seconds (20.));
  // Simulator::Run();
  // Simulator::Destroy ();

  //runLDPCSims(ns3TcpSocket, sinkAddress, enbNodes, ueNodes, gNbNetDev, ueNetDev, internet, ipInterfs);
  //extern void runLDPCSims();

  runLDPCSims();
  return 0;
}