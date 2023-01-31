#include <iostream>
#include <fstream>
//#include <string>
#include <vector>
#include<algorithm>
#include <ctime>
#include <numeric>
#include <random>
#include <math.h> 
#include <list>
#include "ns3/olsr-helper.h"
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
#include "ns3/wifi-helper.h"
#include "ns3/mobility-helper.h"
#include <ns3/yans-wifi-helper.h>
#include <ns3/yans-wifi-channel.h>
#include "ns3/wifi-phy.h"
#include <ns3/ssid.h>
#include "ns3/lte-helper.h"
#include <ns3/node-list.h>

#include "userDefinedFunctions.h"

using namespace std;
using namespace ns3;

template<typename T>
T random(T range_from, T range_to) {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<T> distr(range_from, range_to);
	return distr(generator);
}

double calculateSD(std::vector<int> data) 
{
  double sum = 0.0, mean, standardDeviation = 0.0;

  for(size_t i = 0; i < data.size(); ++i) 
    sum += (double)data[i];

  mean = sum / data.size();

  for(size_t i = 0; i < data.size(); ++i) 
    standardDeviation += pow(data[i] - mean, 2);

  return sqrt(standardDeviation / data.size());
}

//void hildegardVonBingen(std::vector<std::vector<int>> Hsys, std::vector<std::vector<int>> G, int N, int a, int b, int numberofInitialNodes, int numberofInitialLDPCStorageNodes, double delta, std::string rawFileName, int numberofRoundforBuffer, int p, int m, int n, std::string fileNameAlg1, std::string fileNameAlg2, Ptr<Socket> ns3TcpSocket, Address sinkAddress, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, MobilityHelper mobility, InternetStackHelper internet)
//void hildegardVonBingen(std::vector<std::vector<int>> Hsys, std::vector<std::vector<int>> G, int N, int a, int b, int numberofInitialNodes, int numberofInitialLDPCStorageNodes, double delta, std::string rawFileName, int numberofRoundforBuffer, int p, int m, int n, std::string fileNameAlg1, std::string fileNameAlg2, Ptr<Socket> ns3TcpSocket, Address sinkAddress, NodeContainer gNbNodes, NodeContainer ueNodes, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, InternetStackHelper internet, Ipv4InterfaceContainer ipInterfs)
void hildegardVonBingen(std::vector<std::vector<int>> Hsys, std::vector<std::vector<int>> G, int N, int a, int b, int numberofInitialNodes, int numberofInitialLDPCStorageNodes, double delta, std::string rawFileName, int numberofRoundforBuffer, int p, int m, int n, std::string fileNameAlg1, std::string fileNameAlg2)
{
	double tempA, tempS, tempAS;
	int rows = Hsys.size();
	int cols = Hsys[0].size();
	int rowsG = G.size();
	int colsG = G[0].size();
	std::vector<double> repairTimes;
	double arrivalTime;
	std::vector<double> arrivalTimes;
	double serviceTime;
	std::vector<double> serviceTimes;
	std::vector<double> departureTimes;
	//transform(v.begin(), v.end(), v.begin(), [delta](int &c) { return c*delta; });
	//for_each(v.begin(), v.end(), [delta](int &c) { c *= delta; });
	//for (int i = 0; i<v.size(); ++i)
	//	v[i] = v[i] * delta;
	int M = numberofInitialNodes;
	[[maybe_unused]] int allfileCreated = 0;
	//string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/";
	string root_directory = "scratch/testFolder/";
  //string root_directory = "scratch/";
	string current_directory = root_directory + "files/";
	std::ifstream testFile(rawFileName, std::ios_base::ate); // std::ios_base::ate seeks to the end of the file on construction of ifstream
	testFile.seekg(0, std::ios_base::end);
	int testFileSize = testFile.tellg();
	//testFile.seekg(0, std::ios_base::beg); // reset it to beginning if you want to use it
	string current_file = current_directory + "ledger.txt";
	remove(current_file.c_str());
	[[maybe_unused]] FILE *bookofAccountID, *bookofAccountIDV2, *bookofAccountIDV3, *allFilesResultsAlg1, *allFilesResultsAlg2;
	struct strP strParameters;
	struct strP strParameters2;
	std::vector<struct ns> nodeStr;
	struct departureReturns departureRs;
	struct repairReturns repairRs;
	struct encodingReturns encodingRs;
	[[maybe_unused]] int numberofLDPCStorageNodes = 0;
	string baseStation_file = current_directory + "baseStation.bin";	
	time_t startTimeLDPCEncoding, endTimeLDPCEncoding;
	[[maybe_unused]] int blockSize = 0, totalEncodedData = 0;
	std::vector<int> ldpcFileSizes(numberofInitialLDPCStorageNodes, 0);
	std::vector<int> aliveLDPCStorageNodes;
	double elapsedTimeLDPCEncoding;
	[[maybe_unused]] double baseStationSize;
	std::vector<double> initialArrivalTimes(numberofInitialNodes, 0);   //i.e 30 nodes          Initial arrval times for each node in the cell
	//std::list<double> initialArrivalTimes;
	//std::fill_n(initialArrivalTimes, numberofInitialNodes, 0);
	int number_of_time_clocks = 1000;
	std::vector<double> t(number_of_time_clocks, 0);
	int length;
	int startPoint;
	float tempRandomNumber;
	std::vector<double> sortedDepartureTimes;
	//std::list<int> sortedDepartureNodeIndexes;
	std::vector<int> sortedDepartureNodeIndexes;
	// std::vector<int> leavingNodes(N + numberofInitialNodes, 0);
	// std::vector<int> allDepartureNodes(N + numberofInitialNodes, 0);
	std::vector<int> leavingNodes;
	std::vector<int> allDepartureNodes;
	string current_file1 = current_directory + "ledgerV2.txt";
	string current_file2 = current_directory + "ledgerV4.txt";
	int counterLeavingNodes = 0;
	int counter = 0;
	int departureNodeIndex = 0;
	int arrivalNodeIndex = 0;
	int numberOfNodesIntheCell = 0;
	int iii = 0;
	int counterforRepair = 0;
	int numberofLostNodesforInterval = 0;
	int numberofArrivalNodesforInterval = 0;
	int numberofRepairs = 0;
	std::vector<int> symbolsfromBSPernodeV1ALL {};
	std::vector<int> symbolsfromBSPernodeV2ALL {};
	std::vector<int> symbolsfromNODESPernodeV1ALL {};
	std::vector<int> symbolsfromNODESPernodeV2ALL {};
	int symbolsfromBSPernodeV1 = 0;
	int symbolsfromBSPernodeV2 = 0;
	int symbolsfromNODESPernodeV1 = 0;
	int symbolsfromNODESPernodeV2 = 0;
	double timeforRepairResidualperNode = 0;
	double timeforRepairperNode = 0;
	int isMultipleRepair = 0;
	std::vector<int> leavingLDPCStorageNodes{};
	double ldpcFileSize;
	double averageTimeforRepairsperNode;
	double averageTimeforRepairsResidualperNode;
	double averageTimeforRepairsperSymbol;
	double averageTimeforRepairsResidualperSymbol;
	int numberofTotalLDPCRepairs;
	int stateRepair;

  std::vector<int> availableEmptyNodes; // DETERMINING EMPTY NODES IN THE CELL
  std::vector<int> availableLDPCStorageNodes;

	for (int i = 0; i < N; ++i) 
		repairTimes.push_back(double(1) * delta);
	
	bookofAccountID = fopen(current_file.c_str(), "a");
	if (bookofAccountID != NULL)
	{
		fprintf(bookofAccountID, "\n Raw file size is %d bytes", testFileSize);
		fprintf(bookofAccountID, "\n Number of rows in the systematic H matrix is %d", rows);
		fprintf(bookofAccountID, "\n Number of columns in the systematic H matrix is %d", cols);
		fprintf(bookofAccountID, "\n Number of rows in the G matrix is %d", rowsG);
		fprintf(bookofAccountID, "\n Number of columns in the G matrix is %d", colsG);
		fprintf(bookofAccountID, "\n Code Rate for LDPC is %.3f", float(rowsG / colsG));
		fprintf(bookofAccountID, "\n Number of initial LDPC storage nodes is %d", numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountID, "\n Number of initial nodes is %d", numberofInitialNodes);
		fprintf(bookofAccountID, "\n Buffer size for LDPC encoding is %d", numberofRoundforBuffer*numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountID, "\n Buffer size for LDPC decoding is %d", numberofRoundforBuffer*numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountID, "\n\n");
		fprintf(bookofAccountID, "\n SIMULATOR STARTS \n");
		fprintf(bookofAccountID, "\n\n");
		fclose(bookofAccountID);
	}

	numberofLDPCStorageNodes = numberofInitialLDPCStorageNodes;

	startTimeLDPCEncoding = time(0);
	cout<<"We are here in hildegard 5"<<endl;
	encodingRs = ldpcEncodingforArrrayLDPC(G, numberofInitialLDPCStorageNodes, rawFileName, baseStation_file, numberofRoundforBuffer, p, m, n, nodeStr);
	cout<<"We are here in hildegard 6"<<endl;
	blockSize = encodingRs.blockSize;
	aliveLDPCStorageNodes = encodingRs.aliveLDPCStorageNodes;
	totalEncodedData = encodingRs.totalEncodedData;
	ldpcFileSizes = encodingRs.ldpcFileSizes;
	nodeStr = encodingRs.nodeStr;

	endTimeLDPCEncoding = time(0);
	elapsedTimeLDPCEncoding = difftime(startTimeLDPCEncoding, endTimeLDPCEncoding);

	strParameters.startTimeLDPCEncoding = startTimeLDPCEncoding;
	strParameters.endTimeLDPCEncoding = elapsedTimeLDPCEncoding;

	strParameters2.startTimeLDPCEncoding = startTimeLDPCEncoding;
	strParameters2.endTimeLDPCEncoding = elapsedTimeLDPCEncoding;

	ifstream baseStation(baseStation_file, ios::binary);
	baseStation.seekg(0, ios::end);
	baseStationSize = baseStation.tellg();

	bookofAccountID = fopen(current_file.c_str(), "a");
	if (bookofAccountID != NULL)
	{
		fprintf(bookofAccountID, "\n Elapsed time of LDPC encoding is %f", strParameters.endTimeLDPCEncoding);
		fprintf(bookofAccountID, "\n");
		fprintf(bookofAccountID, "-------------------------------------------------------------------------------------------------------------------------------------------");
		fprintf(bookofAccountID, "\n");
		fclose(bookofAccountID);
	}

	t[0] = 0.01;
	for (int i = 1; i < number_of_time_clocks; i++)
		t[i] = t[i-1] + 0.01; // time clocks
	length = t.size();

	//cumulative sum of repair times
	for (size_t i = 1; i<repairTimes.size(); i++)
		repairTimes[i] = repairTimes[i - 1] + repairTimes[i];

	//std::default_random_engine generator;
	//std::uniform_real_distribution<double> distribution(length - numberofInitialNodes, 1.0);
	//double number = distribution(generator);

	startPoint = length - numberofInitialNodes;

	//const int range_from = 0;
	//const int range_to = 1;
	//std::random_device rand_dev;
	//std::mt19937 generator(rand_dev());
	//std::uniform_int_distribution<int> distr(range_from, range_to);
	//for (int i = 0; i < startPoint; ++i)
	//	std::cout << distr(generator) << '\n';

	std::mt19937_64 gen{ std::random_device()() };
	std::uniform_real_distribution<double> dis{ 0.0, 1.0 + std::numeric_limits<double>::epsilon() };
	for (int i = 0; i < startPoint; ++i)
	{
		tempRandomNumber = dis(gen);
		arrivalTime = -log(tempRandomNumber) / (M*a);
		arrivalTimes.push_back(arrivalTime);
	}	
	//std::vector<double> arrivalTimes = log(rand(startPoint, 1)) / (M*a); // Random interarrival times
	//std::list<double> arrivalTimes = log(rand(startPoint, 1)) / (M*a); // Random interarrival times
	// cout << "startPoint: " << startPoint << endl;
	// cout << "length: " << length << endl;
	// cout << "numberofInitialNodes: " << numberofInitialNodes << endl;
	// cout << "size of arrivalTimes: " << arrivalTimes.size() << endl;
	initialArrivalTimes.insert(initialArrivalTimes.end(), arrivalTimes.begin(), arrivalTimes.end());
	arrivalTimes = initialArrivalTimes;
	// cout << "size of arrivalTimes: " << arrivalTimes.size() << endl;
	// cout << endl;
	//cumulative sum of arrival times
	for (size_t i = 1; i<arrivalTimes.size(); i++)
		arrivalTimes[i] = arrivalTimes[i - 1] + arrivalTimes[i]; // Random arrival times

	for (int i = 0; i < length; ++i)
	{
		tempRandomNumber = dis(gen);
		serviceTime = -log(tempRandomNumber) / b;
		serviceTimes.push_back(serviceTime);
	}
	//std::vector<double> serviceTimes = -log(rand(length, 1)) / b;
	//std::list<double> serviceTimes = -log(rand(length, 1)) / b;
	//std::list<double> departureTimes;
	//std::vector<double> departureTimes(arrivalTimes.size(), 0);

	for (size_t i = 0; i<arrivalTimes.size(); i++)
	{
		tempA = arrivalTimes[i];
		tempS = serviceTimes[i];
		tempAS = tempA + tempS;
		departureTimes.push_back(tempAS);   // Departure times for each node in the cell
		//departureTimes.push_back(arrivalTimes[i] + serviceTimes[i]);   // Departure times for each node in the cell	
			
	}
	sortedDepartureTimes = departureTimes;
	//std::list<double> sortedDepartureTimes = departureTimes;
	//sortedDepartureTimes.sort();
	sort(sortedDepartureTimes.begin(), sortedDepartureTimes.end());

	for (size_t si = 0; si < sortedDepartureTimes.size(); si++)
	{
		for (size_t di = 0; di < departureTimes.size(); di++)
			if (sortedDepartureTimes[si] == departureTimes[di])
				sortedDepartureNodeIndexes.push_back(di);
	}

	bookofAccountIDV2 = fopen(current_file1.c_str(), "a");
	if (bookofAccountIDV2 != NULL)
	{
		fprintf(bookofAccountIDV2, "Time\n");
		fprintf(bookofAccountIDV2, "# of symbols readed from Nodes for LDPC\n");
		fprintf(bookofAccountIDV2, "# of symbols readed from Base Station for LDPC\n");
		fprintf(bookofAccountIDV2, "Elapsed Time for LDPC Repair\n");
		fprintf(bookofAccountIDV2, "# of helper nodes for LDPC\n");
		fprintf(bookofAccountIDV2, "# of lost LDPC nodes\n");
		fprintf(bookofAccountIDV2, "# of lost total nodes\n");
		fprintf(bookofAccountIDV2, "# of arrival nodes\n");
		fprintf(bookofAccountIDV2, "Type of repair\n");
		fprintf(bookofAccountIDV2, "---------------------------------------------\n");
		fprintf(bookofAccountIDV2, "\n");
		fclose(bookofAccountIDV2);
	}

	bookofAccountIDV3 = fopen(current_file2.c_str(), "a");
	if (bookofAccountIDV3 != NULL)
	{
		fprintf(bookofAccountIDV3, "Time\n");
		fprintf(bookofAccountIDV3, "# of symbols readed from Nodes for LDPC\n");
		fprintf(bookofAccountIDV3, "# of symbols readed from Base Station for LDPC\n");
		fprintf(bookofAccountIDV3, "Elapsed Time for LDPC Repair\n");
		fprintf(bookofAccountIDV3, "# of helper nodes for LDPC\n");
		fprintf(bookofAccountIDV3, "# of lost LDPC nodes\n");
		fprintf(bookofAccountIDV3, "# of lost total nodes\n");
		fprintf(bookofAccountIDV3, "# of arrival nodes\n");
		fprintf(bookofAccountIDV3, "Type of repair\n");
		fprintf(bookofAccountIDV3, "---------------------------------------------\n");
		fprintf(bookofAccountIDV3, "\n");
		fclose(bookofAccountIDV3);
	}

	NodeContainer newArrivalNodeContainer;
  NetDeviceContainer newArrivalDevice;
  Ipv4InterfaceContainer newArrivalInterface;
  //Ptr<NrHelper> nrHelper = CreateObject<NrHelper> ();
  // int counterZ = 0;
	while (repairTimes.empty() == 0 && arrivalTimes.empty() == 0)
	{
		stateRepair = 0;
		iii = iii + 1;
		// cout << "We are back" << endl;
		// double arrv = arrivalTimes.front();
		// double sdep = sortedDepartureTimes.front();

		if (arrivalTimes.front() < sortedDepartureTimes.front()) // Next point is arrival
		{
      // cout << "We are back 2" << endl;
			if (arrivalTimes.front() < repairTimes.front())
			{
        // cout << "We are back 3" << endl;

				numberOfNodesIntheCell = numberOfNodesIntheCell + 1;    // Increase cell size

       
				if (arrivalNodeIndex >= numberofInitialNodes)
				{
                    printf("Here1 processArrival!!!\n");
					nodeStr = processArrival(arrivalNodeIndex, nodeStr, arrivalTimes, serviceTimes);
					numberofArrivalNodesforInterval = numberofArrivalNodesforInterval + 1;
				}
				else
				{   
                 printf("Here0_11!!!\n");     
					if(arrivalNodeIndex < numberofInitialLDPCStorageNodes)
					{
            // printf("Here0_12!!!\n"); 
						nodeStr[arrivalNodeIndex].arrivalTime = arrivalTimes.front();
						nodeStr[arrivalNodeIndex].serviceTime = serviceTimes.front();
						nodeStr[arrivalNodeIndex].departureTime = arrivalTimes.front() + serviceTimes.front();
					}
					else
					{
						 printf("Here2 processArrival!!!\n");
						 nodeStr = processArrival(arrivalNodeIndex, nodeStr, arrivalTimes, serviceTimes);
					}
				}

        // printf("Here0_14!!!\n");
				arrivalNodeIndex = arrivalNodeIndex + 1;
				// Remove First Element From Vector
				arrivalTimes.erase(arrivalTimes.begin());      // Next arrival time is passed
				serviceTimes.erase(serviceTimes.begin());      // Next service time is passed
			}
			else
				stateRepair = 1;
		}
		else             // Next point is departure
		{ cout<<"dep or rep"<<endl;
			//cout<<sortedDepartureTimes.front()<<" "<<sortedDepartureTimes.begin()<<endl;
			if (sortedDepartureTimes.front() < repairTimes.front())
			{
				numberOfNodesIntheCell = numberOfNodesIntheCell - 1;    // Decrease cell size
				departureRs = processDeparture(departureNodeIndex, nodeStr, counter, allDepartureNodes, counterLeavingNodes, leavingNodes, numberofLDPCStorageNodes, sortedDepartureNodeIndexes, aliveLDPCStorageNodes, numberofLostNodesforInterval);
				cout<<"ProcessDeparture"<<endl;
				//[nodeStr, leavingNodes, numberofLDPCStorageNodes, allDepartureNodes, aliveLDPCStorageNodes, numberofLostNodesforInterval] = processDeparture(departureNodeIndex, nodeStr, counter, allDepartureNodes, counterLeavingNodes, leavingNodes, numberofLDPCStorageNodes, sortedDepartureNodeIndexes, aliveLDPCStorageNodes, numberofLostNodesforInterval);
				departureNodeIndex = departureNodeIndex + 1;
				counter = counter + 1;
				counterLeavingNodes = counterLeavingNodes + 1;

				nodeStr = departureRs.nodeStr;
				leavingNodes = departureRs.leavingNodes;
				numberofLDPCStorageNodes = departureRs.numberofLDPCStorageNodes;
				allDepartureNodes = departureRs.allDepartureNodes;
				aliveLDPCStorageNodes = departureRs.aliveLDPCStorageNodes;
				numberofLostNodesforInterval = departureRs.numberofLDPCStorageNodes;
				sortedDepartureTimes.erase(sortedDepartureTimes.begin());               // Next departure time is passed    
			}
			else
				stateRepair = 1;
		}

   if (stateRepair == 1)
	{
    	availableEmptyNodes.clear();
    	availableLDPCStorageNodes.clear();
    for (size_t  n= 0; n < nodeStr.size(); n++)
    {
      if (nodeStr[n].isLive == 1)
      {
        if (nodeStr[n].encodingType == 0)
          // DETERMINING AVAILABLE EMPTY STORAGE NODES IN THE CELL
          availableEmptyNodes.push_back(n);
        else
        {       
          // DETERMINING AVAILABLE LDPC STORAGE NODES IN THE CELL
          if (nodeStr[n].encodingType == 1)
            availableLDPCStorageNodes.push_back(n);
        }
      }
	}
        cout<<"repair etmeye çalışıyor"<<endl;

		if (stateRepair == 1 && (int)availableLDPCStorageNodes.size() < numberofInitialLDPCStorageNodes)
		{

			cout << "We are here in hildegardVonBingen before processRepair" << endl;
            cout << "size of availableEmptyNodes in hildegardVonBingen: " << availableEmptyNodes.size() << endl;
            cout << "size of availableLDPCStorageNodes in hildegardVonBingen: " << availableLDPCStorageNodes.size() << endl;
            cout << "counterLeavingNodes in hildegardVonBingen: " << counterLeavingNodes << endl;
            cout << "size of leavingNodes in hildegardVonBingen: " << leavingNodes.size() << endl;
      
      //---------------------------------------BEGINNING OF NodeToNodePacketReceiveSend--------------------------------------------------

      // Elif hocanın eklediği kısım access point için 
      std::string dataRate = "100Mbps";                  /* Application layer datarate. */
  		std::string tcpVariant = "TcpNewReno";             /* TCP variant type. */
  		std::string phyRate = "HtMcs7";                    /* Physical layer bitrate. */
  //double simulationTime = 10;                        /* Simulation time in seconds. */


  
  	WifiMacHelper wifiMac;
  	WifiHelper wifiHelper;
  	wifiHelper.SetStandard (WIFI_STANDARD_80211a);
  	/* Set up Legacy Channel */
  	YansWifiChannelHelper wifiChannel;
  	wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  	wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));
  	/* Setup Physical Layer */
  	YansWifiPhyHelper wifiPhy;
  	wifiPhy.SetChannel (wifiChannel.Create ());
  	wifiPhy.SetErrorRateModel ("ns3::YansErrorRateModel");
 	 wifiHelper.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                               "DataMode", StringValue ("OfdmRate54Mbps"));
  	wifiMac.SetType ("ns3::AdhocWifiMac");
  	uint16_t ueNodeCount = availableEmptyNodes.size() + availableLDPCStorageNodes.size(); 

  	NodeContainer ueNodes;
  	ueNodes.Create (ueNodeCount);
  	printf("UENODECOUNT ueNodeCount:%d", ueNodeCount);
  	NetDeviceContainer wifiDevices;
  	wifiDevices = wifiHelper.Install (wifiPhy, wifiMac, ueNodes);

  	/* Mobility model */
 	MobilityHelper mobility;
  	Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  //positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  //positionAlloc->Add (Vector (1.0, 1.0, 0.0));
    
 	for(int i=0;i<ueNodeCount;i++)
  	{
   		 positionAlloc->Add (Vector (i*0.5, i*0.3, 0.0));
  	}
  		Ipv4AddressHelper address;
  		address.SetBase ("10.1.0.0", "255.255.0.0");

 
  	   NodeContainer apNetworkNodes;
  	   apNetworkNodes.Create (1);
  	  	Ptr<Node> apWifiNode = apNetworkNodes.Get (0);

      
       
	 // Ipv4InterfaceContainer wifiIPContainer = ipv4.Assign (wiFidevices);

      //---------------------------------------END OF NodeToNodePacketReceiveSend--------------------------------------------------


      //---------------------------------------BEGINNING OF BSToNodePacketReceiveSend--------------------------------------------------
      // Elif hocanın LTE için eklediği kısım
      Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  	  Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
 	   lteHelper->SetEpcHelper (epcHelper);

  	 Ptr<Node> pgw = epcHelper->GetPgwNode ();

   // Create a single RemoteHost
  	NodeContainer remoteHostContainer;
  	remoteHostContainer.Create (1);
  	Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  	InternetStackHelper internet;
  	internet.Install (remoteHostContainer);

  // Create the Internet
  	PointToPointHelper p2ph;
  	p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  	p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
  	p2ph.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));
  	NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
 	Ipv4AddressHelper ipv4h;
 	 ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  	Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  	[[maybe_unused]] Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  	Ipv4StaticRoutingHelper ipv4RoutingHelper;
  	Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  	remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);

  //NodeContainer ueNodes;
  	NodeContainer enbNodes;
  	enbNodes.Create (1);


  	MobilityHelper mobility2;
	//mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel");
	 mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 60,0, 60)));
  	mobility2.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	//mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  	mobility2.SetPositionAllocator(positionAlloc);
	mobility.SetPositionAllocator(positionAlloc);
  	mobility2.Install(enbNodes);
  	mobility.Install(ueNodes);

  // Install LTE Devices to the nodes
  NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));
  Ipv4InterfaceContainer wifiIpIface = address.Assign(wifiDevices);
 for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  // Attach one UE per eNodeB
  for (uint16_t i = 0; i < ueNodeCount; i++)
    {
      lteHelper->Attach (ueLteDevs.Get(i), enbLteDevs.Get(0));
      // side effect: the default EPS bearer will be activated
    }

     //---------------------------------------END OF BSToNodePacketReceiveSend--------------------------------------------------// address=ipv4h, wifiHelper=wifi, ueIpIface ve apWifiNode kaldırılacak daha sonra
      repairRs = processRepair(Hsys, nodeStr, counterLeavingNodes, leavingNodes, numberofLDPCStorageNodes, numberofInitialLDPCStorageNodes, baseStationSize, ldpcFileSizes, strParameters, strParameters2, numberofRoundforBuffer, blockSize, aliveLDPCStorageNodes, enbNodes, ueNodes, internet, apWifiNode, mobility, ipv4h, wifiHelper, internetIpIfaces, ueIpIface, remoteHost);
      
		
	  cout << "We are here in hildegardVonBingen after processRepair" << endl << endl;
			isMultipleRepair = repairRs.isMultipleRepair;
			nodeStr = repairRs.nodeStr;
			numberofLDPCStorageNodes = repairRs.numberofLDPCStorageNodes;
			strParameters = repairRs.strParameters;
			strParameters2 = repairRs.strParameters2;
			leavingLDPCStorageNodes = repairRs.leavingLDPCStorageNodes;
			aliveLDPCStorageNodes = repairRs.aliveLDPCStorageNodes;
		}
			counterforRepair = counterforRepair + 1;
			if (leavingLDPCStorageNodes.size() > 0)
				numberofRepairs = numberofRepairs + 1;

			bookofAccountIDV2 = fopen(current_file1.c_str(), "a");
			if (bookofAccountIDV2 != NULL)
			{
				fprintf(bookofAccountIDV2, "%d\t", counterforRepair);
				fprintf(bookofAccountIDV2, "%d\t", strParameters.numberofReadedSymbolsfromNodesforLDPCRepair);
				fprintf(bookofAccountIDV2, "%d\t", strParameters.numberofReadedSymbolsfromBSforLDPCRepair);
				fprintf(bookofAccountIDV2, "%.3f\t", strParameters.endTimeLDPCRepair);
				fprintf(bookofAccountIDV2, "%d\t", strParameters.numberofLDPCHelpers);
				fprintf(bookofAccountIDV2, "%zu\t", leavingLDPCStorageNodes.size());
				fprintf(bookofAccountIDV2, "%d\t", numberofLostNodesforInterval);
				fprintf(bookofAccountIDV2, "%d\t", numberofArrivalNodesforInterval);
				if (isMultipleRepair == 1)
					fprintf(bookofAccountIDV2, "Multiple\t");
				else
					fprintf(bookofAccountIDV2, "Single\t");
				fprintf(bookofAccountIDV2, "\n");
				if (leavingLDPCStorageNodes.size() > 0)
				{
					cout<<"strParameters.endTimeLDPCRepair: " << strParameters.endTimeLDPCRepair << endl;
					cout<<"leavingLDPCStorageNodes.size(): " << leavingLDPCStorageNodes.size() << endl;
					cout<<"strParameters.endTimeLDPCRepair / leavingLDPCStorageNodes.size(): " << strParameters.endTimeLDPCRepair / leavingLDPCStorageNodes.size() << endl;
					cout<<"timeforRepairperNode before: " << timeforRepairperNode << endl;
					timeforRepairperNode = timeforRepairperNode + strParameters.endTimeLDPCRepair / leavingLDPCStorageNodes.size();
					cout<<"timeforRepairperNode after: " << timeforRepairperNode << endl;
					symbolsfromNODESPernodeV1 = symbolsfromNODESPernodeV1 + strParameters.numberofReadedSymbolsfromNodesforLDPCRepair / leavingLDPCStorageNodes.size();
					symbolsfromBSPernodeV1 = symbolsfromBSPernodeV1 + strParameters.numberofReadedSymbolsfromBSforLDPCRepair / leavingLDPCStorageNodes.size();
					//symbolsfromNODESPernodeV1ALL = [symbolsfromNODESPernodeV1ALL strParameters.numberofReadedSymbolsfromNodesforLDPCRepair / leavingLDPCStorageNodes.size()];
					//symbolsfromBSPernodeV1ALL = [symbolsfromBSPernodeV1ALL strParameters.numberofReadedSymbolsfromBSforLDPCRepair / leavingLDPCStorageNodes.size()];
					symbolsfromNODESPernodeV1ALL.push_back(strParameters.numberofReadedSymbolsfromNodesforLDPCRepair / leavingLDPCStorageNodes.size());
					symbolsfromBSPernodeV1ALL.push_back(strParameters.numberofReadedSymbolsfromBSforLDPCRepair / leavingLDPCStorageNodes.size());
				}
				else
				{
					//symbolsfromNODESPernodeV1ALL = [symbolsfromNODESPernodeV1ALL 0];
					//symbolsfromBSPernodeV1ALL = [symbolsfromBSPernodeV1ALL 0];
					//vector1.insert(vector1.end(), vector2.begin(), vector2.end()); //Concatenating two std::vectors
					symbolsfromNODESPernodeV1ALL.push_back(0);
					symbolsfromBSPernodeV1ALL.push_back(0);
				}
				fclose(bookofAccountIDV2);
			}
		
			// cout << "We are here in hildegardVonBingen 3" << endl;
			bookofAccountIDV3 = fopen(current_file2.c_str(), "a");
			if (bookofAccountIDV3 != NULL)
			{
				fprintf(bookofAccountIDV3, "%d\t", counterforRepair);
				fprintf(bookofAccountIDV3, "%d\t", strParameters2.numberofReadedSymbolsfromNodesforLDPCRepair);
				fprintf(bookofAccountIDV3, "%d\t", strParameters2.numberofReadedSymbolsfromBSforLDPCRepair);
				fprintf(bookofAccountIDV3, "%.3f\t", strParameters2.endTimeLDPCRepair);
				fprintf(bookofAccountIDV3, "%d\t", strParameters2.numberofLDPCHelpers);
				fprintf(bookofAccountIDV3, "%zu\t", leavingLDPCStorageNodes.size());
				fprintf(bookofAccountIDV3, "%d\t", numberofLostNodesforInterval);
				fprintf(bookofAccountIDV3, "%d\t", numberofArrivalNodesforInterval);
				if (isMultipleRepair == 1)
					fprintf(bookofAccountIDV3, "Multiple\t");
				else
					fprintf(bookofAccountIDV3, "Single\t");
				fprintf(bookofAccountIDV3, "\n");
				if (leavingLDPCStorageNodes.size() > 0)
				{
					timeforRepairperNode = timeforRepairperNode + strParameters2.endTimeLDPCRepair / leavingLDPCStorageNodes.size();
					symbolsfromNODESPernodeV1 = symbolsfromNODESPernodeV1 + strParameters2.numberofReadedSymbolsfromNodesforLDPCRepair / leavingLDPCStorageNodes.size();
					symbolsfromBSPernodeV1 = symbolsfromBSPernodeV1 + strParameters2.numberofReadedSymbolsfromBSforLDPCRepair / leavingLDPCStorageNodes.size();
					//symbolsfromNODESPernodeV1ALL = [symbolsfromNODESPernodeV1ALL strParameters2.numberofReadedSymbolsfromNodesforLDPCRepair / leavingLDPCStorageNodes.size()];
					//symbolsfromBSPernodeV1ALL = [symbolsfromBSPernodeV1ALL strParameters2.numberofReadedSymbolsfromBSforLDPCRepair / leavingLDPCStorageNodes.size()];
					symbolsfromNODESPernodeV1ALL.push_back(strParameters2.numberofReadedSymbolsfromNodesforLDPCRepair / leavingLDPCStorageNodes.size());
					symbolsfromBSPernodeV1ALL.push_back(strParameters2.numberofReadedSymbolsfromBSforLDPCRepair / leavingLDPCStorageNodes.size());
				}
				else
				{		
					//symbolsfromNODESPernodeV1ALL = [symbolsfromNODESPernodeV1ALL 0];
					//symbolsfromBSPernodeV1ALL = [symbolsfromBSPernodeV1ALL 0];
					//vector1.insert(vector1.end(), vector2.begin(), vector2.end()); //Concatenating two std::vectors
					symbolsfromNODESPernodeV1ALL.push_back(0);
					symbolsfromBSPernodeV1ALL.push_back(0);
				}
				fclose(bookofAccountIDV3);
			}
			// cout << "We are here in hildegardVonBingen 4" << endl;
			bookofAccountID = fopen(current_file.c_str(), "a");
			if (bookofAccountID != NULL)
			{
				fprintf(bookofAccountID, "\n Number of symbols readed from base station for LDPC repair is %d", strParameters.numberofReadedSymbolsfromBSforLDPCRepair);
				fprintf(bookofAccountID, "\n Number of symbols readed from nodes for LDPC repair is %d", strParameters.numberofReadedSymbolsfromNodesforLDPCRepair);
				fprintf(bookofAccountID, "\n Number of LDPC helpers for LDPC repair is %d", strParameters.numberofLDPCHelpers);
				fprintf(bookofAccountID, "\n Elapsed time for LDPC repair is %f", strParameters.endTimeLDPCRepair);
				fprintf(bookofAccountID, "\n");
				fprintf(bookofAccountID, "-------------------------------------------------------------------------------------------------------------------------------------------");
				fprintf(bookofAccountID, "\n");
				fclose(bookofAccountID);
			}
	

			numberofLostNodesforInterval = 0;
			numberofArrivalNodesforInterval = 0;

			strParameters.numberofReadedSymbolsfromBSforLDPCRepair = 0;
			strParameters.numberofReadedSymbolsfromNodesforLDPCRepair = 0;
			strParameters.numberofLDPCHelpers = 0;
			strParameters.startTimeLDPCRepair = 0;
			strParameters.endTimeLDPCRepair = 0;
			strParameters.repairTimeforRemainderSymbols = 0;

			strParameters2.numberofReadedSymbolsfromBSforLDPCRepair = 0;
			strParameters2.numberofReadedSymbolsfromNodesforLDPCRepair = 0;
			strParameters2.numberofLDPCHelpers = 0;
			strParameters2.startTimeLDPCRepair = 0;
			strParameters2.endTimeLDPCRepair = 0;
			strParameters2.repairTimeforRemainderSymbols = 0;
			// cout << "We are here in hildegardVonBingen 5" << endl;
			
		
			counterLeavingNodes = 0;
			leavingNodes.clear();
			// cout << "size of repairTimes before erase operation in hildegardVonBingen: " << repairTimes.size() << endl;
			repairTimes.erase(repairTimes.begin());
			// cout << "We are here in hildegardVonBingen 6" << endl;
			// cout << "stateRepair: " << stateRepair << endl;
		
			
		}
	}
	


	// cout << "We are here in hildegardVonBingen 7" << endl;
	ldpcFileSize = totalEncodedData / numberofInitialLDPCStorageNodes;
	cout<<"timeforRepairperNode: " << timeforRepairperNode << endl;
	cout<<"numberofRepairs: " << numberofRepairs << endl;
	averageTimeforRepairsperNode = timeforRepairperNode / (double)numberofRepairs;
	cout<<"averageTimeforRepairsperNode: " << averageTimeforRepairsperNode << endl;
	averageTimeforRepairsResidualperNode = timeforRepairResidualperNode / (double)numberofRepairs;
	averageTimeforRepairsperSymbol = averageTimeforRepairsperNode / ldpcFileSize;
	averageTimeforRepairsResidualperSymbol = averageTimeforRepairsResidualperNode / ldpcFileSize;
	numberofTotalLDPCRepairs = strParameters.numberofLDPCRepairswithBaseStation + strParameters.numberofLDPCRepairswithoutBaseStation + strParameters.numberofLDPCRepairswithOnlyBaseStation;
	// cout << "We are here in hildegardVonBingen 8" << endl;
	bookofAccountID = fopen(current_file.c_str(), "a");
	if (bookofAccountID != NULL)
	{
		fprintf(bookofAccountID, "\n\n");
		fprintf(bookofAccountID, "\n Number of LDPC repairs with base station and nodes is %d", strParameters.numberofLDPCRepairswithBaseStation);
		fprintf(bookofAccountID, "\n Number of LDPC repairs without base station is %d", strParameters.numberofLDPCRepairswithoutBaseStation);
		fprintf(bookofAccountID, "\n Number of LDPC repairs with only base station is %d", strParameters.numberofLDPCRepairswithOnlyBaseStation);
		fprintf(bookofAccountID, "\n Ratio of LDPC repairs with base station and nodes is %.3f", 100.0 * (strParameters.numberofLDPCRepairswithBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountID, "\n Ratio of LDPC repairs without base station is %.3f", 100.0 * (strParameters.numberofLDPCRepairswithoutBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountID, "\n Ratio of LDPC repairs with only base station is %.3f", 100.0 * (strParameters.numberofLDPCRepairswithOnlyBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountID, "\n\n\nSIMULATOR ENDS \n");
		fprintf(bookofAccountID, "\n\n");
		fclose(bookofAccountID);
	}
	// cout << "We are here in hildegardVonBingen 9" << endl;
	bookofAccountIDV2 = fopen(current_file1.c_str(), "a");
	if (bookofAccountIDV2 != NULL)
	{
		fprintf(bookofAccountIDV2, "\n");
		fprintf(bookofAccountIDV2, "Total encoded data: %d bytes\n", totalEncodedData);
		fprintf(bookofAccountIDV2, "Encoding time for LDPC: %.3f\n", strParameters.endTimeLDPCEncoding);
		fprintf(bookofAccountIDV2, "Number of rows in the systematic H matrix: %d\n", rows);
		fprintf(bookofAccountIDV2, "Number of columns in the systematic H matrix: %d\n", cols);
		fprintf(bookofAccountIDV2, "Number of rows in the LDPC generator matrix: %d\n", rowsG);
		fprintf(bookofAccountIDV2, "Number of columns in the LDPC generator matrix: %d\n", colsG);
		fprintf(bookofAccountIDV2, "Raw file size: %d bytes\n", testFileSize);
		fprintf(bookofAccountIDV2, "Buffer size for LDPC encoding: %d\n", numberofRoundforBuffer*numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountIDV2, "Buffer size for LDPC decoding: %d\n", numberofRoundforBuffer*numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountIDV2, "\n");
		fprintf(bookofAccountIDV2, "Number of LDPC repairs with both base station and nodes: %d\n", strParameters.numberofLDPCRepairswithBaseStation);
		fprintf(bookofAccountIDV2, "Number of LDPC repairs without base station: %d\n", strParameters.numberofLDPCRepairswithoutBaseStation);
		fprintf(bookofAccountIDV2, "Number of LDPC repairs with only base station: %d\n", strParameters.numberofLDPCRepairswithOnlyBaseStation);
		fprintf(bookofAccountIDV2, "Ratio of LDPC repairs with base station and nodes: %.3f\n", 100.0 * (strParameters.numberofLDPCRepairswithBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountIDV2, "Ratio of LDPC repairs without base station: %.3f\n", 100.0 * (strParameters.numberofLDPCRepairswithoutBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountIDV2, "Ratio of LDPC repairs with only base station: %.3f\n", 100.0 * (strParameters.numberofLDPCRepairswithOnlyBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountIDV2, "\n\n\nSIMULATOR SETTINGS \n");
		fprintf(bookofAccountIDV2, "------------------------------------ \n");
		fprintf(bookofAccountIDV2, "Initial number of nodes in the cell: %d\n", numberofInitialNodes);
		fprintf(bookofAccountIDV2, "Number of initial LDPC storage nodes: %d\n", numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountIDV2, "Arrival rate: %d\n", a);
		fprintf(bookofAccountIDV2, "Departure rate: %d\n", b);
		fprintf(bookofAccountIDV2, "Interval time between two repairs: %.3f\n", delta);
		fprintf(bookofAccountIDV2, "File size of a LDPC node: %d\n", ldpcFileSizes.front());
		fprintf(bookofAccountIDV2, "Symbols readed from other nodes per lost Node : %.6f\n", (double)(symbolsfromNODESPernodeV1 / counterforRepair));
		fprintf(bookofAccountIDV2, "Symbols readed from Bs  per lost Node : %.6f\n", (double)(symbolsfromBSPernodeV1 / counterforRepair));
		fprintf(bookofAccountIDV2, "Symbols readed from stderr  symbolsfromNODESPernodeV2ALL : %.6f\n", (calculateSD(symbolsfromNODESPernodeV1ALL) / sqrt(counterforRepair)));
		fprintf(bookofAccountIDV2, "Symbols readed from stderr symbolsfromBSPernodeV2ALL : %.6f\n", (calculateSD(symbolsfromBSPernodeV1ALL) / sqrt(counterforRepair)));
		fprintf(bookofAccountIDV2, "Average Repair Time per Node : %.6f\n", averageTimeforRepairsperNode);
		fprintf(bookofAccountIDV2, "Average Repair Time per Symbol : %.6f\n", averageTimeforRepairsperSymbol);
		fclose(bookofAccountIDV2);

		// cout << "We are here before fileNameAlg1 writing" << endl;
		// cout << "fileNameAlg1: " << fileNameAlg1.c_str() << endl;
		allFilesResultsAlg1 = fopen(fileNameAlg1.c_str(), "a");
		if (allFilesResultsAlg1 != NULL)
		{
			if (allfileCreated == 0)
				allfileCreated = 1;
			fprintf(allFilesResultsAlg1, "%.3f\t", delta);
			fprintf(allFilesResultsAlg1, "%.6f\t", (double)(symbolsfromNODESPernodeV1 / counterforRepair));     //Symbols readed from other nodes per lost Node : %.6f
			fprintf(allFilesResultsAlg1, "%.6f\t", (calculateSD(symbolsfromNODESPernodeV1ALL) / sqrt(counterforRepair)));    //Symbols readed from stderr  symbolsfromNODESPernodeV2ALL :
			fprintf(allFilesResultsAlg1, "%.6f\t", (double)(symbolsfromBSPernodeV1 / counterforRepair));    //Symbols readed from Bs  per lost Node :
			fprintf(allFilesResultsAlg1, "%.6f\t", (calculateSD(symbolsfromBSPernodeV1ALL) / sqrt(counterforRepair)));    //Symbols readed from stderr symbolsfromBSPernodeV2ALL :
			fprintf(allFilesResultsAlg1, "%.6f\t", averageTimeforRepairsperNode);
			fprintf(allFilesResultsAlg1, "%.6f\t", averageTimeforRepairsperSymbol);
			fprintf(allFilesResultsAlg1, "%.6f\t", timeforRepairperNode);
			fprintf(allFilesResultsAlg1, "%d\t", numberofRepairs);
			fprintf(allFilesResultsAlg1, "%.6f\n", (double)totalEncodedData);
			fclose(allFilesResultsAlg1);
		}
	}
	// cout << "We are here in hildegardVonBingen 10" << endl;
	bookofAccountIDV3 = fopen(current_file2.c_str(), "a");
	if (bookofAccountIDV3 != NULL)
	{
		fprintf(bookofAccountIDV3, "\n");
		fprintf(bookofAccountIDV3, "Total encoded data: %.3f bytes\n", (double)totalEncodedData);
		fprintf(bookofAccountIDV3, "Encoding time for LDPC: %.3f\n", strParameters2.endTimeLDPCEncoding);
		fprintf(bookofAccountIDV3, "Number of rows in the systematic H matrix: %d\n", rows);
		fprintf(bookofAccountIDV3, "Number of columns in the systematic H matrix: %d\n", cols);
		fprintf(bookofAccountIDV3, "Number of rows in the LDPC generator matrix: %d\n", rowsG);
		fprintf(bookofAccountIDV3, "Number of columns in the LDPC generator matrix: %d\n", colsG);
		fprintf(bookofAccountIDV3, "Raw file size: %d bytes\n", testFileSize);
		fprintf(bookofAccountIDV3, "Buffer size for LDPC encoding: %d\n", numberofRoundforBuffer*numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountIDV3, "Buffer size for LDPC decoding: %d\n", numberofRoundforBuffer*numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountIDV3, "\n");
		fprintf(bookofAccountIDV3, "Number of LDPC repairs with both base station and nodes: %d\n", strParameters2.numberofLDPCRepairswithBaseStation);
		fprintf(bookofAccountIDV3, "Number of LDPC repairs without base station: %d\n", strParameters2.numberofLDPCRepairswithoutBaseStation);
		fprintf(bookofAccountIDV3, "Number of LDPC repairs with only base station: %d\n", strParameters2.numberofLDPCRepairswithOnlyBaseStation);
		fprintf(bookofAccountIDV3, "Ratio of LDPC repairs with base station and nodes: %.3f\n", 100.0 * (strParameters2.numberofLDPCRepairswithBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountIDV3, "Ratio of LDPC repairs without base station: %.3f\n", 100.0 * (strParameters2.numberofLDPCRepairswithoutBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountIDV3, "Ratio of LDPC repairs with only base station: %.3f\n", 100.0 * (strParameters2.numberofLDPCRepairswithOnlyBaseStation / numberofTotalLDPCRepairs));
		fprintf(bookofAccountIDV3, "\n\n\nSIMULATOR SETTINGS \n");
		fprintf(bookofAccountIDV3, "------------------------------------ \n");
		fprintf(bookofAccountIDV3, "Initial number of nodes in the cell: %d\n", numberofInitialNodes);
		fprintf(bookofAccountIDV3, "Number of initial LDPC storage nodes: %d\n", numberofInitialLDPCStorageNodes);
		fprintf(bookofAccountIDV3, "Arrival rate: %d\n", a);
		fprintf(bookofAccountIDV3, "Departure rate: %d\n", b);
		fprintf(bookofAccountIDV3, "Interval time between two repairs: %.3f\n", delta);
		fprintf(bookofAccountIDV3, "File size of a LDPC node: %d\n", ldpcFileSizes.front());
		fprintf(bookofAccountIDV3, "Symbols readed from other nodes per lost Node : %.6f\n", (double)(symbolsfromNODESPernodeV2 / counterforRepair));
		fprintf(bookofAccountIDV3, "Symbols readed from Bs  per lost Node : %.6f\n", (double)(symbolsfromBSPernodeV2 / counterforRepair));
		fprintf(bookofAccountIDV3, "Symbols readed from stderr  symbolsfromNODESPernodeV2ALL : %.6f\n", (calculateSD(symbolsfromNODESPernodeV2ALL) / sqrt(counterforRepair)));
		fprintf(bookofAccountIDV3, "Symbols readed from stderr symbolsfromBSPernodeV2ALL : %.6f\n", (calculateSD(symbolsfromBSPernodeV2ALL) / sqrt(counterforRepair)));
		fprintf(bookofAccountIDV3, "Average Repair Time per Node : %.6f\n", averageTimeforRepairsResidualperNode);
		fprintf(bookofAccountIDV3, "Average Repair Time per Symbol : %.6f\n", averageTimeforRepairsResidualperSymbol);
		fclose(bookofAccountIDV3);

		// cout << "We are here before fileNameAlg2 writing" << endl;
		// cout << "fileNameAlg2: " << fileNameAlg2.c_str() << endl;
		allFilesResultsAlg2 = fopen(fileNameAlg2.c_str(), "a");
		if (allFilesResultsAlg2 != NULL)
		{
			if (allfileCreated == 0)
				allfileCreated = 1;
			fprintf(allFilesResultsAlg2, "%.3f\t", delta);
			fprintf(allFilesResultsAlg2, "%.6f\t", (double)(symbolsfromNODESPernodeV2 / counterforRepair));     //Symbols readed from other nodes per lost Node : %.6f
			fprintf(allFilesResultsAlg2, "%.6f\t", (calculateSD(symbolsfromNODESPernodeV2ALL) / sqrt(counterforRepair)));    //Symbols readed from stderr  symbolsfromNODESPernodeV2ALL :
			fprintf(allFilesResultsAlg2, "%.6f\t", (double)(symbolsfromBSPernodeV2 / counterforRepair));    //Symbols readed from Bs  per lost Node :
			fprintf(allFilesResultsAlg2, "%.6f\t", (calculateSD(symbolsfromBSPernodeV2ALL) / sqrt(counterforRepair)));    //Symbols readed from stderr symbolsfromBSPernodeV2ALL :
			fprintf(allFilesResultsAlg2, "%.6f\t", averageTimeforRepairsResidualperNode);
			fprintf(allFilesResultsAlg2, "%.6f\t", averageTimeforRepairsResidualperSymbol);
			fprintf(allFilesResultsAlg2, "%.6f\t", timeforRepairperNode);
			fprintf(allFilesResultsAlg2, "%d\t", numberofRepairs);
			fprintf(allFilesResultsAlg2, "%.6f\n", (double)totalEncodedData);
			fclose(allFilesResultsAlg2);
		}
	
	// cout << "We are here in hildegardVonBingen 11" << endl;
	}
}

