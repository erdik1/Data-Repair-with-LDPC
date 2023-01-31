#include "userDefinedFunctions.h"
//#include "userDefinedFunctions2.h"
//#include "HandleMessages.h"
//#include "TcpSocketProcesses.h"
#include "messages.h"
#include "NewComerNodeApp.h"
#include "UENodeApp.h"
#include "BSApp.h"


//#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
//#include "ipv4-interface-container.h"
//#include "ns3/eps-bearer-tag.h"
#include <random>
//#include "ns3/application.h"

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

using namespace std;
using namespace ns3;
// Flow monitor
//Ptr<FlowMonitor> flowMonitor;
//typedef struct singleRepairAlgorithmV1Returns Struct;
//#include "HandleMessages.h"
struct singleRepairAlgorithmV1Returns
{
	std::vector<std::string> totalHelperFiles;
	std::vector<struct ns> nodeStr;
	struct strP strParameters;
	std::vector<int> aliveLDPCStorageNodes;
	NewComerNodeApp* newcomerapp;
	UENodeApp** ueapps;
};
//Struct LDPCSingleRepairAlgorithmV1NodeContainer(int foundOne, std::string repairedFile, std::vector<int> currentLostSymbols, std::vector<std::string> totalHelperFiles, int cols, int quotient, std::vector<std::vector<int>> Hsys, std::vector<struct ns> nodeStr, std::vector<int> lostLDPCChunkSymbols, struct strP strParameters, int numberofRoundforBuffer, std::vector<int> aliveLDPCStorageNodes, double blockSize, int maxColLength, NodeContainer gNbNodes, NodeContainer ueNodes, int selectedLostNodeIndex, int selectedEmptyNodeIndex, NetDeviceContainer gNbNetDev, NetDeviceContainer ueNetDev, InternetStackHelper internet, Ptr<Node> apWifiNode, MobilityHelper mobility, Ipv4AddressHelper address, Ipv4InterfaceContainer internetIpIfaces, Ipv4InterfaceContainer ueIpIface, Ptr<Node> remoteHost, WifiHelper wifiHelper, std::string tempUsedEmptyNodeforRepair, int selectedTempEmptyNodeIndex)
struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1NodeContainer(int foundOne, std::string repairedFile, std::vector<int> currentLostSymbols, std::vector<std::string> totalHelperFiles, int cols, int quotient, std::vector<std::vector<int>> Hsys, std::vector<struct ns> nodeStr, std::vector<int> lostLDPCChunkSymbols, struct strP strParameters, int numberofRoundforBuffer, std::vector<int> aliveLDPCStorageNodes, double blockSize, int maxColLength, NodeContainer gNbNodes, NodeContainer ueNodes, int selectedLostNodeIndex, int selectedEmptyNodeIndex, InternetStackHelper internet, Ptr<Node> apWifiNode, MobilityHelper mobility, Ipv4AddressHelper address, Ipv4InterfaceContainer internetIpIfaces, Ipv4InterfaceContainer ueIpIface, Ptr<Node> remoteHost, WifiHelper wifiHelper, std::string tempUsedEmptyNodeforRepair, int selectedTempEmptyNodeIndex, int selectedEmptyNodeLogicalIndex)
//Struct LDPCSingleRepairAlgorithmV1NodeContainer(int foundOne, std::string repairedFile, std::vector<int> currentLostSymbols, std::vector<std::string> totalHelperFiles, int cols, int quotient, std::vector<std::vector<int>> Hsys, std::vector<struct ns> nodeStr, std::vector<int> lostLDPCChunkSymbols, struct strP strParameters, int numberofRoundforBuffer, std::vector<int> aliveLDPCStorageNodes, double blockSize, int maxColLength)
{
	cout<<"H 0"<<endl;
	struct singleRepairAlgorithmV1Returns sraV1Local;
	struct generateHelpersReturns gHR;
	struct firstPhaseReturns fpr;
	struct secondPhaseReturns spr;
	struct fakeFirstPhaseReturns ffpr;
	struct fakeSecondPhaseReturns fspr;
	
	// string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/files/";
	string root_directory = "scratch/testFolder/files/";
	//string root_directory = "scratch/files/";
	//string root_directory = "files/";
	int numberofLostSymbols = currentLostSymbols.size();
	//cout << "numberofLostSymbols: " << numberofLostSymbols << endl;
	std::vector<int> currentLostLDPCChunkSymbols = lostLDPCChunkSymbols;
	string baseStation = root_directory + "baseStation.bin";
   cout<<"H 01"<<endl;
	// Generating helper symbol indexes for each lost symbol
	std::vector<int> L = currentLostSymbols;
	// int index1 = 0;
	// int index2 = 0;
	std::vector<std::vector<int>> R1;
	//std::vector<int> localR1;
	std::vector<std::vector<int>> R2;
	std::vector<int> localR2;
	//std::vector<std::vector<int>> recoveryEquations (numberofLostSymbols, vector<int>(cols - 1, 0));
	std::vector<std::vector<int>> recoveryEquations;
	recoveryEquations.resize(numberofLostSymbols);
	std::vector<int> unrepairedSymbolsfromNodes;
	std::vector<int> unrepairedSymbolsfromBS;
	std::vector<std::vector<int>> allEquationsR2;
	//std::vector<int> copyAllEquationsR2;
	std::vector<int>::iterator it;
	std::vector<int> v;
	int intR;
	int failedSymbolID;
	std::vector<int> helperSymbolIndexes;
	//std::vector<std::vector<int>> allEquations (recoveryEquations[0].size() + allEquationsR2[0].size(), std::vector<int>(std::max(recoveryEquations[0].size(), allEquationsR2.size() - 1)));
	std::vector<std::vector<int>> allEquations;
	// tempEquations = recoveryEquations;
	std::vector<std::vector<int>> tempEquations;
	std::vector<int> symbols;
	std::vector<int> fileIndexes;
	int tempVal;
	std::vector<string> inputFiles {};
	//std::vector<int> inputFileIDs {};
	std::vector<int> synchronisedFileIndexes{};
	std::vector<int> foundIndexes {};
	[[maybe_unused]] std::vector<std::ifstream *> inputFileIDs;
	string fileFullDirectory;

	std::vector<int> readIndexes(inputFiles.size(), 0);
	std::vector<uint8_t> read(quotient, 1);
	std::vector<std::vector<uint8_t>> encodedData;
	std::vector<std::vector<int>> R2ReducedCopy;
	std::vector<int> usedHelpers;
	std::vector<std::vector<int>> R2Reduced;
	std::vector<std::vector<int>> tempR2;
	std::vector<int> tempL;
	std::vector<int> tempUnrepairedSymbolsfromNodes;
	std::vector<int> tempUnrepairedSymbolsfromBS;
	std::vector<int> tempCurrentLostLDPCChunkSymbols;
	std::vector<std::vector<uint8_t>> readedDatainBuffer{};
	std::vector<uint8_t> readedEncodedData(maxColLength,0);
	// int jj;
	// int readIndex;
	std::vector<std::vector<int>> R1Temp;
	std::vector<std::vector<int>> R2Temp;
	std::vector<uint8_t> buffer2(quotient);
	// int bInd;
	//char * buffer = new char[quotient];
	int stopState;
	//int columnIndex;
	int currentColumnIndex;
	std::vector<int> inputFilesSize {};
	std::string path;
	int intersectionState;
	[[maybe_unused]] uint32_t  udpPacketSize = (uint32_t)numberofRoundforBuffer;

	std::vector<int> tempUsedHelpers{};
	std::vector<int> helperNodes, helperNodes2,helperNodeLogicalIndexes;
	std::vector<int> currentHelperNodeIndexes{};
	std::vector<int> currentHelperNodeIndexes2{};
	std::vector<int> allHelperNodeIndexes{};
	std::vector<int>::iterator tempIt, tempIt2;
	[[maybe_unused]]int repairedFileSize;
	[[maybe_unused]]int tempUsedEmptyNodeFileSize;
	//int shouldbeRead;
	std::vector<int> failedSymbolIDsForRepairFromBS{};
	Ipv4Address receiverAddress;
	Ipv4Address senderAddress;
	[[maybe_unused]] int selectedHelperNodeIndex = 0;
	[[maybe_unused]] int selectedHelperNodeLogicalIndex = 0;

	[[maybe_unused]] uint16_t servPort = 5000;
	Ptr<Node> staWifiNode1, staWifiNode2;
	Address defaultAddress;
    cout<<"H 1"<<endl;
	for (int index = 0; index < numberofLostSymbols; index++)
	{
		failedSymbolID = currentLostSymbols[index];
		cout<<"H 1.1"<<endl;
		gHR = GenerateHelpers(Hsys, failedSymbolID, lostLDPCChunkSymbols, allEquationsR2);
		helperSymbolIndexes = gHR.helperSymbolIndexes;
		cout<<"H 1.2"<<endl;
		allEquationsR2 = gHR.allEquationsR2;
		for (size_t i=0; i<helperSymbolIndexes.size(); i++)
			recoveryEquations[index].push_back(helperSymbolIndexes[i]);
			//recoveryEquations[index][i] = helperSymbolIndexes[i];

		intersectionState = 0;
		for (size_t i = 0; i < helperSymbolIndexes.size(); i++)
		{
			for (size_t j = 0; j < lostLDPCChunkSymbols.size(); j++)
			{
				if (helperSymbolIndexes[i] == lostLDPCChunkSymbols[j])
				{
					intersectionState = 1;
					break;
				}
			}
			if (intersectionState == 1)
				break;
		}
		if (intersectionState == 1)
		{
			localR2.push_back(failedSymbolID);
			for (size_t in = 0; in < helperSymbolIndexes.size(); in++)
				localR2.push_back(helperSymbolIndexes[in]);
			R2.push_back(localR2);
			unrepairedSymbolsfromBS.push_back(failedSymbolID);
		}
		else
		{					
			R1.push_back(helperSymbolIndexes);
			unrepairedSymbolsfromNodes.push_back(failedSymbolID);
		}
		// cout << "intersectionState: " << intersectionState << endl;
		// cout << endl;
        cout<<"H 1.3"<<endl;
		localR2.clear();
		helperSymbolIndexes.clear();
	}

	allEquations.resize(recoveryEquations.size() + allEquationsR2.size());
	
	intR = 0;
	for (size_t r = 0; r < recoveryEquations.size(); r++)
	{
		for (size_t c = 0; c < recoveryEquations[r].size(); c++)
			allEquations[intR].push_back(recoveryEquations[r][c]);
		intR = intR + 1;
	}

	for (size_t r = 0; r < allEquationsR2.size(); r++)
	{
		for (size_t c = 1; c < allEquationsR2[r].size(); c++)
			allEquations[intR].push_back(allEquationsR2[r][c]);
		intR = intR + 1;
	}
	
	// in the end of the this section, tempEquations(i + 1) stores the information of the union of the helper symbols idxes
	tempEquations = allEquations;
	for (size_t i = 0; i < tempEquations.size(); i++)
	{
		for (size_t j = 0; j < tempEquations[i].size(); j++)
		{
			// if (tempEquations[i][j] != 0)
			// {
				symbols.push_back(tempEquations[i][j]);
				tempVal = ceil((double)tempEquations[i][j] / (double)quotient);
				fileIndexes.push_back(tempVal);
			// }
		}
	}

	sort(fileIndexes.begin(), fileIndexes.end());
	std::vector<int>::iterator it2 = unique(fileIndexes.begin(), fileIndexes.end());
	fileIndexes.resize(distance(fileIndexes.begin(), it2));

	// Opening files which are encoded by LDPC	
	for (size_t t = 0; t < aliveLDPCStorageNodes.size(); t++)
	{
		for (size_t si = 0; si < fileIndexes.size(); si++)
		{
			if (fileIndexes[si] == (int)t+1)
				foundIndexes.push_back(t);
		}

		// if (aliveLDPCStorageNodes[t] != -1 && foundIndexes.size()>0)
		if (aliveLDPCStorageNodes[t] != -1)
		{
			fileFullDirectory = root_directory + nodeStr[aliveLDPCStorageNodes[t]].fileName.c_str();
			inputFiles.push_back(fileFullDirectory);
			synchronisedFileIndexes.push_back(t);
			// std::ifstream* f = new std::ifstream(fileFullDirectory.c_str(), std::ios::in| std::ios::binary| std::ios::ate);
			// inputFileIDs.push_back(f);
		}
	}

	for (size_t r = 0; r < inputFiles.size(); r++)
		totalHelperFiles.push_back(inputFiles[r]);

	stopState = 0;
	//columnIndex = 0;
	currentColumnIndex = 0;

	// for (size_t g = 0; g < inputFiles.size(); g++)
	// 	inputFilesSize.push_back(std::filesystem::file_size(inputFiles[g].c_str()));

	readIndexes.resize(inputFiles.size());

	tempR2 = R2;
	tempL = L;
	tempUnrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
	tempUnrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
	tempCurrentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;

	//ffpr = FakeFirstPhaseV2(currentLostLDPCChunkSymbols, L, R1, R2, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, quotient, selectedEmptyNodeIndex, ueNetDev, numberofRoundforBuffer, servPort, mobility, address, inputFiles, aliveLDPCStorageNodes, ueNodes, wifiHelper, maxColLength, repairedFile);	
	ffpr = FakeFirstPhaseV2(currentLostLDPCChunkSymbols, tempL, R1, R2, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, quotient, aliveLDPCStorageNodes);
	tempUsedHelpers = ffpr.tempUsedHelpers;
	helperNodes = ffpr.helperNodes;
	allHelperNodeIndexes = ffpr.currentHelperNodeIndexes;
	usedHelpers = ffpr.usedHelpers;
	tempL = ffpr.tempL;
	R2ReducedCopy = ffpr.R2ReducedCopy;
	//strParameters = ffpr.strParameters;

	//fspr = FakeSecondPhaseV2(currentLostLDPCChunkSymbols, tempL, R2, R2ReducedCopy, strParameters, encodedData, currentColumnIndex, cols, stopState, maxColLength, quotient, selectedEmptyNodeIndex, ueNetDev, gNbNetDev, numberofRoundforBuffer, ipInterfs, staInterface, servPort, apWifiNode, ueIpIface, remoteHost, inputFiles, aliveLDPCStorageNodes, wifiHelper, maxColLength, repairedFile);	
	fspr = FakeSecondPhaseV2(currentLostLDPCChunkSymbols, tempL, R2, R2ReducedCopy, strParameters, encodedData, currentColumnIndex, cols, stopState, maxColLength, quotient, aliveLDPCStorageNodes);
	helperNodes2 = fspr.helperNodes;
	currentHelperNodeIndexes2 = fspr.currentHelperNodeIndexes;
	failedSymbolIDsForRepairFromBS = fspr.failedSymbolIDsForRepairFromBS;
	//strParameters = fspr.strParameters;

	allHelperNodeIndexes.insert(allHelperNodeIndexes.end(), currentHelperNodeIndexes2.begin(), currentHelperNodeIndexes2.end());
	sort(allHelperNodeIndexes.begin(), allHelperNodeIndexes.end());
	tempIt = unique(allHelperNodeIndexes.begin(), allHelperNodeIndexes.end());
	allHelperNodeIndexes.resize(distance(allHelperNodeIndexes.begin(), tempIt));

	helperNodes.insert(helperNodes.end(), helperNodes2.begin(), helperNodes2.end());
	sort(helperNodes.begin(), helperNodes.end());
	tempIt = unique(helperNodes.begin(), helperNodes.end());
	helperNodes.resize(distance(helperNodes.begin(), tempIt));

	//--------------------------------------------------------------------------

	//std::vector<Ptr<UENodeApp>> helperNodeApps(helperNodes.size());
	UENodeApp* helperNodeApps[helperNodes.size()];

	//cout << "We are at the beginning of HELPER NODE APPS" << endl;
	//cout << "Size of helperNodes: " << helperNodes.size() << endl;
	// HELPER NODE APPS-------------------------------------
	for (size_t h = 0; h < helperNodes.size(); h++)
	{
		//Ptr<UENodeApp> currenthelperNodeApps = CreateObject<UENodeApp>();
		//helperNodeApps[h] = CreateObject<UENodeApp>();
		cout<<"helperNodes[h]"<<helperNodes[h]<<endl;
		helperNodeApps[h] = new UENodeApp();
	}
	//cout << "We are here 0 HELPER NODE APPS" << endl;

	cout << "helperNodes: ";
    for(size_t i = 0; i < helperNodes.size(); i++)
        cout << helperNodes[i] << " ";
    cout << endl;

    cout << "aliveLDPCStorageNodes: ";
    for(size_t i = 0; i < aliveLDPCStorageNodes.size(); i++)
        cout << aliveLDPCStorageNodes[i] << " ";
    cout << endl;

    for(size_t i = 0; i < inputFiles.size(); i++)
    {
        cout << "inputFiles[i]: " << inputFiles[i].c_str() << endl;
    }
	cout << endl;

	cout << "selectedEmptyNodeLogicalIndex (# of availableLDPCStorageNodes + # of index): " << selectedEmptyNodeLogicalIndex << endl;
	
	int servPort2;
	for (size_t h = 0; h < helperNodes.size(); h++)
	{
		for(size_t i = 0; i < aliveLDPCStorageNodes.size(); i++)
		{
			if(aliveLDPCStorageNodes[i] == helperNodes[h])
			{
				selectedHelperNodeIndex = helperNodes[h]; // aliveLDPCStorageNodes[i];  
				selectedHelperNodeLogicalIndex = i;
				break;
			}
		}
		cout << "selectedHelperNodeIndex: " << selectedHelperNodeIndex << endl;
		cout << "selectedHelperNodeLogicalIndex: " << selectedHelperNodeLogicalIndex << endl;
		//---------------------------------------------------------
		// staWifiNode1 = ueNodes.Get(selectedHelperNodeIndex);  // senderNode
		// staWifiNode2 = ueNodes.Get(selectedEmptyNodeIndex);  //  receiverNode
       cout << "here1!!\n";
		// staWifiNode1 = ueNodes.Get(selectedEmptyNodeIndex);  // senderNode
		staWifiNode1 = ueNodes.Get(selectedEmptyNodeLogicalIndex);  // senderNode 
       cout << "here2!!\n";
		// staWifiNode2 = ueNodes.Get(selectedHelperNodeIndex);  //  receiverNode
		// staWifiNode2 = ueNodes.Get(selectedHelperNodeLogicalIndex);  //  receiverNode
		staWifiNode2 = ueNodes.Get(h);  //  receiverNode
        cout << "here3!! ueNodes.GetN()"<<ueNodes.GetN()<<"\n";
		// Elif hocanın eklediği bölüm
		// Ptr<Ipv4> ipv4 = ueNodes.Get(selectedHelperNodeIndex)->GetObject<Ipv4> ();
		// Ptr<Ipv4> ipv4 = ueNodes.Get(selectedHelperNodeLogicalIndex)->GetObject<Ipv4> ();
		Ptr<Ipv4> ipv4 = ueNodes.Get(h)->GetObject<Ipv4> (); // h selectedHelperNodeIndex'in yerine eklendi
        cout << "herex!! ipv4->GetNInterfaces()"<<ipv4->GetNInterfaces()<<endl;
		Ipv4InterfaceAddress iaddr = ipv4->GetAddress (2,0); 
        // cout<<"NODE ID:"<<receiverNode->GetId()<<"with adress"<<iaddr.GetLocal ();
	    cout << "herey!!\n";
		receiverAddress =iaddr.GetLocal ();

		cout << "here4!!\n";
	    // senderAddress= ueIpIface.GetAddress (selectedEmptyNodeIndex);

	    //Elif hocanın eklediği kısım
		Ptr<Ipv4> ipv42 = ueNodes.Get(selectedEmptyNodeLogicalIndex)->GetObject<Ipv4> (); // selectedEmptyNodeLogicalIndex olarak değiştirildi selectedEmptyNodeIndex
		 cout << "here4.1!! ipv42->GetNInterfaces()"<<ipv42->GetNInterfaces()<<endl;
		
		Ipv4InterfaceAddress iaddr2 = ipv42->GetAddress (2,0); 
		senderAddress=iaddr2.GetLocal (); 
	    // senderAddress= ueIpIface.GetAddress (selectedEmptyNodeLogicalIndex); // Bir üstteki eklendiği için kapatıldı
        cout << "here5!!\n";
	    // Elif hocanın eklediği kısım
	    // int servPort2 = servPort+ueNodes.Get(selectedEmptyNodeIndex)->GetId()+ueNodes.Get(selectedHelperNodeIndex)->GetId(); // orijinal hali
	    servPort2 = servPort + ueNodes.Get(selectedEmptyNodeLogicalIndex)->GetId() + ueNodes.Get(h)->GetId();
	    // servPort2 = servPort + ueNodes.Get(h)->GetId();

		// senderAddress = ueIpIface.GetAddress (selectedHelperNodeIndex);
		// receiverAddress = ueIpIface.GetAddress (selectedEmptyNodeIndex);

		//cout << "We are here 0_1 HELPER NODE APPS before Setup in LDPCSingleRepairAlgorithmV1NodeContainer" << endl;
		helperNodeApps[h]->Setup(staWifiNode1, staWifiNode2, senderAddress, receiverAddress, servPort2, foundOne, repairedFile, totalHelperFiles, cols, nodeStr, ueIpIface, inputFiles, selectedEmptyNodeIndex, selectedHelperNodeIndex, quotient, tempUsedEmptyNodeforRepair, baseStation, failedSymbolIDsForRepairFromBS, maxColLength, R1, R2, L, helperNodes, numberofRoundforBuffer, currentLostLDPCChunkSymbols, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, ueNodes, remoteHost, internetIpIfaces, aliveLDPCStorageNodes, allHelperNodeIndexes, selectedEmptyNodeLogicalIndex,selectedHelperNodeLogicalIndex);
		//cout << "We are here 0_1 HELPER NODE APPS after Setup in LDPCSingleRepairAlgorithmV1NodeContainer" << endl;
		//helperNodeApps[h].Setup(staWifiNode1, staWifiNode2, senderAddress, receiverAddress, servPort, foundOne, repairedFile, totalHelperFiles, cols, nodeStr, ueIpIface, inputFiles, selectedEmptyNodeIndex, selectedHelperNodeIndex, quotient, tempUsedEmptyNodeforRepair, baseStation, failedSymbolIDsForRepairFromBS, maxColLength, R1, R2, L, helperNodes, numberofRoundforBuffer, currentLostLDPCChunkSymbols, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, ueNodes, remoteHost, internetIpIfaces, aliveLDPCStorageNodes, allHelperNodeIndexes);
		cout << "here6!!\n";
		// ueNodes.Get(selectedHelperNodeIndex)->AddApplication(helperNodeApps[h]);
		// ueNodes.Get(selectedHelperNodeLogicalIndex)->AddApplication(helperNodeApps[h]);
		
		ueNodes.Get(h)->AddApplication(helperNodeApps[h]);
		cout<<"ueNodes.Get(h).GetId()"<<ueNodes.Get(h)->GetId()<<"\n";
	}
	cout<<"End \n";
	// END OF HELPER NODE APPS-------------------------------------

	if(  failedSymbolIDsForRepairFromBS.size() > 0)
	{
		//
		
		cout << "We are at the beginning of BS NODE APP in LDPCSingleRepairAlgorithmV1NodeContainer" << endl;
		// BS NODE APP*********************

		// Elif hocanın eklediği bölüm
		// Ptr<Ipv4> ipv4 = ueNodes.Get(selectedHelperNodeIndex)->GetObject<Ipv4> ();//????
		// Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
		// // cout<<"NODE ID:"<<receiverNode->GetId()<<"with adress"<<iaddr.GetLocal ();
		// receiverAddress =iaddr.GetLocal ();
		// senderAddress = internetIpIfaces.GetAddress(0);
		// staWifiNode1 = remoteHost; //  receiverNode

		// Benim eklediğim bölüm
		cout << "We are BS before  remoteHost->GetObject remoteHost->GetId()"<<remoteHost->GetId()<<endl;
		Ptr<Ipv4> ipv4 = remoteHost->GetObject<Ipv4> ();//????
		cout << "We are BS after  remoteHost->GetObject "<<endl;
		Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
		// cout<<"NODE ID:"<<receiverNode->GetId()<<"with adress"<<iaddr.GetLocal ();
		cout << "We are BS before  iaddr.GetLocal  "<<endl;
		receiverAddress =iaddr.GetLocal ();
		cout << "We are BS after  iaddr.GetLocal  ueIpIface.GetN()  "<<ueIpIface.GetN()<<" selectedEmptyNodeIndex"<<selectedEmptyNodeIndex<<endl;
		// senderAddress= ueIpIface.GetAddress (selectedEmptyNodeIndex);
		//senderAddress= ueIpIface.GetAddress (selectedEmptyNodeIndex);
       
	    Ptr<Ipv4> ipv42 = ueNodes.Get(selectedEmptyNodeLogicalIndex)->GetObject<Ipv4> (); // selectedEmptyNodeLogicalIndex olarak değiştirildi selectedEmptyNodeIndex
		Ipv4InterfaceAddress iaddr2 = ipv42->GetAddress (1,0); 
		senderAddress=iaddr2.GetLocal (); 
		cout<<"senderAddress"<<senderAddress<<endl;




		cout << "We are BS after  ueIpIface.GetAddress (selectedEmptyNodeIndex)  "<<endl;

		// Elif hocanın değiştirdiği kısım
		// int servPort2 = servPort+ueNodes.Get(selectedEmptyNodeIndex)->GetId()+ueNodes.Get(selectedHelperNodeIndex)->GetId(); // orijinali
		servPort2 = servPort + ueNodes.Get(selectedEmptyNodeLogicalIndex)->GetId() +remoteHost->GetId(); //remoteHost->GetId(); 
		// servPort2 = poai + remoteHost->GetId();
        cout << "We are BS after  servPort2  "<<endl;

		// staWifiNode1 = ueNodes.Get (selectedEmptyNodeIndex);  // senderNode
		staWifiNode1 = ueNodes.Get (selectedEmptyNodeLogicalIndex);  // senderNode
		staWifiNode2 = remoteHost; // receiverNode 
        cout << "We are before bsAPP "<<endl;
		BSApp* bsApp = new BSApp();
		cout << "We are BS before  bsApp->Setup(  "<<endl;
		bsApp->Setup(staWifiNode1, staWifiNode2, senderAddress, receiverAddress, servPort2, foundOne, repairedFile, totalHelperFiles, cols, nodeStr, ueIpIface, inputFiles, selectedEmptyNodeIndex, selectedHelperNodeIndex, quotient, tempUsedEmptyNodeforRepair, baseStation, failedSymbolIDsForRepairFromBS, maxColLength, R1, R2, L, helperNodes, numberofRoundforBuffer, currentLostLDPCChunkSymbols, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, ueNodes, remoteHost, internetIpIfaces, aliveLDPCStorageNodes, allHelperNodeIndexes, selectedEmptyNodeLogicalIndex);
		//cout << "We are here BS NODE APP after Setup in LDPCSingleRepairAlgorithmV1NodeContainer" << endl;
		cout << "We are BS after  bsApp->Setup(  "<<endl;
		remoteHost->AddApplication(bsApp);
		//servPort = servPort + 1;
		// END OF BS NODE APP*********************
	}
	else
    	cout << "There is no need for BS.!!" << endl << endl;

	//cout << "We are at the beginning of NEW COMER NODE APP in LDPCSingleRepairAlgorithmV1NodeContainer" << endl;
	// NEW COMER NODE APP---------------------

    // Elif hocanın eklediği bölüm
	// Ptr<Ipv4> ipv4 = ueNodes.Get(selectedHelperNodeIndex)->GetObject<Ipv4> ();
	// Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0); 
	// receiverAddress =iaddr.GetLocal ();

	// staWifiNode1 = ueNodes.Get(selectedEmptyNodeIndex);  // senderNode
	//staWifiNode2 = ueNodes.Get(selectedHelperNodeIndex);  //  receiverNode
	//cout << "Here 1 NEW COMER NODE APP in LDPCSingleRepairAlgorithmV1NodeContainer" << endl;
	NewComerNodeApp* newComerNodeApp = new NewComerNodeApp();
	newComerNodeApp->Setup (foundOne, repairedFile, totalHelperFiles, cols, nodeStr, ueIpIface, inputFiles, selectedEmptyNodeIndex, quotient, tempUsedEmptyNodeforRepair, baseStation, failedSymbolIDsForRepairFromBS, maxColLength, R1, R2, L, helperNodes, numberofRoundforBuffer, currentLostLDPCChunkSymbols, strParameters, unrepairedSymbolsfromNodes, unrepairedSymbolsfromBS, allEquationsR2, ueNodes, remoteHost, internetIpIfaces, aliveLDPCStorageNodes, allHelperNodeIndexes, selectedEmptyNodeLogicalIndex);

	// ueNodes.Get(selectedEmptyNodeIndex)->AddApplication(newComerNodeApp);
	ueNodes.Get(selectedEmptyNodeLogicalIndex)->AddApplication(newComerNodeApp);
	//Simulator::Stop (Seconds (10));
    //Simulator::Run ();
	

	//Simulator::Stop (Seconds (10.0));
	//Simulator::Destroy();
    cout << "Here 4 in LDPCSingleRepairAlgorithmV1NodeContainer after Simulator::Stop" << endl;
    // ();
    //exit(0);


// Print per flow statistics
//This is after Simulator::Run() and assuming monitor is Ptr<FlowMonitor> monitor = flowmon.InstallAll();

//flowMonitor->CheckForLostPackets (); 
//Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowHelper.GetClassifier ());
//std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats ();
//FILE * fp=fopen("ResultsWithoutBS.txt","wb+");   
//fprintf(fp, "Flow ID: \t t.sourceAddress \t t.destinationAddress \t iter->second.txPackets \t  iter->second.rxPackets \t Time \t Throughput ");
//ofstream MyFile2;
//MyFile2.open("ResultsWithBS.txt", std::ios_base::app);
//ofstream MyFile;
//MyFile.open("ResultsWithoutBS.txt", std::ios_base::app);

//Ptr<Ipv4> ipv4 = remoteHost->GetObject<Ipv4> ();//????
//cout << "We are BS after  remoteHost->GetObject "<<endl;
//Ipv4InterfaceAddress remoteAdress = ipv4->GetAddress (1,0); 
//for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator iter = stats.begin (); iter != stats.end (); ++iter)
  //{
         // Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (iter->first);
 	     // NS_LOG_UNCOND("Flow ID: " << iter->first << " Src Addr " << t.sourceAddress << " Dst Addr " << t.destinationAddress);
    	 // NS_LOG_UNCOND("Tx Packets = " << iter->second.txPackets);
    	 // NS_LOG_UNCOND("Rx Packets = " << iter->second.rxPackets);
		 // NS_LOG_UNCOND("Time = " << (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()));
    	 // NS_LOG_UNCOND("Throughput: " << iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024  << " Kbps");
          //MyFile<< iter->first<<"\t"<<t.sourceAddress<<"\t"<<t.destinationAddress<<"\t"<<iter->second.txPackets<<"\t"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024 <<endl;
		 // if (t.sourceAddress==remoteAdress.GetLocal() || t.destinationAddress==remoteAdress.GetLocal()){
 
           //    MyFile2<< iter->first<<"\t"<<t.sourceAddress<<"\t"<<t.destinationAddress<<"\t"<<iter->second.txPackets<<"\t"<<(iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds())<<"\t"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024 <<endl;

		  //}
		  //else
            //   MyFile<< iter->first<<"\t"<<t.sourceAddress<<"\t"<<t.destinationAddress<<"\t"<<iter->second.txPackets<<"\t"<<(iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds())<<"\t"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024 <<endl;

		 
		 // fwrite(&bufferStruct1, sizeof(std::uint8_t), sizeof(totalHelperFiles), fileTobeWritten);
         // fprintf(fp, "%d\t%s\t%s\t%d\t%d\t%e\n", iter->first, t.sourceAddress.Print() , std::to_string(t.destinationAddress), iter->second.txPackets,iter->second.rxPackets,((iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024));
         //fprintf(fp, "%d\t%d\t%d\t%e\n", iter->first , iter->second.txPackets,iter->second.rxPackets,((iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024));
   
 //}
 //fclose(fp);
	// FILE * fileTobeRead;
	// struct strP strParametersFromFile;
	// std::string file = "scratch/testFolder/files/returnFileFromNewComerToBS.bin";
 //    if((fileTobeRead = fopen(file,"r")) == NULL)  
 //        printf("Unable to open file to read\n");
 //    else
 //    	fread(&strParametersFromFile, sizeof(struct strP), 1, fileTobeRead);
 //    strParameters = strParametersFromFile;

	// Create and open a text file
	//ofstream MyFile("filename.txt");

	// Write to the file
	//MyFile << "Files can be tricky, but it is fun enough!";

	// Close the file
	//MyFile.close();
	//MyFile2.close();

	strParameters.usedNodes = inputFiles;
	sraV1Local.totalHelperFiles = totalHelperFiles;
	sraV1Local.nodeStr = nodeStr;
	sraV1Local.strParameters = strParameters;
	sraV1Local.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	sraV1Local.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	cout<<"At the end of LDPCSingleRepair"<<"\n";
	//sraV1Local.newcomerapp = newComerNodeApp;
	//sraV1Local.ueapps= helperNodeApps;
    //exit(0);
	return sraV1Local;
}