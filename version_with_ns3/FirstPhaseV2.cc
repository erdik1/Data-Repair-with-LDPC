#include "userDefinedFunctions.h"
//#include "TcpSocketProcesses.h"
//#include "messages.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;
//using namespace ns3;

typedef struct firstPhaseReturns Struct;

//Struct FirstPhaseV2(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<uint8_t>> readedDatainBuffer, std::vector<std::vector<int>> allEquationsR2, int quotient, int selectedEmptyNodeIndex, NetDeviceContainer ueNetDev, int numberofRoundforBuffer, uint16_t servPort, MobilityHelper mobility, Ipv4AddressHelper address, std::vector<string> inputFiles, std::vector<int> aliveLDPCStorageNodes, NodeContainer ueNodes, WifiHelper wifiHelper)
Struct FirstPhaseV2(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<uint8_t>> readedDatainBuffer, std::vector<std::vector<int>> allEquationsR2)
{
	Struct fprLocal;
	struct updateRecoveryEquationsReturns urer;
	std::vector<int> selectedEquation, selectedEquationReduced;

	std::vector<int> sortedCurrentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
	std::vector<int> sortedUnrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
	std::sort(sortedCurrentLostLDPCChunkSymbols.begin(), sortedCurrentLostLDPCChunkSymbols.end());
	std::sort(sortedUnrepairedSymbolsfromNodes.begin(), sortedUnrepairedSymbolsfromNodes.end());
	std::vector<int> diff;
	std::set_difference(sortedCurrentLostLDPCChunkSymbols.begin(), sortedCurrentLostLDPCChunkSymbols.end(), sortedUnrepairedSymbolsfromNodes.begin(), sortedUnrepairedSymbolsfromNodes.end(), std::inserter(diff, diff.begin()));
	//for (auto i : diff) std::cout << i << ' ';
	//AllLostFromBS = setdiff(currentLostLDPCChunkSymbols, unrepairedSymbolsfromNodes);

	std::vector<std::vector<uint8_t>> encodedData = readedDatainBuffer;
	std::vector<std::vector<int>> R1ReducedCopy = R1; // To count the used effective helper Indexes % To indicate the used before hep
	std::vector<std::vector<int>> allEquationsR2ReducedCopy = allEquationsR2;
	std::vector<std::vector<int>> R2ReducedCopy = R2; // To count the used effective helper Indexes For the second phase%
	std::vector<int> usedHelpers{};

	std::vector<int> currentHelpers;
	std::vector<int> helperSizes;
	std::vector<int> R;
	std::vector<int> RReduced;
	int M, I;
	int failedSymbolID;
	std::vector<int> helperIndexes, helperIndexesReduced;
	std::vector<uint8_t> temp (encodedData[0].size());
	std::vector<std::vector<uint8_t>> helperData;
	std::vector<int> AllLostFromBS;
	std::vector<int>::iterator tempIt, it, it2; // = usedHelpers.begin(); // = unique(usedHelpers.begin(), usedHelpers.end());
	[[maybe_unused]] int f;
	int failedSymbolIDt;
	std::vector<int> eqs;
	std::vector<int> tempEqs;
	std::vector<int> tempSelectedEquation;
	std::vector<int> deletedEquations{};
	std::vector<int> tempR, tempReduced;
	int lostSymbol;
	std::vector<int> helperSymbolIndexesR2;
	std::vector<int> v;
	[[maybe_unused]] std::vector<int> foundIndex;
	[[maybe_unused]] std::vector<int> foundIndexAll;
	[[maybe_unused]] std::vector<int> tempL, tempCurrentLostLDPCChunkSymbols, tempAllLostFromBS, tempUnrepairedSymbolsfromBS;
	[[maybe_unused]] std::vector<std::vector<int>> tempR2, tempR2ReducedCopy; 
	int intersectionState, intState;
	//int selectedHelperNodeIndex;
	//uint32_t packetSize = (uint32_t) numberofRoundforBuffer;

	Ptr<Node> staWifiNode1;  // senderNode
	Ptr<Node> staWifiNode2;  // receiverNode
	//uint32_t localWriteSize = 1040;
	//uint8_t locaData[localWriteSize];
	std::vector<uint8_t> locaData;
	NodeContainer UesNodesWifi;
	Ipv4InterfaceContainer staInterface;

	while (!R1.empty())
	{
		helperSizes.clear();
		helperIndexes.clear();
		helperIndexesReduced.clear();
		R.clear();
		// Sorting R1 and R2
		//cout << "Size of R1: " << R1.size() << endl;
		//cout << "We are here in firstPhase 1_1" << endl;
		for (size_t k = 0; k < R1ReducedCopy.size(); k++)
		{
			for (size_t c = 0; c < R1ReducedCopy[k].size(); c++)
			{
				if (R1ReducedCopy[k][c] != -1)
					currentHelpers.push_back(c);
			}
			//currentHelpers = find(R1ReducedCopy(k, :) ~= 0);
			//helperSizes(k) = size(currentHelpers, 2); // 0 olan da var
			helperSizes.push_back(currentHelpers.size());
			currentHelpers.clear();
		}
		//cout << "We are here in firstPhase 1_2" << endl;
		M = helperSizes[0];
		I = 0;
		for (size_t i = 1; i < helperSizes.size(); i++)
		{
			if (helperSizes[i] < M)
			{
				M = helperSizes[i];
				I = i;
			}
		}
		//cout << "We are here in firstPhase 1_3" << endl;
		//[M, I] = min(helperSizes);
		for (size_t c = 0; c < R1[I].size(); c++)
			R.push_back(R1[I][c]);
		//R = R1(I, :); 
		
		for (size_t c = 0; c < R1ReducedCopy[I].size(); c++)
			RReduced.push_back(R1ReducedCopy[I][c]);
		//RReduced = R1ReducedCopy(I, :);
		//cout << "We are here in firstPhase 1_4" << endl;
		failedSymbolID = unrepairedSymbolsfromNodes[I];
		// REPAIR FROM OTHER NODES
		for (size_t c = 0; c < R.size(); c++)
		{
			if (R[c] != -1)
				helperIndexes.push_back(R[c]);
		}

		//helperIndexes = R(R ~= 0);
		for (size_t c = 0; c < RReduced.size(); c++)
		{
			if (RReduced[c] != -1)
				helperIndexesReduced.push_back(c);
		}
		//cout << "We are here in firstPhase 1_5" << endl;
		//helperIndexesReduced = RReduced(RReduced~= 0);
		std::fill(temp.begin(), temp.end(), 0);

		//temp = zeros(1, size(encodedData, 2));
		// cout << "size of helperData before resize:" << helperData.size() << endl;
		helperData.clear();
		helperData.resize(helperIndexes.size());
		// cout << "size of helperData after resize:" << helperData.size() << endl;
		for (size_t r = 0; r < helperIndexes.size(); r++)
		{
			// cout << "r: " << r << endl;
			// cout << "size of encodedData[r]:" << encodedData[r].size() << endl;
			for (size_t c = 0; c < encodedData[r].size(); c++)
			{
				// cout << "c: " << c << endl;
				// cout << "encodedData[helperIndexes[r]][c]: " << encodedData[helperIndexes[r]][c] << endl;
				helperData[r].push_back(encodedData[helperIndexes[r]][c]);

				// //---------------------------------------------------------
				// selectedHelperNodeIndex = helperIndexes[r]/quotient;
				// staWifiNode1 = ueNodes.Get (selectedHelperNodeIndex);  // senderNode
				// staWifiNode2 = ueNodes.Get (selectedEmptyNodeIndex);  //  receiverNode

				// //NodeContainer UesNodesWifi;
				// UesNodesWifi.Add(staWifiNode1);
				// UesNodesWifi.Add(staWifiNode2);

				// mobility.Install (UesNodesWifi);

				// NetDeviceContainer staDevices;
				// staDevices = wifiHelper.Install (wifiPhy, wifiMac, UesNodesWifi);
				// //Ipv4InterfaceContainer staInterface;
				// staInterface = address.Assign (staDevices);

				// //TCPSocketProcesses* tcpAppF = new TCPSocketProcesses(staWifiNode1, staWifiNode2, staInterface.GetAddress (1), servPort);
				// TCPSocketProcesses* tcpAppF = new HandleMessages(staWifiNode1,staWifiNode2,staInterface.GetAddress (1),servPort);

				// // initialize the tx buffer.
				// size_t lc = 0;
				// while(lc < encodedData[r].size())
				// {
				// 	for(size_t i = 0; i < localWriteSize; ++i)
				// 	{
				//     	locaData[i] = encodedData[helperIndexes[r]][lc];
				//     	lc = lc + 1;
				//     	if (lc >= encodedData[r].size())
				//     		break;
				//     }
				// }
				// memcpy(tcpAppF.data, locaData, (sizeof(locaData)));
				// //tcpApp->data = locaData;

				// tcpAppF->SetReceiverSocket();
   	// 			tcpAppF->SetSenderSocket();
   	// 			MType messageType = REQUESTREPAIRFROMUE;
   	// 			tcpAppF->StartFlow(messageType, encodedData);
				// //---------------------------------------------------------

   				//uint8_t *p = &encodedData[helperIndexes[r]][c];
				//SendPacketV2(ueNetDev.Get (selectedHelperNodeIndex), ueNetDev.Get (selectedEmptyNodeIndex)->GetAddress (), packetSize, p);
				//createSocket_Bind_Listen_Accept_Process(ns3TcpSocket, sinkAddress, gNbNodes, ueNodes, gNbNetDev, ueNetDev, internet, selectedEmptyNodeIndex, ipInterfs, p);
			}
		}
		//cout << "We are here in firstPhase 1_5_2" << endl;
		//helperData = encodedData(helperIndexes, :);
		usedHelpers.insert(usedHelpers.end(), helperIndexes.begin(), helperIndexes.end());
		//usedHelpers = [usedHelpers helperIndexes];
		//cout << "We are here in firstPhase 1_6" << endl;
		sort(usedHelpers.begin(), usedHelpers.end());

		//it.clear();
		it = unique(usedHelpers.begin(), usedHelpers.end());
		usedHelpers.resize(distance(usedHelpers.begin(), it));
		for (size_t i = 0; i < helperData.size(); i++)
		{
			//temp = (helperData[i]) ^ temp;
			for (size_t j = 0; j < helperData[i].size(); j++)
			{
				temp[j] = (helperData[i][j]) ^ temp[j];
			}
		}

		encodedData[failedSymbolID] = temp;
		//strParameters.numberofReadedSymbolsfromNodesforLDPCRepair = strParameters.numberofReadedSymbolsfromNodesforLDPCRepair + helperIndexesReduced.size()*encodedData[0].size();
		
		tempL.clear();
		for (size_t c = 0; c < L.size(); c++)
		{
			if (L[c] != failedSymbolID)
				tempL.push_back(L[c]);
		}
		L.clear();
		L = tempL;
		
		// foundIndexAll.clear();
		// for (size_t c = 0; c < currentLostLDPCChunkSymbols.size(); c++)
		// {
		// 	if (currentLostLDPCChunkSymbols[c] == failedSymbolID)
		// 		foundIndexAll.push_back(c);
		// }
		// //foundIndexAll = find(currentLostLDPCChunkSymbols == failedSymbolID);
		// for (size_t c = 0; c < foundIndexAll.size(); c++)
		// 	currentLostLDPCChunkSymbols.erase(std::remove(currentLostLDPCChunkSymbols.begin(), currentLostLDPCChunkSymbols.end(), currentLostLDPCChunkSymbols[foundIndexAll[c]]), currentLostLDPCChunkSymbols.end());
		// 	//currentLostLDPCChunkSymbols(foundIndexAll) = [];
		//cout << "We are here in firstPhase 1_8" << endl;
		tempCurrentLostLDPCChunkSymbols.clear();
		for (size_t c = 0; c < currentLostLDPCChunkSymbols.size(); c++)
		{
			if (currentLostLDPCChunkSymbols[c] != failedSymbolID)
				tempCurrentLostLDPCChunkSymbols.push_back(currentLostLDPCChunkSymbols[c]);
		}
		currentLostLDPCChunkSymbols.clear();
		currentLostLDPCChunkSymbols = tempCurrentLostLDPCChunkSymbols;

		// for (size_t c = 0; c < AllLostFromBS.size(); c++)
		// {
		// 	if (AllLostFromBS[c] == failedSymbolID)
		// 		AllLostFromBS.erase(std::remove(AllLostFromBS.begin(), AllLostFromBS.end(), AllLostFromBS[c]), AllLostFromBS.end());	
		// }

		tempAllLostFromBS.clear();
		for (size_t c = 0; c < AllLostFromBS.size(); c++)
		{
			if (AllLostFromBS[c] != failedSymbolID)
				tempAllLostFromBS.push_back(AllLostFromBS[c]);
		}
		AllLostFromBS.clear();
		AllLostFromBS = tempAllLostFromBS;

		// Update allEquationsR2ReducedCopy with before used helper Indexes
		for (size_t b = 0; b < helperIndexes.size(); b++)
		{
			//std::vector<std::vector<int>> idx{};
			for (size_t r = 0; r < allEquationsR2ReducedCopy.size(); r++)
			{
				for (size_t c = 0; c < allEquationsR2ReducedCopy[r].size(); c++)
				{
					if (allEquationsR2ReducedCopy[r][c] == helperIndexes[b])
						allEquationsR2ReducedCopy[r][c] = -1;
				}
			}
		}
		// Update allEquationsR2Reduced
		// Update R1ReducedCopy with before used helper Indexes
		for (size_t b = 0; b < helperIndexes.size(); b++)
		{
			//std::vector<std::vector<int>> idx{};
			for (size_t r = 0; r < R1ReducedCopy.size(); r++)
			{
				for (size_t c = 0; c < R1ReducedCopy[r].size(); c++)
				{
					if (R1ReducedCopy[r][c] == helperIndexes[b])
						R1ReducedCopy[r][c] = -1;
				}
			}
		}

		// Update R2ReducedCopy with before used helper Indexes
		for (size_t b = 0; b < helperIndexes.size(); b++)
		{
			//std::vector<std::vector<int>> idx{};
			for (size_t r = 0; r < R2ReducedCopy.size(); r++)
			{
				for (size_t c = 0; c < R2ReducedCopy[r].size(); c++)
				{
					if (R2ReducedCopy[r][c] == helperIndexes[b])
						R2ReducedCopy[r][c] = -1;
				}
			}
		}
		//cout << "We are here in firstPhase 2" << endl;
		// Update R2 equations
		eqs.clear();
		tempEqs.clear();
		tempSelectedEquation.clear();
		selectedEquation.clear();
		selectedEquationReduced.clear();
		if (!allEquationsR2.empty())
		{
			for (size_t index = 0; index < unrepairedSymbolsfromBS.size(); index++)
			{
				failedSymbolIDt = unrepairedSymbolsfromBS[index];
				urer = updateRecoveryEquations(failedSymbolIDt, AllLostFromBS, allEquationsR2, allEquationsR2ReducedCopy);
				
				selectedEquation = urer.selectedEquation;
				selectedEquationReduced = urer.selectedEquationReduced;

				if (failedSymbolIDt == R2[index][0])
				{
					eqs = R2[index];
					
					for (size_t c = 0; c < eqs.size(); c++)
					{
						if (eqs[c] != -1)
							tempEqs.push_back(eqs[c]);
					}

					for (size_t c = 0; c < selectedEquation.size(); c++)
					{
						if (selectedEquation[c] != -1)
							tempSelectedEquation.push_back(selectedEquation[c]);
					}

					if (tempEqs.size() != tempSelectedEquation.size() || tempEqs != tempSelectedEquation)
						cout<<"Equations are different."<<endl;

					for (size_t c = 0; c < R2[index].size(); c++)
					{
						R2[index][c] = -1;
						R2ReducedCopy[index][c] = -1;					
					}
					for (size_t c = 0; c < selectedEquation.size(); c++)
						R2[index][c] = selectedEquation[c];
					for (size_t c = 0; c < selectedEquationReduced.size(); c++)
						R2ReducedCopy[index][c] = selectedEquationReduced[c];	
				}
				else
					cout << "Error in First phase line 76" << endl;
			}
		}
		//cout << "We are here in firstPhase 3" << endl;
		// Add from R2 to R1
		deletedEquations.clear();
		tempR.clear();
		tempReduced.clear();
		helperSymbolIndexesR2.clear();
		v.clear();
		for (size_t ind = 0; ind < R2.size(); ind++)
		{
			tempR = R2[ind];
			tempR.erase(std::remove(tempR.begin(), tempR.end(), tempR[0]), tempR.end());

			tempReduced = R2ReducedCopy[ind];
			// cout << "size of tempReduced before erase operation in firstPhase: " << tempReduced.size() << endl;
			tempReduced.erase(std::remove(tempReduced.begin(), tempReduced.end(), tempReduced[0]), tempReduced.end());
			//cout << "We are here in firstPhase 3_1" << endl;
			lostSymbol = R2[ind][0];
			for (size_t c = 0; c < tempR.size(); c++)
			{
				if (tempR[c] != -1)
					helperSymbolIndexesR2.push_back(c);
			}

			intersectionState = 0;
			for (size_t i = 0; i < helperSymbolIndexesR2.size(); i++)
			{
				for (size_t j = 0; j < currentLostLDPCChunkSymbols.size(); j++)
				{
					if (helperSymbolIndexesR2[i] == currentLostLDPCChunkSymbols[j])
					{
						intersectionState = 1;
						break;
					}
				}
				if (intersectionState == 1)
					break;
			}
			//cout << "We are here in firstPhase 3_3" << endl;
			// it = std::set_intersection(helperSymbolIndexesR2.begin(), helperSymbolIndexesR2.end(), currentLostLDPCChunkSymbols.begin(), currentLostLDPCChunkSymbols.end(), v.begin());
			// v.resize(it - v.begin());
			// if (v.size() <= 0)
			if (intersectionState == 0)
			{
				deletedEquations.push_back(ind);

				R1.push_back(tempR);
				//cout << "We are here in firstPhase 3_3_1_2" << endl;
				R1ReducedCopy.push_back(tempReduced);
				//cout << "We are here in firstPhase 3_3_1" << endl;
				if (R2ReducedCopy[ind][0] != R2[ind][0])
					cout << "Error in First phase line 93" << endl;

				unrepairedSymbolsfromNodes.push_back(lostSymbol);

				// for (size_t idx = 0; idx < unrepairedSymbolsfromBS.size(); idx++)
				// {
				// 	if (unrepairedSymbolsfromBS[idx] == lostSymbol)
				// 		unrepairedSymbolsfromBS.erase(std::remove(unrepairedSymbolsfromBS.begin(), unrepairedSymbolsfromBS.end(), unrepairedSymbolsfromBS[idx]), unrepairedSymbolsfromBS.end());
				// }
				// //idx = find(unrepairedSymbolsfromBS == lostSymbol);
				// //unrepairedSymbolsfromBS(idx) = [];
				//cout << "We are here in firstPhase 3_3_2" << endl;
				tempUnrepairedSymbolsfromBS.clear();
				for (size_t c = 0; c < unrepairedSymbolsfromBS.size(); c++)
				{
					if (unrepairedSymbolsfromBS[c] != lostSymbol)
						tempUnrepairedSymbolsfromBS.push_back(unrepairedSymbolsfromBS[c]);
				}
				unrepairedSymbolsfromBS.clear();
				unrepairedSymbolsfromBS = tempUnrepairedSymbolsfromBS;

				// for (size_t idx = 0; idx < AllLostFromBS.size(); idx++)
				// {
				// 	if (AllLostFromBS[idx] == lostSymbol)
				// 		AllLostFromBS.erase(std::remove(AllLostFromBS.begin(), AllLostFromBS.end(), AllLostFromBS[idx]), AllLostFromBS.end());
				// }
				// //idx = find(AllLostFromBS == lostSymbol);
				// //AllLostFromBS(idx) = [];
				//cout << "We are here in firstPhase 3_3_3" << endl;
				tempAllLostFromBS.clear();
				for (size_t c = 0; c < AllLostFromBS.size(); c++)
				{
					if (AllLostFromBS[c] != lostSymbol)
						tempAllLostFromBS.push_back(AllLostFromBS[c]);
				}
				AllLostFromBS.clear();
				AllLostFromBS = tempAllLostFromBS;
			}
			//cout << "We are here in firstPhase 3_4" << endl;
		}

		tempR2.clear();
		tempR2ReducedCopy.clear();
		for (size_t r = 0; r < R2.size(); r++) 
		{
			intState = 0;
			for (size_t i = 0; i < deletedEquations.size(); i++)
			{
				if ((int)r == deletedEquations[i])
				{
					intState = 1;
					break;
				}
			}
			if (intState == 0)
			{
				tempR2.push_back(R2[r]);
				tempR2ReducedCopy.push_back(R2ReducedCopy[r]);
			}				
		}

		R2.clear();
		R2 = tempR2;
		R2ReducedCopy.clear();
		R2ReducedCopy = tempR2ReducedCopy;

		R1.erase(R1.begin() + I);
		//R1(I, :) = [];
		R1ReducedCopy.erase(R1ReducedCopy.begin() + I);
		//R1ReducedCopy(I, :) = [];
		unrepairedSymbolsfromNodes.erase(std::remove(unrepairedSymbolsfromNodes.begin(), unrepairedSymbolsfromNodes.end(), unrepairedSymbolsfromNodes[I]), unrepairedSymbolsfromNodes.end());
	}

	//fprLocal.strParameters = strParameters;
	fprLocal.encodedData = encodedData;
	fprLocal.L = L;
	fprLocal.currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
	fprLocal.R2 = R2;
	fprLocal.R2ReducedCopy = R2ReducedCopy;
	fprLocal.unrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
	fprLocal.unrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
	fprLocal.usedHelpers = usedHelpers;

	return fprLocal;
}