#include "userDefinedFunctions.h"
#include <vector>
#include <random>
#include<algorithm>
#include <iterator>
#include <ctime> 
#include <iostream>
#include<string> 

using namespace std;

typedef struct repairReturns Struct;

Struct processRepair(std::vector<std::vector<int>> Hsys, std::vector<struct ns> nodeStr, int counterLeavingNodes, std::vector<int> leavingNodes, int numberofLDPCStorageNodes, int numberofInitialLDPCStorageNodes, double baseStationSize, std::vector<int> ldpcFileSizes, struct strP strParameters, struct strP strParameters2, int numberofRoundforBuffer, double blockSize, std::vector<int> aliveLDPCStorageNodes)
{
	Struct rrLocal;	
	struct singleRepairAlgorithmV1Returns sAV1R;
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
	string tempS1;
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
	[[maybe_unused]] int rows = (int)Hsys.size();
	int cols = (int)Hsys[0].size();
	int quotient = ceil((double)cols / (double)numberofInitialLDPCStorageNodes);
	[[maybe_unused]] int maxColLength = (numberofInitialLDPCStorageNodes - 1)*quotient + quotient;
	FILE *bookofAccountID;

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
	
	for (int i = 0; i < counterLeavingNodes; i++)
	{
		val = leavingNodes[i];
		// if (val > 0)
		// {
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
				//lostLDPCChunkSymbols = [lostLDPCChunkSymbols, (nodeStr(val).logicalNodeID - 1)*quotient + 1:upper];

				// cout << "quotient: " << quotient << endl;
				// cout << "val: " << val << endl;
				// cout << "nodeStr[val].logicalNodeID: " << nodeStr[val].logicalNodeID << endl;
				// cout << "start: " << start << endl;
				// cout << "upper: " << upper << endl;
				// cout << "lostLDPCChunkSymbols: " ;
				// for(size_t i = 0; i < lostLDPCChunkSymbols.size(); i++)
				// 	cout << lostLDPCChunkSymbols[i] << " ";
				// cout << endl;
			}
			if (availableEmptyNodes.empty() == 0)
			{
				// EMPTY NODES ARE SELECTED FROM ALL EMPTY NODES IN THE CELL
				// std::mt19937_64 gen{ std::random_device()() };
				// std::uniform_real_distribution<int> dis{ 0, (int)availableEmptyNodes.size() };
				// int temp = dis(gen);
				temp = rand() % (int)availableEmptyNodes.size(); //ranges from 0 to (int)availableEmptyNodes.size()-1
				//temp = randperm(availableEmptyNodes.size(), 1);
				selectedEmptyNodes.push_back(availableEmptyNodes[temp]);
				// DISCARDING THE USED NODE FROM THE AVAILABLE EMPTY NODES
				// cout << "size of availableEmptyNodes before erase operation in processRepair: " << availableEmptyNodes.size() << endl;
				availableEmptyNodes.erase(availableEmptyNodes.begin()+temp);
			}
		// }
	}
	
	nodeStr2 = nodeStr;
	aliveLDPCStorageNodes2 = aliveLDPCStorageNodes;

	sort(lostLDPCChunkSymbols.begin(), lostLDPCChunkSymbols.end());	
	it = unique(lostLDPCChunkSymbols.begin(), lostLDPCChunkSymbols.end());
	lostLDPCChunkSymbols.resize(distance(lostLDPCChunkSymbols.begin(), it));

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

				// std::vector<int> logicalIDs(leavingLDPCStorageNodes.size(), 0);
				// std::vector<int> sortedLeavingLDPCStorageNodes(leavingLDPCStorageNodes.size(), 0);

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
						//sortedLeavingLDPCStorageNodes[j] = nodeStr[leavingLDPCStorageNodes[sortValue]].nodeID;
					// else
					// {
					// 	sortedLeavingLDPCStorageNodes.push_back(0);
					// }
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

					// cout << "i: " << i << endl;
					// cout << "selectedEmptyNodes[i]: " << selectedEmptyNodes[i] << endl;
					// cout << "nodeStr[selectedEmptyNodes[i]].nodeID: " << nodeStr[selectedEmptyNodes[i]].nodeID << endl;
					// cout << "nodeStr[selectedEmptyNodes[i]].logicalNodeID: " << nodeStr[selectedEmptyNodes[i]].logicalNodeID << endl;
					// cout << "nodeStr[selectedEmptyNodes[i]].fileName: " << nodeStr[selectedEmptyNodes[i]].fileName << endl;
					// cout << "nodeStr[selectedEmptyNodes[i]].isLive: " << nodeStr[selectedEmptyNodes[i]].isLive << endl;
					// cout << "nodeStr[selectedEmptyNodes[i]].encodingType: " << nodeStr[selectedEmptyNodes[i]].encodingType << endl;
					// cout << "nodeStr[selectedEmptyNodes[i]].repairedNodeID: " << nodeStr[selectedEmptyNodes[i]].repairedNodeID << endl;
					// cout << endl;
				}
					
				endTimeLDPCRepairGeneral = time(0);
				elapsedTimeLDPCRepairGeneral = difftime(startTimeLDPCRepairGeneral, endTimeLDPCRepairGeneral);			
				startTimeLDPCRepair = time(0);
				
				for (size_t i = 0; i<leavingLDPCStorageNodes.size();i++)
				{
					// //upper2 = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID - 1)*quotient + quotient;
					// upper2 = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID)*quotient + quotient;
					// if (upper2 > cols)
					// 	upper2 = cols;
					// //startP = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID - 1)*quotient + 1;
					// startP = (nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID)*quotient + 1;

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

					// cout << "quotient: " << quotient << endl;
					// cout << "sortedLeavingLDPCStorageNodes[i]: " << sortedLeavingLDPCStorageNodes[i] << endl;
					// cout << "nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID: " << nodeStr[sortedLeavingLDPCStorageNodes[i]].logicalNodeID << endl;
					// cout << "startP: " << startP << endl;
					// cout << "upper2: " << upper2 << endl;
					// cout << "currentLostSymbols: " ;
					// for(size_t i = 0; i < currentLostSymbols.size(); i++)
					// 	cout << currentLostSymbols[i] << " ";
					// cout << endl;

					cout << "We are in processRepair before LDPCSingleRepairAlgorithmV1" << endl;
					sAV1R = LDPCSingleRepairAlgorithmV1(foundOne, repairedFile, currentLostSymbols, totalHelperFiles, cols, quotient, Hsys, nodeStr, lostLDPCChunkSymbols, strParameters, numberofRoundforBuffer, aliveLDPCStorageNodes, blockSize, maxColLength);				
					cout << "We are in processRepair after LDPCSingleRepairAlgorithmV1" << endl;
					totalHelperFiles = sAV1R.totalHelperFiles;
					nodeStr = sAV1R.nodeStr;
					strParameters = sAV1R.strParameters;
					aliveLDPCStorageNodes = sAV1R.aliveLDPCStorageNodes;
					cout << "We are here in processRepair 1" << endl;
					ex = strParameters.numberofReadedSymbolsfromNodesforLDPCRepair;
				}

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
			fcloseall();
			exit(0);
		}
	}
	else
	{
		cout << "There is no leaving storage nodes!" << endl;
	}
	cout << "We are here in processRepair 7" << endl;
	rrLocal.isMultipleRepair = isMultipleRepair;
	rrLocal.nodeStr = nodeStr;
	rrLocal.numberofLDPCStorageNodes = numberofLDPCStorageNodes;
	rrLocal.strParameters = strParameters;
	rrLocal.strParameters2 = strParameters2;
	rrLocal.leavingLDPCStorageNodes = leavingLDPCStorageNodes;	
	rrLocal.aliveLDPCStorageNodes = aliveLDPCStorageNodes;
	cout << "We are here in processRepair 8" << endl;
	return rrLocal;
}