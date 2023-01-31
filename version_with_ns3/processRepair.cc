#include "userDefinedFunctions.h"
#include "LDPCSingleRepairAlgorithmV1NodeContainer.h"//"userDefinedFunctions3.h"
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <ctime> 
#include <iostream>
#include <string> 
#include <stdio.h> 
//#include "ns3/mobility-helper.h"

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
//#include "NewComerNodeApp.h"
//#include "UENodeApp.h"
//#include "BSApp.h" 
using namespace std;
using namespace ns3;

typedef struct repairReturns Struct;
Ptr<FlowMonitor> flowMonitor;
FlowMonitorHelper flowHelper;
void printResults(Ptr<Node> remoteHost ,int lostStorageCount,int bsUSed);
//Struct processRepair(std::vector<std::vector<int>> Hsys, std::vector<struct ns> nodeStr, int counterLeavingNodes, std::vector<int> leavingNodes, int numberofLDPCStorageNodes, int numberofInitialLDPCStorageNodes, double baseStationSize, std::vector<int> ldpcFileSizes, struct strP strParameters, struct strP strParameters2, int numberofRoundforBuffer, double blockSize, std::vector<int> aliveLDPCStorageNodes)
Struct processRepair(std::vector<std::vector<int>> Hsys, std::vector<struct ns> nodeStr, int counterLeavingNodes, std::vector<int> leavingNodes, int numberofLDPCStorageNodes, int numberofInitialLDPCStorageNodes, double baseStationSize, std::vector<int> ldpcFileSizes, struct strP strParameters, struct strP strParameters2, int numberofRoundforBuffer, double blockSize, std::vector<int> aliveLDPCStorageNodes, NodeContainer gNbNodes, NodeContainer ueNodes, InternetStackHelper internet, Ptr<Node> apWifiNode, MobilityHelper mobility, Ipv4AddressHelper address, WifiHelper wifiHelper, Ipv4InterfaceContainer ueIpIface, Ipv4InterfaceContainer internetIpIfaces, Ptr<Node> remoteHost)
{
	Struct rrLocal;	
	struct singleRepairAlgorithmV1Returns sAV1R;
	//struct singleRepairAlgorithmV1Returns * SrAV;
	int isMultipleRepair = 0;
	std::vector<string> totalHelperFiles;
	std::vector<string> totalHelperFiles2;	
	std::vector<int> availableEmptyNodes; // DETERMINING EMPTY NODES IN THE CELL
	std::vector<int> availableLDPCStorageNodes;
	std::vector<int> lostLDPCChunkSymbols;
	std::vector<int> leavingLDPCStorageNodes;
	std::vector<int> selectedEmptyNodes;
	int val;
	int upper;
	int start;
	int temp;
	std::vector<int>::iterator it;
	std::vector<ns> nodeStr2;
	std::vector<int> aliveLDPCStorageNodes2;
	time_t startTimeLDPCRepairGeneral, endTimeLDPCRepairGeneral;
	std::vector<int> found;
	std::vector<int> logicalIDs;
	std::vector<int> sortedLeavingLDPCStorageNodes;
	int sortValue;
	std::vector<string> lostFilesLDPC;
	std::vector<string> repairedFiles;
	string tempS1, tempS2;
	time_t startTimeLDPCRepair, endTimeLDPCRepair;
	[[maybe_unused]] double elapsedTimeLDPCRepairGeneral;
	[[maybe_unused]] int ex;
	int upper2;
	int startP;
	std::vector<int> currentLostSymbols;
	[[maybe_unused]] string repairedFile;
	[[maybe_unused]] int foundOne;
	[[maybe_unused]] double elapsedTimeLDPCRepair;
	std::vector<string>::iterator it2;
	string current_file;
	//string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/files/";
	string root_directory = "scratch/testFolder/files/";
	//string root_directory = "scratch/files/";
	[[maybe_unused]] int rows = (int)Hsys.size();
	int cols = (int)Hsys[0].size();
	int quotient = ceil((double)cols / (double)numberofInitialLDPCStorageNodes);
	[[maybe_unused]] int maxColLength = (numberofInitialLDPCStorageNodes - 1)*quotient + quotient;
	FILE *bookofAccountID;
	[[maybe_unused]] int selectedLostNodeIndex;
	[[maybe_unused]] int selectedEmptyNodeIndex, selectedEmptyNodeLogicalIndex;
	[[maybe_unused]] int selectedTempEmptyNodeIndex;
	string tempUsedEmptyNodeforRepair;
	Address defaultAddress;

	for (size_t j = 0; j < nodeStr.size(); j++)
	{
		if (nodeStr[j].isLive == 1)
		{
			if (nodeStr[j].encodingType == 0)
				// DETERMINING AVAILABLE EMPTY STORAGE NODES IN THE CELL
				availableEmptyNodes.push_back(j);
			else
			{				
				// DETERMINING AVAILABLE LDPC STORAGE NODES IN THE CELL
				if (nodeStr[j].encodingType == 1)
					availableLDPCStorageNodes.push_back(j);
			}
		}
	}

	cout << "size of availableEmptyNodes in processRepair: " << availableEmptyNodes.size() << endl;
    cout << "size of availableLDPCStorageNodes in processRepair: " << availableLDPCStorageNodes.size() << endl;

	temp = rand() % (int)availableEmptyNodes.size();
	selectedTempEmptyNodeIndex = availableEmptyNodes[temp];
	// availableEmptyNodes.erase(availableEmptyNodes.begin()+temp);
	// tempS2 = "nodeFile";
	// tempS2.append(to_string(nodeStr[selectedTempEmptyNodeIndex].nodeID));
	// tempS2.append(".bin");
	tempS2 = "tempNodeFile.bin";
	tempUsedEmptyNodeforRepair = root_directory + tempS2;
	
	for (int i = 0; i < counterLeavingNodes; i++)
	{
		val = leavingNodes[i];
		if (nodeStr[val].encodingType == 1)
		{
			leavingLDPCStorageNodes.push_back(val);
			//upper = (nodeStr[val].logicalNodeID - 1)*quotient + quotient;
			upper = (nodeStr[val].logicalNodeID)*quotient + quotient - 1;
			if (upper>cols) 
				upper = cols;
			//start = (nodeStr[val].logicalNodeID - 1)*quotient + 1;
			start = (nodeStr[val].logicalNodeID)*quotient + 1 - 1;
			for (int tInd = start; tInd <= upper; tInd++)
			{
				lostLDPCChunkSymbols.push_back(tInd);
			}
		}
		// if (availableEmptyNodes.empty() == 0)
		// {
		// 	// EMPTY NODES ARE SELECTED FROM ALL EMPTY NODES IN THE CELL
		// 	// std::mt19937_64 gen{ std::random_device()() };
		// 	// std::uniform_real_distribution<int> dis{ 0, (int)availableEmptyNodes.size() };
		// 	// int temp = dis(gen);
		// 	temp = rand() % (int)availableEmptyNodes.size(); //ranges from 0 to (int)availableEmptyNodes.size()-1
		// 	//temp = randperm(availableEmptyNodes.size(), 1);
		// 	selectedEmptyNodes.push_back(availableEmptyNodes[temp]);
		// 	// DISCARDING THE USED NODE FROM THE AVAILABLE EMPTY NODES
		// 	// cout << "size of availableEmptyNodes before erase operation in processRepair: " << availableEmptyNodes.size() << endl;
		// 	availableEmptyNodes.erase(availableEmptyNodes.begin()+temp);
		// }
	}
	int uniqueRandoms = 0;
	std::vector<int> randomIndexes{};
	while(uniqueRandoms < counterLeavingNodes)
	{
		temp = rand() % (int)availableEmptyNodes.size(); //ranges from 0 to (int)availableEmptyNodes.size()-1
		if(std::find(randomIndexes.begin(), randomIndexes.end(), temp) == randomIndexes.end()) /* randomIndexes does not contain temp */
		{
			selectedEmptyNodes.push_back(availableEmptyNodes[temp]);
			uniqueRandoms = uniqueRandoms + 1;
			randomIndexes.push_back(temp);
		}
	}

	// cout << "counterLeavingNodes: " << counterLeavingNodes << endl;
	cout << "size of leavingNodes: " << leavingNodes.size() << endl;
	cout << "size of leavingLDPCStorageNodes: " << leavingLDPCStorageNodes.size() << endl;
	cout << "size of availableEmptyNodes: " << availableEmptyNodes.size() << endl;
	cout << "size of availableLDPCStorageNodes: " << availableLDPCStorageNodes.size() << endl;
	cout << "size of numberofLDPCStorageNodes: " << numberofLDPCStorageNodes << endl;
	cout << "size of numberofInitialLDPCStorageNodes: " << numberofInitialLDPCStorageNodes << endl;
	cout << "size of ueNodes (availableEmptyNodes + availableLDPCStorageNodes): " << ueNodes.GetN() << endl;

	cout << "leavingNodes: ";
    for(size_t i = 0; i < leavingNodes.size(); i++)
        cout << leavingNodes[i] << " ";
    cout << endl;

    cout << "leavingLDPCStorageNodes: ";
    for(size_t i = 0; i < leavingLDPCStorageNodes.size(); i++)
        cout << leavingLDPCStorageNodes[i] << " ";
    cout << endl;

    cout << "availableEmptyNodes: ";
    for(size_t i = 0; i < availableEmptyNodes.size(); i++)
        cout << availableEmptyNodes[i] << " ";
    cout << endl;

    cout << "availableLDPCStorageNodes: ";
    for(size_t i = 0; i < availableLDPCStorageNodes.size(); i++)
        cout << availableLDPCStorageNodes[i] << " ";
    cout << endl;

	cout << "aliveLDPCStorageNodes: ";
    for(size_t i = 0; i < aliveLDPCStorageNodes.size(); i++)
        cout << aliveLDPCStorageNodes[i] << " ";
    cout << endl;

    cout << "selectedEmptyNodes: ";
    for(size_t i = 0; i < selectedEmptyNodes.size(); i++)
        cout << selectedEmptyNodes[i] << " ";
    cout << endl;

	// if (selectedEmptyNodes.size() != ueNodes.GetN())
	// 	cout << "Sizes of selectedEmptyNodes and ueNodes are different" << endl;
	
	nodeStr2 = nodeStr;
	aliveLDPCStorageNodes2 = aliveLDPCStorageNodes;

	sort(lostLDPCChunkSymbols.begin(), lostLDPCChunkSymbols.end());	
	it = unique(lostLDPCChunkSymbols.begin(), lostLDPCChunkSymbols.end());
	lostLDPCChunkSymbols.resize(distance(lostLDPCChunkSymbols.begin(), it));
    // = (struct singleRepairAlgorithmV1Returns *) malloc(sizeof(struct singleRepairAlgorithmV1Returns)*leavingLDPCStorageNodes.size());
	if (selectedEmptyNodes.empty() == 0 && lostLDPCChunkSymbols.empty() == 0)
	{
		if (selectedEmptyNodes.size() >= leavingLDPCStorageNodes.size())
		{
			// EXECUTING LDPC REPAIR TRANSACTION
			if (leavingLDPCStorageNodes.size() > 0)
			{			
				startTimeLDPCRepairGeneral = time(0);

				for (size_t ff = 0; ff < aliveLDPCStorageNodes.size(); ff++)
				{
					if (aliveLDPCStorageNodes[ff] == -1)
						found.push_back(ff);
				}

				for (size_t j = 0; j < leavingLDPCStorageNodes.size(); j++)
					logicalIDs.push_back(nodeStr[leavingLDPCStorageNodes[j]].logicalNodeID);
					//logicalIDs[j] = nodeStr[leavingLDPCStorageNodes[j]].logicalNodeID;

				for (size_t j = 0; j < found.size(); j++)
				{
					sortValue = -1;
					for (size_t ff = 0; ff < logicalIDs.size(); ff++)
					{
						if (found[j] == logicalIDs[ff])
						{
							sortValue = ff;
							break;
						}
					}
					if (sortValue != -1)
						sortedLeavingLDPCStorageNodes.push_back(nodeStr[leavingLDPCStorageNodes[sortValue]].nodeID);
				}
				
				for (size_t t = 0; t < sortedLeavingLDPCStorageNodes.size(); t++)
					lostFilesLDPC.push_back(nodeStr[sortedLeavingLDPCStorageNodes[t]].fileName);  // Which files lost(e.g nodeFile2.bin, nodeFile4.bim, etc.)
				
				for (size_t i = 0; i < leavingLDPCStorageNodes.size(); i++)
				{
					tempS1 = "nodeFile";
					tempS1.append(to_string(nodeStr[selectedEmptyNodes[i]].nodeID));
					tempS1.append(".bin");
					repairedFiles.push_back(root_directory + tempS1);
					// nodeStr[selectedEmptyNodes[i]].fileName = repairedFiles[i];
					nodeStr[selectedEmptyNodes[i]].fileName = tempS1;
				}
					
				endTimeLDPCRepairGeneral = time(0);
				elapsedTimeLDPCRepairGeneral = difftime(startTimeLDPCRepairGeneral, endTimeLDPCRepairGeneral);			
				startTimeLDPCRepair = time(0);
				//Ptr<LDPCSingleRepairAlgorithmApp> newComerNodeApp[leavingLDPCStorageNodes.size()];

				//REPAIR PROCESS IN HERE
				for (size_t i = 0; i<leavingLDPCStorageNodes.size();i++)
				{
					//upper2 = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID - 1)*quotient + quotient;
					upper2 = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID)*quotient + quotient - 1;
					if (upper2 > cols)
						upper2 = cols-1;
					//startP = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID - 1)*quotient + 1;
					startP = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID)*quotient + 1 - 1;
 
					for (int tt = startP; tt <= upper2; tt++)
						currentLostSymbols.push_back(tt);
					repairedFile = repairedFiles[i];
					foundOne = found[i];
					selectedLostNodeIndex = sortedLeavingLDPCStorageNodes[i];
					selectedEmptyNodeIndex = selectedEmptyNodes[i];

					// Eklediğim kısım
					for(size_t i = 0; i < availableEmptyNodes.size(); i++)
					{
						if (availableEmptyNodes[i] == selectedEmptyNodeIndex)
						{
							selectedEmptyNodeLogicalIndex = availableLDPCStorageNodes.size() + i;
							break;
						}
					}

					cout << "selectedEmptyNodeIndex: " << selectedEmptyNodeIndex << endl;
					cout << "selectedEmptyNodeLogicalIndex (# of availableLDPCStorageNodes + # of index): " << selectedEmptyNodeLogicalIndex << endl;
					cout << "availableEmptyNodes[i]: " << availableEmptyNodes[i] << endl;
					cout << "i: " << i << endl;
					cout << "availableLDPCStorageNodes.size(): " << availableLDPCStorageNodes.size() << endl;
					cout << "We are in processRepair before LDPCSingleRepairAlgorithmV1" << endl;

					//sAV1R = LDPCSingleRepairAlgorithmV1NodeContainer(foundOne, repairedFile, currentLostSymbols, totalHelperFiles, cols, quotient, Hsys, nodeStr, lostLDPCChunkSymbols, strParameters, numberofRoundforBuffer, aliveLDPCStorageNodes, blockSize, maxColLength);
					//SrAV[i] = 
					sAV1R = LDPCSingleRepairAlgorithmV1NodeContainer(foundOne, repairedFile, currentLostSymbols, totalHelperFiles, cols, quotient, Hsys, nodeStr, lostLDPCChunkSymbols, strParameters, numberofRoundforBuffer, aliveLDPCStorageNodes, blockSize, maxColLength, gNbNodes, ueNodes, selectedLostNodeIndex, selectedEmptyNodeIndex, internet, apWifiNode, mobility, address, internetIpIfaces, ueIpIface, remoteHost, wifiHelper, tempUsedEmptyNodeforRepair, selectedTempEmptyNodeIndex, selectedEmptyNodeLogicalIndex);
                    //sAV1R =SrAV[i];
					totalHelperFiles = sAV1R.totalHelperFiles;
					nodeStr = sAV1R.nodeStr;
					strParameters = sAV1R.strParameters;
					aliveLDPCStorageNodes = sAV1R.aliveLDPCStorageNodes;
					cout << "We are here in processRepair 1" << endl;
					ex = strParameters.numberofReadedSymbolsfromNodesforLDPCRepair;
					cout << "We are here in processRepair 2" << endl;
				}
				

    
    		
	            cout << "Here 5 in LDPCSingleRepairAlgorithmV1NodeContainer after Simulator::Run" << endl;
	//servPort = servPort + 1;
	// END OF NEW COMER NODE APP---------------------
	
    //flowMonitor->SerializeToXmlFile("FlowMonitor2.xml", true, true);

				endTimeLDPCRepair = time(0);
				elapsedTimeLDPCRepair = difftime(startTimeLDPCRepair, endTimeLDPCRepair);
				cout << "We are here in processRepair 2" << endl;
				for (size_t k = 0; k<leavingLDPCStorageNodes.size();k++)
				{
					nodeStr[selectedEmptyNodes[k]].isLive = 1;
					nodeStr[selectedEmptyNodes[k]].encodingType = 1;
					nodeStr[selectedEmptyNodes[k]].logicalNodeID = nodeStr[sortedLeavingLDPCStorageNodes[k]].logicalNodeID;
					aliveLDPCStorageNodes[nodeStr[sortedLeavingLDPCStorageNodes[k]].logicalNodeID] = nodeStr[selectedEmptyNodes[k]].nodeID;
				}
				cout << "We are here in processRepair 3" << endl;
				if ((int)lostLDPCChunkSymbols.size() == cols)
					strParameters.numberofLDPCRepairswithOnlyBaseStation = strParameters.numberofLDPCRepairswithOnlyBaseStation + 1;
				else
					if (strParameters.numberofReadedSymbolsfromBSforLDPCRepair > 0)
						strParameters.numberofLDPCRepairswithBaseStation = strParameters.numberofLDPCRepairswithBaseStation + 1;
					else
						strParameters.numberofLDPCRepairswithoutBaseStation = strParameters.numberofLDPCRepairswithoutBaseStation + 1;
				cout << "We are here in processRepair 4" << endl;	
				// Unique equivalent in c++
				sort(totalHelperFiles.begin(), totalHelperFiles.end());
				it2 = unique(totalHelperFiles.begin(), totalHelperFiles.end());
				totalHelperFiles.resize(distance(totalHelperFiles.begin(), it2));
				cout << "We are here in processRepair 5" << endl;
				strParameters.numberofLDPCHelpers = totalHelperFiles.size();
				//strParameters.numberofLDPCHelpers = size(unique(totalHelperFiles), 2);
				strParameters.startTimeLDPCRepair = startTimeLDPCRepairGeneral;
				strParameters.endTimeLDPCRepair = endTimeLDPCRepair + endTimeLDPCRepairGeneral;

				current_file = root_directory + "/ledger.txt";
				bookofAccountID = fopen(current_file.c_str(), "a");
				if (bookofAccountID != NULL)
				{
					fprintf(bookofAccountID, "\n Selected empty node(s) for LDPC repair: ");
					for (size_t i = 0; i < repairedFiles.size(); i++)
						fprintf(bookofAccountID, "%s ", repairedFiles[i].c_str());
					fprintf(bookofAccountID, "\n");
					fprintf(bookofAccountID, "\n Leaving LDPC storage node(s): ");
					for (size_t i = 0; i < lostFilesLDPC.size(); i++)
						fprintf(bookofAccountID, "%s ", lostFilesLDPC[i].c_str());
					fprintf(bookofAccountID, "\n");
					fprintf(bookofAccountID, "\n Logical node IDs of leaving LDPC storage node(s): ");
					for (size_t i = 0; i < leavingLDPCStorageNodes.size(); i++)					
						fprintf(bookofAccountID, "%d ", nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID);
					fprintf(bookofAccountID, "\n");
					fclose(bookofAccountID);
				}
				cout << "We are here in processRepair 6" << endl;
			}
			numberofLDPCStorageNodes = numberofLDPCStorageNodes + leavingLDPCStorageNodes.size();
		}
		else
		{
			cout << "There are not sufficient number of available empty nodes to LDPC repair the leaving storage nodes!" << endl;
			//fcloseall();
			exit(0);
		}
		
	}
	else
	{
		cout << "There is no leaving storage nodes!" << endl;
	}
	    Simulator::Stop (Seconds (3.0));
        cout << "Here 5 in process repair after Simulator::Stop" << endl;
	    flowMonitor = flowHelper.InstallAll();
        Simulator::Run ();
		 cout << "Here 5 in process repair after Simulator::Run" << endl;
		printResults( remoteHost,leavingLDPCStorageNodes.size(),strParameters.numberofReadedSymbolsfromBSforLDPCRepair);
		Simulator::Destroy();
		exit(0);
       
	//exit(0);
	// cout << "We are here in processRepair 7" << endl;
	rrLocal.isMultipleRepair = isMultipleRepair;
	rrLocal.nodeStr = nodeStr;
	rrLocal.numberofLDPCStorageNodes = numberofLDPCStorageNodes;
	rrLocal.strParameters = strParameters;
	rrLocal.strParameters2 = strParameters2;
	rrLocal.leavingLDPCStorageNodes = leavingLDPCStorageNodes;	
	rrLocal.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	// cout << "We are here in processRepair 8" << endl
	
	//free(SrAV);
	return rrLocal;
}

void printResults(Ptr<Node> remoteHost, int lostStorageCount, int bsUSed)
{

    flowMonitor->CheckForLostPackets (); 
    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowHelper.GetClassifier ());
    std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats ();
    //FILE * fp=fopen("ResultsWithoutBS.txt","wb+");   
//fprintf(fp, "Flow ID: \t t.sourceAddress \t t.destinationAddress \t iter->second.txPackets \t  iter->second.rxPackets \t Time \t Throughput ");
    ofstream MyFile2;
	ofstream MyFile;
    MyFile2.open("ResultsWithBS.txt", std::ios_base::app);
    MyFile.open("ResultsWithoutBS.txt", std::ios_base::app);

     Ptr<Ipv4> ipv4 = remoteHost->GetObject<Ipv4> ();//????

     Ipv4InterfaceAddress remoteAdress = ipv4->GetAddress (1,0); 
 for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator iter = stats.begin (); iter != stats.end (); ++iter)
   {

         Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (iter->first);
 	     NS_LOG_UNCOND("Flow ID: " << iter->first << " Src Addr " << t.sourceAddress << " Dst Addr " << t.destinationAddress);
    	 NS_LOG_UNCOND("Tx Packets = " << iter->second.txPackets);
    	 NS_LOG_UNCOND("Rx Packets = " << iter->second.rxPackets);
		 // NS_LOG_UNCOND("Time = " << (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()));
    	 // NS_LOG_UNCOND("Throughput: " << iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024  << " Kbps");
          //MyFile<< iter->first<<"\t"<<t.sourceAddress<<"\t"<<t.destinationAddress<<"\t"<<iter->second.txPackets<<"\t"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024 <<endl;
		  if (t.sourceAddress==remoteAdress.GetLocal() || t.destinationAddress==remoteAdress.GetLocal())
               MyFile2<< iter->first<<"\t"<<t.sourceAddress<<"\t"<<t.destinationAddress<<"\t"<<iter->second.txPackets<<"\t"<<iter->second.rxPackets<<"\t"<<(iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds())<<"\t"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024 <<"\t"<<lostStorageCount<<"\t"<<bsUSed<<endl;
		  //}
		  else{
               MyFile<< iter->first<<"\t"<<t.sourceAddress<<"\t"<<t.destinationAddress<<"\t"<<iter->second.txPackets<<"\t"<<iter->second.rxPackets<<"\t"<<(iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds())<<"\t"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024<<"\t"<<lostStorageCount<<"\t"<<bsUSed<<endl;
		  //} <<endl;
               cout<< iter->first<<"\t"<<t.sourceAddress<<"\t"<<t.destinationAddress<<"\t"<<iter->second.txPackets<<"\t"<<iter->second.rxPackets<<"\t"<<(iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds())<<"\t"<<iter->second.rxBytes * 8.0 / (iter->second.timeLastRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSeconds()) / 1024<<"\t"<<lostStorageCount<<"\t"<<bsUSed<<endl;
		  //} <<endl;
 
		  }
 }
 
	MyFile.close();
	MyFile2.close();

}