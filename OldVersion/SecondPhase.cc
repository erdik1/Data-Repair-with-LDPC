#include "userDefinedFunctions.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

typedef struct secondPhaseReturns Struct;

Struct SecondPhase(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R2, std::vector<std::vector<int>> R2Reduced, struct strP strParameters, std::vector<std::vector<uint8_t>> encodedData, int currentColumnIndex, int cols, int stopState, int maxColLength)
{
	Struct sprLocal;
	FILE *baseStationID;
	// string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/";
	string root_directory = "scratch/testFolder/";
	string current_directory = root_directory + "files/";
	string baseStation = current_directory + "baseStation.bin";
	baseStationID = fopen(baseStation.c_str(), "r");

	std::vector<int> currentLostHelpers(R2.size(),0);
	std::vector<int> lostHelperSizes, helperIndexes, helperIndexesReduced, helperIndexesfromBS;
	std::vector<int> R, RReduced, lostHelpers;
	int M, I, failedSymbolID, finished;
	[[maybe_unused]] int index;
	uint8_t read;
	std::vector<int> helperIndexesfromNodes, helperIndexesfromNodesReduced;
	std::vector<int> repairedHelperSymbols{};
	//auto last;
	[[maybe_unused]] int c;
	[[maybe_unused]] int increment;
	std::vector<uint8_t> temp(encodedData[0].size(), 0);
	std::vector<std::vector<uint8_t>> helperData{};
	int intState;
	//[[maybe_unused]] size_t tempCheckSize = encodedData[0].size();

	cout << "We are here in secondPhase 1" << endl;
	// cout << "size of R2: " << R2.size() << endl;
	// cout << "size of R2Reduced: " << R2Reduced.size() << endl;

	// cout << "R2: " << endl;
	// for (size_t r = 0; r < R2.size(); r++)
	// {
	// 	for (size_t c = 0; c < R2[r].size(); c++)
	// 	{
	// 		cout << R2[r][c] << " " ;
	// 	}
	// 	cout << endl;
	// }

	// cout << "R2Reduced: " << endl;
	// for (size_t r = 0; r < R2Reduced.size(); r++)
	// {
	// 	for (size_t c = 0; c < R2Reduced[r].size(); c++)
	// 	{
	// 		cout << R2Reduced[r][c] << " " ;
	// 	}
	// 	cout << endl;
	// }
	[[maybe_unused]] int tempIndex;
	// cout << "size of L at the beginning of SecondPhase: " << L.size() << endl;
	// cout << "L (lost symbols): ";
	for (size_t k = 0; k < L.size(); k++)
	{
		// cout << L[k] << " ";
		tempIndex = L[k];
	}

	cout << endl;
	// cout << "At the beginning of SecondPhase: " << endl;
	// cout << "size of encodedData: " << encodedData.size() << endl;
	// for (size_t r = 0; r < encodedData.size(); r++)
	// {
	// 	cout << "size of encodedData[r]: " << encodedData[r].size() << endl;
	// }
	while (!L.empty())
	{
		//std::vector<int> currentLostHelpers(R2.size(),0);
		//std::fill(currentLostHelpers.begin(), currentLostHelpers.end(), 0);
		//std::vector<int> lostHelperSizes{};
		lostHelperSizes.clear();
		helperIndexes.clear();
		helperIndexesReduced.clear();
		helperIndexesfromBS.clear();

		for (size_t k = 0; k < R2.size(); k++)
		{
			// Finding the number of lost symbols in the recovery equations
			for (size_t c = 1; c < R2[k].size(); c++)
			{
				for (size_t l = 0; l < currentLostLDPCChunkSymbols.size(); l++)
				{
					if (R2[k][c] == currentLostLDPCChunkSymbols[l])
						currentLostHelpers.push_back(c);
				}
			}
			lostHelperSizes.push_back(currentLostHelpers.size());
			currentLostHelpers.clear();
			//intersections = ismember(R2(k, 2:end), currentLostLDPCChunkSymbols);
		}
		cout << "We are here in secondPhase 1_1" << endl;
		// cout << "size of currentLostLDPCChunkSymbols: " << currentLostLDPCChunkSymbols.size() << endl;	
		// cout << "size of currentLostHelpers: " << currentLostHelpers.size() << endl;

		// cout << "currentLostHelpers: ";
		// for (size_t i = 0; i < currentLostHelpers.size(); i++)
		// 	cout << currentLostHelpers[i] << " ";
		// cout << endl;
		cout << "We are here in secondPhase 1_1_1" << endl;
		// cout << "currentLostLDPCChunkSymbols: ";
		// for (size_t i = 0; i < currentLostLDPCChunkSymbols.size(); i++)
		// 	cout << currentLostLDPCChunkSymbols[i] << " ";
		// cout << endl;
		cout << "We are here in secondPhase 1_1_2" << endl;
		// cout << "R2: " << endl;
		// for (size_t r = 0; r < R2.size(); r++)
		// {
		// 	for (size_t c = 0; c < R2[r].size(); c++)
		// 	{
		// 		cout << R2[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

		// cout << "R2Reduced: " << endl;
		// for (size_t r = 0; r < R2Reduced.size(); r++)
		// {
		// 	for (size_t c = 0; c < R2Reduced[r].size(); c++)
		// 	{
		// 		cout << R2Reduced[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }
		cout << "We are here in secondPhase 1_1_3" << endl;
		// cout << "size of currentLostHelpers: " << currentLostHelpers.size() << endl;
		// cout << "size of lostHelperSizes: " << lostHelperSizes.size() << endl; 
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
		cout << "We are here in secondPhase 1_2" << endl;
		for (size_t c = 1; c < R2[I].size(); c++)
			R.push_back(R2[I][c]);
		//R = R2(I, 2:end);
		cout << "We are here in secondPhase 1_3" << endl;
		// cout << "size of R2: " << R2.size() << endl;
		// cout << "size of R2Reduced: " << R2Reduced.size() << endl;
		// cout << "size of RReduced: " << RReduced.size() << endl;
		for (size_t c = 1; c < R2Reduced[I].size(); c++)
			RReduced.push_back(R2Reduced[I][c]);  // Reduced helper symbols from
		//RReduced = R2Reduced(I, 2:end);

		// cout << "L (lost symbols): ";
		for (size_t k = 0; k < L.size(); k++)
		{
			// cout << L[k] << " ";
			tempIndex = L[k];
		}
		cout << endl;
		// cout << "I: " << I << endl;
		// cout << "M: " << M << endl;
		failedSymbolID = L[I];
		// cout << "failedSymbolID (L[I]): " << failedSymbolID << endl;
		// cout << "encodedData[failedSymbolID][c]: " ;
		// for (int c = 0; c < 10; c++)
		// 	cout << encodedData[failedSymbolID][c] << " ";
		// cout << endl;
		cout << "We are here in secondPhase 1_4" << endl;
		for (size_t c = 0; c < RReduced.size(); c++)
		{
			for (size_t l = 0; l < currentLostLDPCChunkSymbols.size(); l++)
			{
				if (RReduced[c] == currentLostLDPCChunkSymbols[l])
					lostHelpers.push_back(c);
			}
		}		
		//intersections = ismember(RReduced, currentLostLDPCChunkSymbols);
		cout << "We are here in secondPhase 1_5" << endl;
		repairedHelperSymbols.clear();
		if (lostHelpers.size() >= 1)
		{
			// REPAIR FROM BASE STATION
			index = 0;
			finished = 0;
			cout << "We are here in secondPhase 1_5_1" << endl;
			// cout << "size of encodedData: " << encodedData.size() << endl;
			// cout << "size of encodedData[failedSymbolID]: " << encodedData[failedSymbolID].size() << endl;
			// cout << "tempIndex: " << tempIndex << endl;
			// cout << "size of encodedData[tempIndex]: " << encodedData[tempIndex].size() << endl;
			// cout << "encodedData[failedSymbolID]: ";
			// for (int c=0;c<10;c++)
			// 	cout << encodedData[failedSymbolID][c] << " ";
			// cout << endl;
			// cout << "currentColumnIndex: " << currentColumnIndex << endl;
			// cout << "maxColLength: " << maxColLength << endl;
			for (size_t j = currentColumnIndex; j < currentColumnIndex + encodedData[failedSymbolID].size(); j++)
			{
				//if (fseek(baseStationID, (j - 1)* maxColLength + failedSymbolID - 1, SEEK_SET) == 0)
				if (fseek(baseStationID, j * maxColLength + failedSymbolID , SEEK_SET) == 0)
				{
					size_t result = fread(&read, sizeof(std::uint8_t), 1, baseStationID);
					//cout << "result: " << result << endl;
					if (result == 1)
					{
						encodedData[failedSymbolID][index] = read;
						// cout << "failedSymbolID: " << failedSymbolID << endl;
						// if (tempCheckSize > encodedData[failedSymbolID].size())
						// 	cout << "We are here 1 in secondPhase" << endl;
						//encodedData[failedSymbolID].push_back(read);
						strParameters.numberofReadedSymbolsfromBSforLDPCRepair = strParameters.numberofReadedSymbolsfromBSforLDPCRepair + 1;
					}
					else
						finished = 1;
				}
				else
					finished = 1;

				if (finished == 1)
				{
					cout << "We are here in secondPhase 1_5_1_2" << endl;
					// for(size_t columnIndex=index;columnIndex<encodedData[failedSymbolID].size();columnIndex++)
					// {
					// 	std::for_each(encodedData.begin(), encodedData.end(), 
					//     [&](auto& row) {
					//         row.erase(std::next(row.begin(), columnIndex));
					//     });
					// }
					
					// for (auto& row : encodedData) 
					// 	row.erase(next(row.begin(), index));
					//encodedData(:, index : end) = [];
					for(size_t columnToDelete=index; columnToDelete<encodedData[failedSymbolID].size(); columnToDelete++)
					{
						for (unsigned i = 0; i < encodedData.size(); ++i)
						{
						  if (encodedData[i].size() > columnToDelete)
						  {
						    encodedData[i].erase(encodedData[i].begin() + columnToDelete);
						  }
						}
					}

					stopState = 1;
					break;
				}
				index = index + 1;
			}
		}
		else
		{
			// REPAIR FROM NODES
			cout << "We are here in secondPhase 1_5_2" << endl;
			for (size_t r = 0; r < R.size(); r++)
			{
				if (R[r] != 0)
					helperIndexes.push_back(r);
			}
			//helperIndexes = R(R(:) ~= 0);
			cout << "We are here in secondPhase 1_5_3" << endl;
			for (size_t r = 0; r < RReduced.size(); r++)
			{
				if (RReduced[r] != 0)
					helperIndexesReduced.push_back(r);
			}
			//helperIndexesReduced = RReduced(RReduced(:) ~= 0);
			cout << "We are here in secondPhase 1_5_4" << endl;
			for (size_t c = 0; c < helperIndexes.size(); c++)
			{
				for (size_t l = 0; l < currentLostLDPCChunkSymbols.size(); l++)
				{
					if (helperIndexes[c] == currentLostLDPCChunkSymbols[l])
					{
						helperIndexesfromBS.push_back(currentLostLDPCChunkSymbols[l]);
						break;
					}
				}
			}
			auto last = std::unique(helperIndexesfromBS.begin(), helperIndexesfromBS.end());
			// cout << "size of helperIndexesfromBS before erase operation in secondPhase: " << helperIndexesfromBS.size() << endl;
			helperIndexesfromBS.erase(last, helperIndexesfromBS.end());
			std::sort(helperIndexesfromBS.begin(), helperIndexesfromBS.end());
			//helperIndexesfromBS = intersect(helperIndexes, currentLostLDPCChunkSymbols);
			cout << "We are here in secondPhase 1_5_5" << endl;		
	
			// cout << "size of helperIndexes: " << helperIndexes.size() << endl; 		
			// cout << "size of helperIndexesfromBS: " << helperIndexesfromBS.size() << endl; 

			// helperIndexesfromNodes = helperIndexes;
			// c = 0;
			// while(helperIndexesfromNodes.size() > 0)
			// {
			// 	increment = 0;
			// 	for (size_t l = 1; l < helperIndexesfromBS.size(); l++)
			// 	{
			// 		if (helperIndexesfromNodes[c] == helperIndexesfromBS[l])
			// 		{
			// 			helperIndexesfromNodes.erase(std::remove(helperIndexesfromNodes.begin(), helperIndexesfromNodes.end(), helperIndexesfromNodes[c]), helperIndexesfromNodes.end());
			// 			increment = increment + 1;
			// 		}				
			// 	}
			// 	if (increment == 0)
			// 		c = c + 1;
			// 	//cout << "size of helperIndexesfromNodes: " << helperIndexesfromNodes.size() << endl; 
			// }

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
					helperIndexesfromNodes.push_back(helperIndexes[r]);			
			}

			//helperIndexesfromNodes.clear();
			//std::set_difference(helperIndexes.begin(), helperIndexes.end(), helperIndexesfromBS.begin(), helperIndexesfromBS.end(), std::inserter(helperIndexesfromNodes, helperIndexesfromNodes.begin()));
			//helperIndexesfromNodes = setdiff(helperIndexes, helperIndexesfromBS);
			cout << "We are here in secondPhase 1_5_6" << endl;
			if (helperIndexesfromNodes.size() != helperIndexes.size())
				cout << "Error in size(helperIndexesfromNodes)" << endl;

			// helperIndexesfromNodesReduced = helperIndexesReduced;
			// c = 0;
			// while (helperIndexesfromNodesReduced.size() > 0)
			// {
			// 	increment = 0;
			// 	for (size_t l = 1; l < helperIndexesfromBS.size(); l++)
			// 	{
			// 		if (helperIndexesfromNodesReduced[c] == helperIndexesfromBS[l])
			// 		{
			// 			helperIndexesfromNodesReduced.erase(std::remove(helperIndexesfromNodes.begin(), helperIndexesfromNodes.end(), helperIndexesfromNodes[c]), helperIndexesfromNodes.end());
			// 			increment = increment + 1;
			// 		}
			// 	}
			// 	if (increment == 0)
			// 		c = c + 1;
			// }

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

			//helperIndexesfromNodesReduced.clear();
			//std::set_difference(helperIndexesReduced.begin(), helperIndexesReduced.end(), helperIndexesfromBS.begin(), helperIndexesfromBS.end(), std::inserter(helperIndexesfromNodesReduced, helperIndexesfromNodesReduced.begin()));
			//helperIndexesfromNodesReduced = setdiff(helperIndexesReduced, helperIndexesfromBS);
			cout << "We are here in secondPhase 1_5_7" << endl;
			// cout << "tempIndex: " << tempIndex << endl;
			// cout << "size of encodedData[tempIndex]: " << encodedData[tempIndex].size() << endl;
			if (helperIndexes.size() == 1)
			{
				// cout << "size of encodedData[helperIndexes[0]]: " << encodedData[helperIndexes[0]].size() << endl;
				encodedData[failedSymbolID] = encodedData[helperIndexes[0]];
				// cout << "tempIndex: " << tempIndex << endl;
				// cout << "size of encodedData[tempIndex] 1: " << encodedData[tempIndex].size() << endl;
				// cout << "failedSymbolID: " << failedSymbolID << endl;
				// if (tempCheckSize > encodedData[failedSymbolID].size())
				// 	cout << "We are here 2 in secondPhase" << endl;
				//encodedData(failedSymbolID, :) = encodedData(helperIndexes, :);
			}
			else
			{
				helperData.clear();
				for (size_t c = 0; c < helperIndexes.size(); c++)
					helperData.push_back(encodedData[helperIndexes[c]]);

				// cout << "Size of temp: " << temp.size() << endl;
				temp.clear();
				temp.resize(helperData[0].size(), 0);
				//std::fill(temp.begin(), temp.end(), 0);
				// cout << "Size of temp: " << temp.size() << endl;


				for (size_t i = 0; i < helperData.size(); i++)
				{
					//temp.resize(helperData[i].size());
					for (size_t j = 0; j < helperData[i].size(); j++)
						temp[j] = (helperData[i][j]) ^ temp[j];
					//temp = bitxor(helperData(i, :), temp);
				}
				// cout << "size of temp: " << temp.size() << endl;
				encodedData[failedSymbolID] = temp;
				// cout << "tempIndex: " << tempIndex << endl;
				// cout << "size of encodedData[tempIndex] 2: " << encodedData[tempIndex].size() << endl;
				// cout << "failedSymbolID: " << failedSymbolID << endl;
				// if (tempCheckSize > encodedData[failedSymbolID].size())
				// 	cout << "We are here 3 in secondPhase" << endl;
				//for (int j = 0; j < encodedData[0].size(); j++)
				//{
				//	encodedData[failedSymbolID][j] = temp[j];
				//}
				//encodedData(failedSymbolID, :) = temp;
				strParameters.numberofReadedSymbolsfromNodesforLDPCRepair = strParameters.numberofReadedSymbolsfromNodesforLDPCRepair + helperIndexesfromNodesReduced.size() * encodedData[0].size();
			}
		}
		cout << "We are here in secondPhase 1_6" << endl;
		// cout << "failedSymbolID: " << failedSymbolID << endl;
		// cout << "tempIndex: " << tempIndex << endl;
		// cout << "size of encodedData[tempIndex]: " << encodedData[tempIndex].size() << endl;
		// cout << "encodedData[failedSymbolID][c]: " ;
		// for (int c = 0; c < 10; c++)
		// 	cout << encodedData[failedSymbolID][c] << " ";
		// cout << endl;
		std::vector<int> tempL{};
		for (size_t r = 0; r < L.size(); r++)
		{
			if (L[r] != failedSymbolID)
				tempL.push_back(L[r]);
		}
		L = tempL;
		//L = L(L ~= failedSymbolID);
		cout << "We are here in secondPhase 1_7" << endl;
		std::vector<int> tempCurrentLostLDPCChunkSymbols{};
		for (size_t r = 0; r < currentLostLDPCChunkSymbols.size(); r++)
		{
			if (currentLostLDPCChunkSymbols[r] != failedSymbolID)
				tempCurrentLostLDPCChunkSymbols.push_back(r);
		}
		currentLostLDPCChunkSymbols = tempCurrentLostLDPCChunkSymbols;
		//currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols(currentLostLDPCChunkSymbols ~= failedSymbolID);

		// cout << "size of R2 before erase operation in secondPhase: " << R2.size() << endl;
		R2.erase(R2.begin() + I);
		//R2(I, :) = [];

		// cout << "size of R2Reduced before erase operation in secondPhase: " << R2Reduced.size() << endl;
		R2Reduced.erase(R2Reduced.begin() + I);
		//R2Reduced(I, :) = [];
		cout << "We are here in secondPhase 1_8" << endl;
		for (size_t i = 0; i < repairedHelperSymbols.size(); i++)
		{
			int foundIndexHelper;
			for (size_t c = 0; c < L.size(); c++)
			{
				if (L[c] != repairedHelperSymbols[i])
					foundIndexHelper = c;
			}
			//foundIndexHelper = find(L == repairedHelperSymbols(i));

			// cout << "size of L before erase operation in secondPhase: " << L.size() << endl;
			L.erase(std::remove(L.begin(), L.end(), L[foundIndexHelper]), L.end());
			//L(foundIndexHelper) = [];

			// cout << "size of R2 before erase operation in secondPhase 2: " << R2.size() << endl;
			R2.erase(std::remove(R2.begin(), R2.end(), R2[foundIndexHelper]), R2.end());
			//R2(foundIndexHelper, :) = [];

			int foundAllIndexHelper;
			for (size_t c = 0; c < currentLostLDPCChunkSymbols.size(); c++)
			{
				if (currentLostLDPCChunkSymbols[c] != repairedHelperSymbols[i])
					foundAllIndexHelper = c;
			}
			//foundAllIndexHelper = find(currentLostLDPCChunkSymbols == repairedHelperSymbols(i));

			// cout << "size of currentLostLDPCChunkSymbols before erase operation in secondPhase: " << currentLostLDPCChunkSymbols.size() << endl;
			currentLostLDPCChunkSymbols.erase(std::remove(currentLostLDPCChunkSymbols.begin(), currentLostLDPCChunkSymbols.end(), currentLostLDPCChunkSymbols[foundAllIndexHelper]), currentLostLDPCChunkSymbols.end());
			//currentLostLDPCChunkSymbols(foundAllIndexHelper) = [];
		}
		cout << "We are here in secondPhase 1_9" << endl;
	}
	cout << "We are here in secondPhase 2" << endl;
	fclose(baseStationID);
	currentColumnIndex = currentColumnIndex + encodedData[0].size();
	// cout << "size of L at the end of SecondPhase: " << L.size() << endl;
	sprLocal.strParameters = strParameters;
	sprLocal.encodedData = encodedData;
	sprLocal.currentColumnIndex = currentColumnIndex;
	sprLocal.stopState = stopState;
	cout << "We are here in secondPhase 3" << endl;
	// cout << "At the end of SecondPhase: " << endl;
	// cout << "size of encodedData: " << encodedData.size() << endl;
	// for (size_t r = 0; r < encodedData.size(); r++)
	// {
	// 	cout << "size of encodedData[r]: " << encodedData[r].size() << endl;
	// }
	return sprLocal;
}
