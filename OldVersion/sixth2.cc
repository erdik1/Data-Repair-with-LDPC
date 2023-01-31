/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// #include "ns3/core-module.h"
// #include "ns3/network-module.h"
// #include "ns3/mobility-module.h"
// #include "ns3/config-store.h"
// #include "ns3/nr-helper.h"
// #include <ns3/buildings-helper.h>
// #include "ns3/log.h"
// #include "ns3/nr-point-to-point-epc-helper.h"
// #include "ns3/network-module.h"
// #include "ns3/ipv4-global-routing-helper.h"
// #include "ns3/internet-module.h"
// #include "ns3/applications-module.h"
// #include "ns3/point-to-point-helper.h"
// #include "ns3/nr-mac-scheduler-tdma-rr.h"
// #include "ns3/nr-module.h"
// #include <ns3/antenna-module.h>

// using namespace ns3;

#include "userDefinedFunctions.h"

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SixthScriptExample");

// ===========================================================================
//
//         node 0                 node 1
//   +----------------+    +----------------+
//   |    ns-3 TCP    |    |    ns-3 TCP    |
//   +----------------+    +----------------+
//   |    10.1.1.1    |    |    10.1.1.2    |
//   +----------------+    +----------------+
//   | point-to-point |    | point-to-point |
//   +----------------+    +----------------+
//           |                     |
//           +---------------------+
//                5 Mbps, 2 ms
//
//
// We want to look at changes in the ns-3 TCP congestion window.  We need
// to crank up a flow and hook the CongestionWindow attribute on the socket
// of the sender.  Normally one would use an on-off application to generate a
// flow, but this has a couple of problems.  First, the socket of the on-off
// application is not created until Application Start time, so we wouldn't be
// able to hook the socket (now) at configuration time.  Second, even if we
// could arrange a call after start time, the socket is not public so we
// couldn't get at it.
//
// So, we can cook up a simple version of the on-off application that does what
// we want.  On the plus side we don't need all of the complexity of the on-off
// application.  On the minus side, we don't have a helper, so we have to get
// a little more involved in the details, but this is trivial.
//
// So first, we create a socket and do the trace connect on it; then we pass
// this socket into the constructor of our simple application which we then
// install in the source node.
// ===========================================================================
//

static void CwndChange (Ptr<OutputStreamWrapper> stream, uint32_t oldCwnd, uint32_t newCwnd)
{
  NS_LOG_UNCOND (Simulator::Now ().GetSeconds () << "\t" << newCwnd);
  *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << oldCwnd << "\t" << newCwnd << std::endl;
}

static void RxDrop (Ptr<PcapFileWrapper> file, Ptr<const Packet> p)
{
  NS_LOG_UNCOND ("RxDrop at " << Simulator::Now ().GetSeconds ());
  file->Write (Simulator::Now (), p);
}

int main (int argc, char *argv[])
{
  CommandLine cmd (__FILE__);
  cmd.Parse (argc, argv);
  [[maybe_unused]] int numberofInitialStorageNodes = 30;

  // NodeContainer enbNodes;
  // NodeContainer ueNodes;
  // enbNodes.Create (2);
  // ueNodes.Create (2);

  NodeContainer nodes;
  // nodes.Create (numberofInitialStorageNodes);
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install(nodes);

  Ptr<RateErrorModel> em = CreateObject<RateErrorModel> ();
  em->SetAttribute ("ErrorRate", DoubleValue (0.00001));

  // for (int i = 0; i < numberofInitialStorageNodes; i++)
  //   devices.Get (i)->SetAttribute ("ReceiveErrorModel", PointerValue (em));
  devices.Get (1)->SetAttribute ("ReceiveErrorModel", PointerValue (em));
 

  InternetStackHelper stack;
  stack.Install(nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.252");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  // Packet Sink Application receives and consumes traffic generated to an IP address and port. 
  uint16_t sinkPort = 8080;
  // for (int i = 0; i < numberofInitialStorageNodes; i++)
  // {
  //   Address sinkAddress (InetSocketAddress (interfaces.GetAddress (i), sinkPort));
  //   PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
  //   ApplicationContainer sinkApps = packetSinkHelper.Install (nodes.Get (i));
  //   sinkApps.Start (Seconds (0.));
  //   sinkApps.Stop (Seconds (20.));
  // }
  Address sinkAddress (InetSocketAddress (interfaces.GetAddress (1), sinkPort));
  PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
  ApplicationContainer sinkApps = packetSinkHelper.Install (nodes.Get (1));
  sinkApps.Start (Seconds (0.));
  sinkApps.Stop (Seconds (20.));


  Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (nodes.Get (0), TcpSocketFactory::GetTypeId ());

  Ptr<MyApp> app = CreateObject<MyApp> ();
  app->Setup (ns3TcpSocket, sinkAddress, 1040, 1000, DataRate ("1Mbps"));
  nodes.Get (0)->AddApplication (app);
  app->SetStartTime (Seconds (1.));
  app->SetStopTime (Seconds (20.));

  // uint32_t nNodes = nodes.GetN ();
  // for (uint32_t i = 0; i < nNodes; ++i)
  // {
  //   Ptr<Node> p = nodes.Get (i);
  //   i->method ();  // some Node method
  // }

  // std::vector<int> tempV(4, 0);
  // NodeContainer::Iterator i;
  // for (i = nodes.Begin (); i != nodes.End (); ++i)
  // {
  //   (*i)->display1DVector(tempV);  // some Node method
  //   (*i)->
  // }

  
  AsciiTraceHelper asciiTraceHelper;
  Ptr<OutputStreamWrapper> stream = asciiTraceHelper.CreateFileStream ("sixth.cwnd");
  ns3TcpSocket->TraceConnectWithoutContext ("CongestionWindow", MakeBoundCallback (&CwndChange, stream));

  
  PcapHelper pcapHelper;
  Ptr<PcapFileWrapper> file = pcapHelper.CreateFile ("sixth.pcap", std::ios::out, PcapHelper::DLT_PPP);
  devices.Get (1)->TraceConnectWithoutContext ("PhyRxDrop", MakeBoundCallback (&RxDrop, file));

  Simulator::Stop (Seconds (20));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

