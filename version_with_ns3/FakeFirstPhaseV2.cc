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

typedef struct fakeFirstPhaseReturns Struct;

//Struct FakeFirstPhaseV2(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, int quotient, int selectedEmptyNodeIndex, NetDeviceContainer ueNetDev, int numberofRoundforBuffer, uint16_t servPort, MobilityHelper mobility, Ipv4AddressHelper address, std::vector<string> inputFiles, std::vector<int> aliveLDPCStorageNodes, NodeContainer ueNodes, WifiHelper wifiHelper, int maxColLength, std::string repairedFile)
Struct FakeFirstPhaseV2(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<int>> allEquationsR2, int quotient, std::vector<int> aliveLDPCStorageNodes)
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

	std::vector<std::vector<uint8_t>> encodedData;
	std::vector<std::vector<int>> R1ReducedCopy = R1; // To count the used effective helper Indexes % To indicate the used before hep
	std::vector<std::vector<int>> allEquationsR2ReducedCopy = allEquationsR2;
	std::vector<std::vector<int>> R2ReducedCopy = R2; // To count the used effective helper Indexes For the second phase%
	std::vector<int> usedHelpers{};

	std::vector<int> currentHelpers;
	std::vector<int> helperSizes;
	std::vector<int> R;
	std::vector<int> RReduced;
	int M, I;
	//int failedSymbolID;
	std::vector<int> helperIndexes, helperIndexesReduced;
	//std::vector<uint8_t> temp (encodedData[0].size());
	std::vector<std::vector<uint8_t>> helperData;
	std::vector<int> AllLostFromBS;
	std::vector<int>::iterator tempIt, it, it2; // = usedHelpers.begin(); // = unique(usedHelpers.begin(), usedHelpers.end());
	[[maybe_unused]] int f;
	//int failedSymbolIDt;
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
	[[maybe_unused]] std::vector<std::vector<int>> tempR2ReducedCopy; 
	int intersectionState, intState;
	int selectedHelperNodeIndex;
	//uint32_t packetSize = (uint32_t) numberofRoundforBuffer;

	Ptr<Node> staWifiNode1;  // senderNode
	Ptr<Node> staWifiNode2;  // receiverNode
	//uint32_t localWriteSize = 1040;
	//uint8_t locaData[localWriteSize];
	std::vector<uint8_t> locaData;
	NodeContainer UesNodesWifi;
	Ipv4InterfaceContainer staInterface;

	std::vector<std::vector<int>> tempR1 = R1;
	std::vector<std::vector<int>> tempR2 = R2;
	[[maybe_unused]] std::vector<std::vector<int>> tempRR2ReducedCopy;
	std::vector<int> tempRR;
	std::vector<std::vector<int>> tempRR2;
	std::vector<int> tempUsedHelpers{};
	std::vector<int> tempHelperIndexes;
	std::vector<int> tempUnrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
	int tempFailedSymbolID, tempFailedSymbolIDt;
	std::vector<int> tempHelperSizes;
	//int nodeIndex;
	std::vector<int> helperNodes;
	std::vector<int> currentHelperNodeIndexes{};

	cout << "We are in FakeFirstPhaseV2" << endl;

	while (!tempR1.empty())
	{   cout << "We are in FakeFirstPhaseV2 0" << endl;
		tempHelperSizes.clear();
		tempHelperIndexes.clear();
		tempR.clear();

		for (size_t k = 0; k < R1ReducedCopy.size(); k++)
		{
			for (size_t c = 0; c < R1ReducedCopy[k].size(); c++)
			{
				if (R1ReducedCopy[k][c] != -1)
					currentHelpers.push_back(c);
			}
			tempHelperSizes.push_back(currentHelpers.size());
			currentHelpers.clear();
		}
		M = tempHelperSizes[0];
		I = 0;
		cout << "We are in FakeFirstPhaseV2 1" << endl;
		for (size_t i = 1; i < tempHelperSizes.size(); i++)
		{
			if (tempHelperSizes[i] < M)
			{
				M = tempHelperSizes[i];
				I = i;
			}
		}
		for (size_t c = 0; c < tempR1[I].size(); c++)
			tempR.push_back(tempR1[I][c]);
		
		for (size_t c = 0; c < tempR.size(); c++)
		{
			if (tempR[c] != -1)
				tempHelperIndexes.push_back(tempR[c]);
		}
        cout << "We are in FakeFirstPhaseV2 3" << endl;
		tempUsedHelpers.insert(tempUsedHelpers.end(), tempHelperIndexes.begin(), tempHelperIndexes.end());
		sort(tempUsedHelpers.begin(), tempUsedHelpers.end());
		tempIt = unique(tempUsedHelpers.begin(), tempUsedHelpers.end());
		tempUsedHelpers.resize(distance(tempUsedHelpers.begin(), tempIt));

		//---------------------------------------------------------

		tempAllLostFromBS.clear();
		tempFailedSymbolID = tempUnrepairedSymbolsfromNodes[I];

		//---------------------------------------------------------

		// cout << "L: ";
		// for (size_t i = 0; i < L.size(); i++)
		// 	cout << L[i] << " ";
		// cout << endl;
		// cout << "tempFailedSymbolID: " << tempFailedSymbolID << endl;
         cout << "We are in FakeFirstPhaseV2 4" << endl;
		vector<int>::iterator it = L.begin();
		for (size_t c = 0; c < L.size(); c++)
		{
			if (L[c] == tempFailedSymbolID)
			{
				L.erase(it + c);
				break;
			}
		}

		// cout << "L: ";
		// for (size_t i = 0; i < L.size(); i++)
		// 	cout << L[i] << " ";
		// cout << endl;
		// cout << "tempFailedSymbolID: " << tempFailedSymbolID << endl;

		//---------------------------------------------------------
        cout << "We are in FakeFirstPhaseV2 5" << endl;
		for (size_t c = 0; c < AllLostFromBS.size(); c++)
		{
			if (AllLostFromBS[c] != tempFailedSymbolID)
				tempAllLostFromBS.push_back(AllLostFromBS[c]);
		}
		AllLostFromBS.clear();
		AllLostFromBS = tempAllLostFromBS;
        cout << "We are in FakeFirstPhaseV2 6" << endl;
		// Update allEquationsR2ReducedCopy with before used helper Indexes
		for (size_t b = 0; b < tempHelperIndexes.size(); b++)
		{
			for (size_t r = 0; r < allEquationsR2ReducedCopy.size(); r++)
			{
				for (size_t c = 0; c < allEquationsR2ReducedCopy[r].size(); c++)
				{
					if (allEquationsR2ReducedCopy[r][c] == tempHelperIndexes[b])
						allEquationsR2ReducedCopy[r][c] = -1;
				}
			}
		}
        cout << "We are in FakeFirstPhaseV2 7" << endl;
		// Update R1ReducedCopy with before used helper Indexes
		for (size_t b = 0; b < tempHelperIndexes.size(); b++)
		{
			for (size_t r = 0; r < R1ReducedCopy.size(); r++)
			{
				for (size_t c = 0; c < R1ReducedCopy[r].size(); c++)
				{
					if (R1ReducedCopy[r][c] == tempHelperIndexes[b])
						R1ReducedCopy[r][c] = -1;
				}
			}
		}

		// Update R2ReducedCopy with before used helper Indexes
		for (size_t b = 0; b < tempHelperIndexes.size(); b++)
		{
			for (size_t r = 0; r < R2ReducedCopy.size(); r++)
			{
				for (size_t c = 0; c < R2ReducedCopy[r].size(); c++)
				{
					if (R2ReducedCopy[r][c] == tempHelperIndexes[b])
						R2ReducedCopy[r][c] = -1;
				}
			}
		}
        cout << "We are in FakeFirstPhaseV2 8" << endl;
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
				tempFailedSymbolIDt = unrepairedSymbolsfromBS[index];
				urer = updateRecoveryEquations(tempFailedSymbolIDt, AllLostFromBS, allEquationsR2, allEquationsR2ReducedCopy);
				
				selectedEquation = urer.selectedEquation;
				selectedEquationReduced = urer.selectedEquationReduced;

				if (tempFailedSymbolIDt == tempR2[index][0])
				{
					eqs = tempR2[index];
					
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

					for (size_t c = 0; c < tempR2[index].size(); c++)
					{
						tempR2[index][c] = -1;
						R2ReducedCopy[index][c] = -1;		
						cout<<"Fake first v2 1."<<endl;			
					}
					for (size_t c = 0; c < selectedEquation.size(); c++)
						tempR2[index][c] = selectedEquation[c];
						cout<<"Fake first v2 2."<<endl;	
					for (size_t c = 0; c < selectedEquationReduced.size(); c++)
						R2ReducedCopy[index][c] = selectedEquationReduced[c];	
				}
				else
					cout << "Error in First phase line 76" << endl;
			}
		}

		// Add from R2 to R1
		deletedEquations.clear();
		tempRR.clear();
		tempReduced.clear();
		helperSymbolIndexesR2.clear();
		v.clear();
		for (size_t ind = 0; ind < tempR2.size(); ind++)
		{
			tempRR = tempR2[ind];
			tempRR.erase(std::remove(tempRR.begin(), tempRR.end(), tempRR[0]), tempRR.end());

			tempReduced = R2ReducedCopy[ind];
			tempReduced.erase(std::remove(tempReduced.begin(), tempReduced.end(), tempReduced[0]), tempReduced.end());
			lostSymbol = tempR2[ind][0];
			for (size_t c = 0; c < tempRR.size(); c++)
			{
				if (tempRR[c] != -1)
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

			if (intersectionState == 0)
			{
				deletedEquations.push_back(ind);

				tempR1.push_back(tempRR);
				R1ReducedCopy.push_back(tempReduced);
				if (R2ReducedCopy[ind][0] != tempR2[ind][0])
					cout << "Error in First phase line 93" << endl;

				tempUnrepairedSymbolsfromNodes.push_back(lostSymbol);

				tempUnrepairedSymbolsfromBS.clear();
				for (size_t c = 0; c < unrepairedSymbolsfromBS.size(); c++)
				{
					if (unrepairedSymbolsfromBS[c] != lostSymbol)
						tempUnrepairedSymbolsfromBS.push_back(unrepairedSymbolsfromBS[c]);
				}
				unrepairedSymbolsfromBS.clear();
				unrepairedSymbolsfromBS = tempUnrepairedSymbolsfromBS;

				tempAllLostFromBS.clear();
				for (size_t c = 0; c < AllLostFromBS.size(); c++)
				{
					if (AllLostFromBS[c] != lostSymbol)
						tempAllLostFromBS.push_back(AllLostFromBS[c]);
				}
				AllLostFromBS.clear();
				AllLostFromBS = tempAllLostFromBS;
			}
		}

		tempRR2.clear();
		tempRR2ReducedCopy.clear();
		for (size_t r = 0; r < tempR2.size(); r++) 
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
				tempRR2.push_back(tempR2[r]);
				tempRR2ReducedCopy.push_back(R2ReducedCopy[r]);
			}				
		}

		tempR2.clear();
		tempR2 = tempRR2;
		R2ReducedCopy.clear();
		R2ReducedCopy = tempRR2ReducedCopy;

		tempR1.erase(tempR1.begin() + I);
		R1ReducedCopy.erase(R1ReducedCopy.begin() + I);
		tempUnrepairedSymbolsfromNodes.erase(std::remove(tempUnrepairedSymbolsfromNodes.begin(), tempUnrepairedSymbolsfromNodes.end(), tempUnrepairedSymbolsfromNodes[I]), tempUnrepairedSymbolsfromNodes.end());
	}

	R1ReducedCopy.clear();
	R1ReducedCopy = R1;
	R2ReducedCopy.clear();
	R2ReducedCopy = R2;
	tempReduced.clear();
	deletedEquations.clear();
	helperSymbolIndexesR2.clear();
	//size_t lc;

	// cout << "tempUsedHelpers: ";
	// for (size_t i = 0; i < tempUsedHelpers.size(); i++)
	// 	cout << tempUsedHelpers[i] << " ";
	// cout << endl;

	// aliveLDPCStorageNodes[helperNodes[h]]
	int tempNodeIndex;
	for (size_t i = 0; i < tempUsedHelpers.size(); i++)
	{
		tempNodeIndex = (int)(tempUsedHelpers[i]/quotient);
		if(aliveLDPCStorageNodes[tempNodeIndex] != -1)
			helperNodes.push_back(tempNodeIndex);
	}
	//helperNodes[i] = (int)(tempUsedHelpers[i]/quotient);

	//sort(helperNodes.begin(), helperNodes.end());
	it2 = unique(helperNodes.begin(), helperNodes.end());
	helperNodes.resize(distance(helperNodes.begin(), it2));

	// cout << "helperNodes: ";
	// for (size_t i = 0; i < helperNodes.size(); i++)
	// 	cout << helperNodes[i] << " ";
	// cout << endl;

	// helperData.clear();
	// helperData.resize(tempUsedHelpers.size());
	for (size_t h = 0; h < helperNodes.size(); h++)
	{
		selectedHelperNodeIndex = aliveLDPCStorageNodes[helperNodes[h]];

		// //---------------------------------------------------------
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
		// TCPSocketProcesses* tcpAppF = new HandleMessages(staWifiNode1,staWifiNode2,staInterface.GetAddress (selectedEmptyNodeIndex),servPort);
		// //---------------------------------------------------------

		currentHelperNodeIndexes.clear();
		for (size_t r = 0; r < tempUsedHelpers.size(); r++)
		{
			if (selectedHelperNodeIndex == tempUsedHelpers[r]/quotient)
				currentHelperNodeIndexes.push_back(tempUsedHelpers[r]);
		}

		// //---------------------------------------------------------
		// tcpAppF->SetReceiverSocket();
		// tcpAppF->SetSenderSocket();
		// MType messageType = REQUESTREPAIRFROMUE;
		// //encodedData = tcpAppF->StartFlowV1(messageType, inputFiles, selectedHelperNodeIndex);
		// //tcpAppF->StartFlowV2(messageType, encodedData, currentHelperNodeIndexes);
		// tcpAppF->StartFlowV4(messageType, encodedData, currentHelperNodeIndexes, inputFiles, selectedHelperNodeIndex, quotient, repairedFile);
		// //---------------------------------------------------------	
	}

	//---------------------------------------------------------------------------------------

	
	fprLocal.tempUsedHelpers = tempUsedHelpers;
	fprLocal.helperNodes = helperNodes;
	fprLocal.currentHelperNodeIndexes = currentHelperNodeIndexes;
	//fprLocal.encodedData = encodedData;
	fprLocal.usedHelpers = usedHelpers;
	fprLocal.tempL = L;
	//fprLocal.strParameters = strParameters;
	fprLocal.R2ReducedCopy = R2ReducedCopy;
	
	return fprLocal;
}