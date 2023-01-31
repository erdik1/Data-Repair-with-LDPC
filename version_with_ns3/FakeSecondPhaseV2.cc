#include "userDefinedFunctions.h"
//#include "TcpSocketProcesses.h"
//#include "messages.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;
//using namespace ns3;

typedef struct fakeSecondPhaseReturns Struct;

//Struct FakeSecondPhaseV2(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R2, std::vector<std::vector<int>> R2Reduced, struct strP strParameters, std::vector<std::vector<uint8_t>> encodedData, int currentColumnIndex, int cols, int stopState, int maxColLength, int quotient, int selectedEmptyNodeIndex, NetDeviceContainer ueNetDev, NetDeviceContainer gNbNetDev, int numberofRoundforBuffer, Ipv4InterfaceContainer ipInterfs, Ipv4InterfaceContainer staInterface, uint16_t servPort, Ptr<Node> apWifiNode, Ipv4InterfaceContainer ueIpIface, Ptr<Node> remoteHost, std::vector<string> inputFiles, std::vector<int> aliveLDPCStorageNodes, WifiHelper wifiHelper, , int maxColLength, std::string repairedFile)
Struct FakeSecondPhaseV2(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R2, std::vector<std::vector<int>> R2Reduced, struct strP strParameters, std::vector<std::vector<uint8_t>> encodedData, int currentColumnIndex, int cols, int stopState, int maxColLength, int quotient, std::vector<int> aliveLDPCStorageNodes)
{
	Struct sprLocal;
	FILE *baseStationID;
	// string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/";
	string root_directory = "scratch/testFolder/";
	//string root_directory = "scratch/";
	string current_directory = root_directory + "files/";
	string baseStation = current_directory + "baseStation.bin";
	baseStationID = fopen(baseStation.c_str(), "r");

	std::vector<int> currentLostHelpers(R2.size(),0);
	std::vector<int> lostHelperSizes, helperIndexes, helperIndexesReduced, helperIndexesfromBS;
	std::vector<int> R, RReduced, lostHelpers;
	int M, I, failedSymbolID; 
	//int finished;
	[[maybe_unused]] int index;
	//uint8_t read;
	std::vector<int> helperIndexesfromNodes, helperIndexesfromNodesReduced, totalHelperIndexesfromNodes;
	std::vector<int> repairedHelperSymbols{};
	//auto last;
	[[maybe_unused]] int c;
	[[maybe_unused]] int increment;
	//std::vector<uint8_t> temp(encodedData[0].size(), 0);
	std::vector<std::vector<uint8_t>> helperData{};
	int intState;
	//[[maybe_unused]] size_t tempCheckSize = encodedData[0].size();
	//int selectedHelperNodeIndex;
	//uint32_t packetSize = (uint32_t) numberofRoundforBuffer;

	Ptr<Node> staWifiNode1;  // senderNode
	Ptr<Node> staWifiNode2;  // receiverNode
	//uint32_t localWriteSize = 1040;
	//uint8_t locaData[writeSize];
	NodeContainer UesNodesWifi;
	Ipv4InterfaceContainer staInterface;

	std::vector<int> tempL = L;
	std::vector<std::vector<int>> tempR2 = R2;
	std::vector<std::vector<int>> tempR2Reduced = R2Reduced;
	std::vector<int> tempCurrentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
	std::vector<std::vector<uint8_t>> tempEncodedData = encodedData;
	std::vector<int>::iterator tempIt, tempIt2;
	std::vector<int> helperNodes;
	std::vector<int> currentHelperNodeIndexes{};
	std::vector<int> failedSymbolIDsForRepairFromBS{};

	cout << "We are in FakeSecondPhaseV2" << endl;

	// cout << "size of tempL: " << tempL.size() << endl;
	// cout << "tempL: ";
	// for (size_t i = 0; i < tempL.size(); i++)
	// 	cout << tempL[i] << " ";
	// cout << endl;

	while (!tempL.empty())
	{
		//std::vector<int> currentLostHelpers(R2.size(),0);
		//std::fill(currentLostHelpers.begin(), currentLostHelpers.end(), 0);
		//std::vector<int> lostHelperSizes{};
		lostHelperSizes.clear();
		helperIndexes.clear();
		helperIndexesReduced.clear();
		helperIndexesfromBS.clear();

		for (size_t k = 0; k < tempR2.size(); k++)
		{
			// Finding the number of lost symbols in the recovery equations
			for (size_t c = 1; c < tempR2[k].size(); c++)
			{
				for (size_t l = 0; l < tempCurrentLostLDPCChunkSymbols.size(); l++)
				{
					if (tempR2[k][c] == tempCurrentLostLDPCChunkSymbols[l])
						currentLostHelpers.push_back(c);
				}
			}
			lostHelperSizes.push_back(currentLostHelpers.size());
			currentLostHelpers.clear();
			//intersections = ismember(R2(k, 2:end), currentLostLDPCChunkSymbols);
		}

		// cout << "We are in FakeSecondPhaseV2 2" << endl;
		// cout << "size of R2: " << R2.size() << endl;
		// cout << "size of tempR2: " << tempR2.size() << endl;
		// cout << "size of lostHelperSizes: " << lostHelperSizes.size() << endl;
		// cout << endl;

		M = lostHelperSizes[0];
		I = 0;
		for (size_t i = 1; i < lostHelperSizes.size(); i++)
		{
			if (lostHelperSizes[i] < M)
			{
				M = lostHelperSizes[i];
				I = i;
			}
		}

		//[M, I] = min(lostHelperSizes);
		//cout << "We are here in secondPhase 1_2" << endl;
		for (size_t c = 1; c < tempR2[I].size(); c++)
			R.push_back(tempR2[I][c]);
		//R = R2(I, 2:end);

		// cout << "We are in FakeSecondPhaseV2 2_2" << endl;
		// cout << "size of tempR2Reduced: " << tempR2Reduced.size() << endl;
		// cout << "size of R2Reduced: " << R2Reduced.size() << endl;

		for (size_t c = 1; c < tempR2Reduced[I].size(); c++)
			RReduced.push_back(tempR2Reduced[I][c]);  // Reduced helper symbols from
		//RReduced = R2Reduced(I, 2:end);

		failedSymbolID = tempL[I];

		for (size_t c = 0; c < RReduced.size(); c++)
		{
			for (size_t l = 0; l < tempCurrentLostLDPCChunkSymbols.size(); l++)
			{
				if (RReduced[c] == tempCurrentLostLDPCChunkSymbols[l])
					lostHelpers.push_back(c);
			}
		}		

		//intersections = ismember(RReduced, currentLostLDPCChunkSymbols);
		repairedHelperSymbols.clear();
		if (lostHelpers.size() >= 1)
		{
			failedSymbolIDsForRepairFromBS.push_back(failedSymbolID);
			// REPAIR FROM BASE STATION
			// index = 0;
			// finished = 0;
			// servPort = servPort + 1;
			// for (size_t j = currentColumnIndex; j < currentColumnIndex + tempEncodedData[failedSymbolID].size(); j++)
			// {
			// 	//if (fseek(baseStationID, (j - 1)* maxColLength + failedSymbolID - 1, SEEK_SET) == 0)
			// 	if (fseek(baseStationID, j * maxColLength + failedSymbolID , SEEK_SET) == 0)
			// 	{
			// 		size_t result = fread(&read, sizeof(std::uint8_t), 1, baseStationID);
			// 		//cout << "result: " << result << endl;
			// 		if (result == 1)
			// 		{
			// 			tempEncodedData[failedSymbolID][index] = read;
			// 			strParameters.numberofReadedSymbolsfromBSforLDPCRepair = strParameters.numberofReadedSymbolsfromBSforLDPCRepair + 1;

			// 			//---------------------------------------------------------
			// 			TCPSocketProcesses* tcpAppS1 = new HandleMessages(remoteHost, ueNodes.Get(selectedEmptyNodeIndex),ueIpIface.GetAddress (selectedEmptyNodeIndex), servPort);

			// 			// // initialize the tx buffer.
			// 			// size_t lc = 0;
			// 			// while(lc < encodedData[r].size())
			// 			// {
			// 			// 	for(size_t i = 0; i < localWriteSize; ++i)
			// 			// 	{
			// 			//     	locaData[i] = encodedData[failedSymbolID][index];
			// 			//     	lc = lc + 1;
			// 			//     	if (lc >= encodedData[r].size())
			// 			//     		break;
			// 			//     }
			// 			// }
			// 			//memcpy(tcpAppS1.data, encodedData[failedSymbolID][index], 1);
			// 			tcpAppS1.data = tempEncodedData[failedSymbolID][index];

			// 			tcpAppS1->SetReceiverSocket();
		 //   				tcpAppS1->SetSenderSocket();
		 //   				MType messageType = REQUESTREPAIRFROMBS;
   // 				        tcpAppS1->StartFlow(messageType, tempEncodedData);
		 //   				//tcpAppS1->StartFlow();
			// 			//---------------------------------------------------------

			// 			// uint8_t *p = &read;
			// 			// //SendPacketV2(gNbNetDev.Get (0), ueNetDev.Get (selectedEmptyNodeIndex)->GetAddress (), packetSize, p);
			// 			// createSocket_Bind_Listen_Accept_Process(ns3TcpSocket, sinkAddress, gNbNodes, ueNodes, gNbNetDev, ueNetDev, internet, selectedEmptyNodeIndex, ipInterfs, p);
			// 		}
			// 		else
			// 			finished = 1;
			// 	}
			// 	else
			// 		finished = 1;

			// 	if (finished == 1)
			// 	{
			// 		for(size_t columnToDelete=index; columnToDelete<tempEncodedData[failedSymbolID].size(); columnToDelete++)
			// 		{
			// 			for (unsigned i = 0; i < tempEncodedData.size(); ++i)
			// 			{
			// 			  if (tempEncodedData[i].size() > columnToDelete)
			// 			  {
			// 			    tempEncodedData[i].erase(tempEncodedData[i].begin() + columnToDelete);
			// 			  }
			// 			}
			// 		}

			// 		stopState = 1;
			// 		break;
			// 	}
			// 	index = index + 1;
			// }
		}
		else
		{
			// REPAIR FROM NODES
			for (size_t r = 0; r < R.size(); r++)
			{
				// if (R[r] != 0)
				if (R[r] != -1)
					helperIndexes.push_back(r);
			}
			//helperIndexes = R(R(:) ~= 0);
			for (size_t r = 0; r < RReduced.size(); r++)
			{
				if (RReduced[r] != 0)
					helperIndexesReduced.push_back(r);
			}
			//helperIndexesReduced = RReduced(RReduced(:) ~= 0);
			for (size_t c = 0; c < helperIndexes.size(); c++)
			{
				for (size_t l = 0; l < tempCurrentLostLDPCChunkSymbols.size(); l++)
				{
					if (helperIndexes[c] == tempCurrentLostLDPCChunkSymbols[l])
					{
						helperIndexesfromBS.push_back(tempCurrentLostLDPCChunkSymbols[l]);
						break;
					}
				}
			}
			auto last = std::unique(helperIndexesfromBS.begin(), helperIndexesfromBS.end());
			helperIndexesfromBS.erase(last, helperIndexesfromBS.end());
			std::sort(helperIndexesfromBS.begin(), helperIndexesfromBS.end());

			helperIndexesfromNodes.clear();
			for (size_t r = 0; r < helperIndexes.size(); r++) 
			{
				intState = 0;
				for (size_t i = 0; i < helperIndexesfromBS.size(); i++)
				{
					if (helperIndexes[r] == helperIndexesfromBS[i])
					{
						intState = 1;
						break;
					}
				}
				if (intState == 0)
				{
					helperIndexesfromNodes.push_back(helperIndexes[r]);		
					totalHelperIndexesfromNodes.push_back(helperIndexes[r]);		
				}
			}

			if (helperIndexesfromNodes.size() != helperIndexes.size())
				cout << "Error in size(helperIndexesfromNodes)" << endl;

			helperIndexesfromNodesReduced.clear();
			for (size_t r = 0; r < helperIndexesReduced.size(); r++) 
			{
				intState = 0;
				for (size_t i = 0; i < helperIndexesfromBS.size(); i++)
				{
					if (helperIndexesReduced[r] == helperIndexesfromBS[i])
					{
						intState = 1;
						break;
					}
				}
				if (intState == 0)
					helperIndexesfromNodesReduced.push_back(helperIndexesReduced[r]);			
			}
		}

		std::vector<int> tempLL{};
		for (size_t r = 0; r < tempL.size(); r++)
		{
			if (tempL[r] != failedSymbolID)
				tempLL.push_back(tempL[r]);
		}
		tempL = tempLL;
		//L = L(L ~= failedSymbolID);
		std::vector<int> tempTempCurrentLostLDPCChunkSymbols{};
		for (size_t r = 0; r < tempCurrentLostLDPCChunkSymbols.size(); r++)
		{
			if (tempCurrentLostLDPCChunkSymbols[r] != failedSymbolID)
				tempTempCurrentLostLDPCChunkSymbols.push_back(r);
		}
		tempCurrentLostLDPCChunkSymbols = tempTempCurrentLostLDPCChunkSymbols;
		//currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols(currentLostLDPCChunkSymbols ~= failedSymbolID);

		tempR2.erase(tempR2.begin() + I);
		//R2(I, :) = [];

		tempR2Reduced.erase(tempR2Reduced.begin() + I);
		//R2Reduced(I, :) = [];
		for (size_t i = 0; i < repairedHelperSymbols.size(); i++)
		{
			int foundIndexHelper;
			for (size_t c = 0; c < tempL.size(); c++)
			{
				if (tempL[c] != repairedHelperSymbols[i])
					foundIndexHelper = c;
			}
			//foundIndexHelper = find(L == repairedHelperSymbols(i));

			tempL.erase(std::remove(tempL.begin(), tempL.end(), tempL[foundIndexHelper]), tempL.end());
			//L(foundIndexHelper) = [];

			tempR2.erase(std::remove(tempR2.begin(), tempR2.end(), tempR2[foundIndexHelper]), tempR2.end());
			//R2(foundIndexHelper, :) = [];

			int foundAllIndexHelper;
			for (size_t c = 0; c < tempCurrentLostLDPCChunkSymbols.size(); c++)
			{
				if (tempCurrentLostLDPCChunkSymbols[c] != repairedHelperSymbols[i])
					foundAllIndexHelper = c;
			}

			tempCurrentLostLDPCChunkSymbols.erase(std::remove(tempCurrentLostLDPCChunkSymbols.begin(), tempCurrentLostLDPCChunkSymbols.end(), tempCurrentLostLDPCChunkSymbols[foundAllIndexHelper]), tempCurrentLostLDPCChunkSymbols.end());
		}
	}

	repairedHelperSymbols.clear();
	lostHelpers.clear();
	currentLostHelpers.clear();
	RReduced.clear();
	R.clear();
	helperIndexesfromNodes.clear();
	helperIndexes.clear();
	helperIndexesfromNodesReduced.clear();

	sort(totalHelperIndexesfromNodes.begin(), totalHelperIndexesfromNodes.end());
	tempIt = unique(totalHelperIndexesfromNodes.begin(), totalHelperIndexesfromNodes.end());
	totalHelperIndexesfromNodes.resize(distance(totalHelperIndexesfromNodes.begin(), tempIt));

	helperNodes.clear();
	int tempNodeIndex;
	for (size_t i = 0; i < totalHelperIndexesfromNodes.size(); i++)
	{
		//helperNodes[i] = totalHelperIndexesfromNodes[i]/quotient;
		tempNodeIndex = (int)(totalHelperIndexesfromNodes[i]/quotient);
		if(aliveLDPCStorageNodes[tempNodeIndex] != -1)
			helperNodes.push_back(tempNodeIndex);
			// helperNodes.push_back(totalHelperIndexesfromNodes[i]/quotient);
	}

	//sort(helperNodes.begin(), helperNodes.end());
	tempIt2 = unique(helperNodes.begin(), helperNodes.end());
	helperNodes.resize(distance(helperNodes.begin(), tempIt2));

	//-------------------------------------------------------------------------------------------------------------------

	//cout << "We are here in secondPhase 2" << endl;
	fclose(baseStationID);
	//currentColumnIndex = currentColumnIndex + encodedData[0].size();
	//sprLocal.encodedData = encodedData;
	//sprLocal.currentColumnIndex = currentColumnIndex;
	sprLocal.helperNodes = helperNodes;
	sprLocal.stopState = stopState;
	sprLocal.currentHelperNodeIndexes = totalHelperIndexesfromNodes;
	sprLocal.failedSymbolIDsForRepairFromBS = failedSymbolIDsForRepairFromBS;
	//sprLocal.strParameters = strParameters;
	cout << "We are at the end of FakeSecondPhaseV2" << endl;
	return sprLocal;
}
