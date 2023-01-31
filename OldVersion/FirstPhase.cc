#include "userDefinedFunctions.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;

typedef struct firstPhaseReturns Struct;

Struct FirstPhase(std::vector<int> currentLostLDPCChunkSymbols, std::vector<int> L, std::vector<std::vector<int>> R1, std::vector<std::vector<int>> R2, struct strP strParameters, std::vector<int> unrepairedSymbolsfromNodes, std::vector<int> unrepairedSymbolsfromBS, std::vector<std::vector<uint8_t>> readedDatainBuffer, std::vector<std::vector<int>> allEquationsR2)
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
	std::vector<int>::iterator it; // = usedHelpers.begin(); // = unique(usedHelpers.begin(), usedHelpers.end());
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

	cout << "We are here in firstPhase 1" << endl;
	// cout << "size of R1: " << R1.size() << endl;

	// cout << "R2: " << endl;
	// for (size_t r = 0; r < R2.size(); r++)
	// {
	// 	for (size_t c = 0; c < R2[r].size(); c++)
	// 	{
	// 		cout << R2[r][c] << " " ;
	// 	}
	// 	cout << endl;
	// }

	// cout << "R2ReducedCopy: " << endl;
	// for (size_t r = 0; r < R2ReducedCopy.size(); r++)
	// {
	// 	for (size_t c = 0; c < R2ReducedCopy[r].size(); c++)
	// 	{
	// 		cout << R2ReducedCopy[r][c] << " " ;
	// 	}
	// 	cout << endl;
	// }

	while (!R1.empty())
	{
		// cout << "R1: " << endl;
		// for (size_t r = 0; r < R1.size(); r++)
		// {
		// 	for (size_t c = 0; c < R1[r].size(); c++)
		// 	{
		// 		cout << R1[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

		// cout << "R1ReducedCopy: " << endl;
		// for (size_t r = 0; r < R1ReducedCopy.size(); r++)
		// {
		// 	for (size_t c = 0; c < R1ReducedCopy[r].size(); c++)
		// 	{
		// 		cout << R1ReducedCopy[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

		// cout << "R2: " << endl;
		// for (size_t r = 0; r < R2.size(); r++)
		// {
		// 	for (size_t c = 0; c < R2[r].size(); c++)
		// 	{
		// 		cout << R2[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

		// cout << "R2ReducedCopy: " << endl;
		// for (size_t r = 0; r < R2ReducedCopy.size(); r++)
		// {
		// 	for (size_t c = 0; c < R2ReducedCopy[r].size(); c++)
		// 	{
		// 		cout << R2ReducedCopy[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

		helperSizes.clear();
		helperIndexes.clear();
		helperIndexesReduced.clear();
		R.clear();
		// Sorting R1 and R2
		//cout << "Size of R1: " << R1.size() << endl;
		cout << "We are here in firstPhase 1_1" << endl;
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
		cout << "We are here in firstPhase 1_2" << endl;
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
		cout << "We are here in firstPhase 1_3" << endl;
		//[M, I] = min(helperSizes);
		for (size_t c = 0; c < R1[I].size(); c++)
			R.push_back(R1[I][c]);
		//R = R1(I, :); 
		
		for (size_t c = 0; c < R1ReducedCopy[I].size(); c++)
			RReduced.push_back(R1ReducedCopy[I][c]);
		//RReduced = R1ReducedCopy(I, :);
		cout << "We are here in firstPhase 1_4" << endl;
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
		cout << "We are here in firstPhase 1_5" << endl;
		//helperIndexesReduced = RReduced(RReduced~= 0);
		std::fill(temp.begin(), temp.end(), 0);
		cout << "We are here in firstPhase 1_5_1" << endl;
		// cout << "size of helperIndexes:" << helperIndexes.size() << endl;
		// cout << "size of encodedData:" << encodedData.size() << endl;


		// cout << "helperIndexes: ";
		// for (size_t i = 0; i < helperIndexes.size(); i++)
		// 	cout << helperIndexes[i] << " ";
		// cout << endl;

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
			}
		}
		cout << "We are here in firstPhase 1_5_2" << endl;
		//helperData = encodedData(helperIndexes, :);
		usedHelpers.insert(usedHelpers.end(), helperIndexes.begin(), helperIndexes.end());
		//usedHelpers = [usedHelpers helperIndexes];
		cout << "We are here in firstPhase 1_6" << endl;
		sort(usedHelpers.begin(), usedHelpers.end());

		//it.clear();
		it = unique(usedHelpers.begin(), usedHelpers.end());
		usedHelpers.resize(distance(usedHelpers.begin(), it));
		cout << "We are here in firstPhase 1_7" << endl;
		// cout << "size of helperData: " << helperData.size() << endl;
		for (size_t i = 0; i < helperData.size(); i++)
		{
			//temp = (helperData[i]) ^ temp;
			for (size_t j = 0; j < helperData[i].size(); j++)
			{
				temp[j] = (helperData[i][j]) ^ temp[j];
			}
			//std::transform(a.begin(), a.end(), b.begin(), a.begin(), std::bit_xor<uint8_t>());
			//std::transform(a.begin(), a.end(), b.begin(), a.begin(), [](auto e1, auto e2) {return e1 ^ e2;});
			//std::transform(helperData[i].begin(), helperData[i].end(), temp.begin(), helperData[i].begin(), [](auto e1, auto e2) {return e1 ^ e2; });
		}
		//for i = 1:size(helperData, 1)
		//	temp = bitxor(helperData(i, :), temp);
		//end

		// for (size_t j = 0; j < encodedData[failedSymbolID].size(); j++)
		// {
		// 	encodedData[failedSymbolID][j] = temp[j];
		// }
		encodedData[failedSymbolID] = temp;
		strParameters.numberofReadedSymbolsfromNodesforLDPCRepair = strParameters.numberofReadedSymbolsfromNodesforLDPCRepair + helperIndexesReduced.size()*encodedData[0].size();
		
		// foundIndex.clear();
		// for (size_t c = 0; c < L.size(); c++)
		// {
		// 	if (L[c] == failedSymbolID)
		// 		foundIndex.push_back(c);
		// }
		// //foundIndex = find(L == failedSymbolID);
		// for (size_t c = 0; c < foundIndex.size(); c++)
		// {
		// 	L.erase(std::remove(L.begin(), L.end(), L[foundIndex[c]]), L.end());
		// 	//L(foundIndex) = [];
		// }
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
		cout << "We are here in firstPhase 1_8" << endl;
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

		// cout << "helperIndexes: ";
		// for (size_t i = 0; i < helperIndexes.size(); i++)
		// 	cout << helperIndexes[i] << " ";
		// cout << endl;

		// cout << "R1ReducedCopy before: " << endl;
		// for (size_t r = 0; r < R1ReducedCopy.size(); r++)
		// {
		// 	for (size_t c = 0; c < R1ReducedCopy[r].size(); c++)
		// 	{
		// 		cout << R1ReducedCopy[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

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

		// cout << "R1ReducedCopy after: " << endl;
		// for (size_t r = 0; r < R1ReducedCopy.size(); r++)
		// {
		// 	for (size_t c = 0; c < R1ReducedCopy[r].size(); c++)
		// 	{
		// 		cout << R1ReducedCopy[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

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
		cout << "We are here in firstPhase 2" << endl;
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
		cout << "We are here in firstPhase 3" << endl;
		// Add from R2 to R1
		deletedEquations.clear();
		tempR.clear();
		tempReduced.clear();
		helperSymbolIndexesR2.clear();
		v.clear();
		for (size_t ind = 0; ind < R2.size(); ind++)
		{
			tempR = R2[ind];
						
			// cout << "tempR before: ";
			// for (size_t i = 0; i < tempR.size(); i++)
			// 	cout << tempR[i] << " ";
			// cout << endl;

			// cout << "R2 before: " << endl;
			// for (size_t r = 0; r < R2.size(); r++)
			// {
			// 	for (size_t c = 0; c < R2[r].size(); c++)
			// 	{
			// 		cout << R2[r][c] << " " ;
			// 	}
			// 	cout << endl;
			// }
			// cout << "size of tempR before erase operation in firstPhase: " << tempR.size() << endl;
			tempR.erase(std::remove(tempR.begin(), tempR.end(), tempR[0]), tempR.end());

			// cout << "tempR after: ";
			// for (size_t i = 0; i < tempR.size(); i++)
			// 	cout << tempR[i] << " ";
			// cout << endl;

			// cout << "R2 after: " << endl;
			// for (size_t r = 0; r < R2.size(); r++)
			// {
			// 	for (size_t c = 0; c < R2[r].size(); c++)
			// 	{
			// 		cout << R2[r][c] << " " ;
			// 	}
			// 	cout << endl;
			// }

			tempReduced = R2ReducedCopy[ind];
			// cout << "size of tempReduced before erase operation in firstPhase: " << tempReduced.size() << endl;
			tempReduced.erase(std::remove(tempReduced.begin(), tempReduced.end(), tempReduced[0]), tempReduced.end());
			cout << "We are here in firstPhase 3_1" << endl;
			lostSymbol = R2[ind][0];
			for (size_t c = 0; c < tempR.size(); c++)
			{
				if (tempR[c] != -1)
					helperSymbolIndexesR2.push_back(c);
			}
			cout << "We are here in firstPhase 3_2" << endl;

			// cout << "helperSymbolIndexesR2: ";
			// for (size_t i = 0; i < helperSymbolIndexesR2.size(); i++)
			// 	cout << helperSymbolIndexesR2[i] << " ";
			// cout << endl;

			// cout << "currentLostLDPCChunkSymbols: ";
			// for (size_t i = 0; i < currentLostLDPCChunkSymbols.size(); i++)
			// 	cout << currentLostLDPCChunkSymbols[i] << " ";
			// cout << endl;

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
			cout << "We are here in firstPhase 3_3" << endl;
			// it = std::set_intersection(helperSymbolIndexesR2.begin(), helperSymbolIndexesR2.end(), currentLostLDPCChunkSymbols.begin(), currentLostLDPCChunkSymbols.end(), v.begin());
			// v.resize(it - v.begin());
			// if (v.size() <= 0)
			if (intersectionState == 0)
			{
				deletedEquations.push_back(ind);
				cout << "We are here in firstPhase 3_3_1_1" << endl;
				//for (int c = 0; c < tempR.size(); c++)
				//	R1[ind+1].push_back(tempR[c]);
				//for (int c = 0; c < tempReduced.size(); c++)
				//	R1ReducedCopy[ind + 1].push_back(tempReduced[c]);

				// cout << "tempR: ";
				// for (size_t i = 0; i < tempR.size(); i++)
				// 	cout << tempR[i] << " ";
				// cout << endl;

				R1.push_back(tempR);
				cout << "We are here in firstPhase 3_3_1_2" << endl;
				R1ReducedCopy.push_back(tempReduced);
				cout << "We are here in firstPhase 3_3_1" << endl;
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
				cout << "We are here in firstPhase 3_3_2" << endl;
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
				cout << "We are here in firstPhase 3_3_3" << endl;
				tempAllLostFromBS.clear();
				for (size_t c = 0; c < AllLostFromBS.size(); c++)
				{
					if (AllLostFromBS[c] != lostSymbol)
						tempAllLostFromBS.push_back(AllLostFromBS[c]);
				}
				AllLostFromBS.clear();
				AllLostFromBS = tempAllLostFromBS;
			}
			cout << "We are here in firstPhase 3_4" << endl;
		}
		cout << "We are here in firstPhase 4" << endl;
		// //dim2.erase(dim2.begin() + 9); // erase the 10th row
		// for (size_t i = 0; i < deletedEquations.size(); i++)
		// {
		// 	R2.erase(R2.begin() + deletedEquations[i]);
		// 	R2ReducedCopy.erase(R2ReducedCopy.begin() + deletedEquations[i]);
		// }	
		// //R2(deletedEquations, :) = [];
		// //R2ReducedCopy(deletedEquations, :) = [];
		// //unrepairedSymbolsfromBS(deletedEquations) = [];
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

				// if ((int)r != deletedEquations[i])
				// {
				// 	tempR2.push_back(R2[r]);
				// 	tempR2ReducedCopy.push_back(R2ReducedCopy[r]);
				// }
			}
			if (intState == 0)
			{
				tempR2.push_back(R2[r]);
				tempR2ReducedCopy.push_back(R2ReducedCopy[r]);
			}				
		}

		// cout << "tempR2 (R2): " << endl;
		// for (size_t r = 0; r < tempR2.size(); r++)
		// {
		// 	for (size_t c = 0; c < tempR2[r].size(); c++)
		// 	{
		// 		cout << tempR2[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }

		R2.clear();
		R2 = tempR2;
		R2ReducedCopy.clear();
		R2ReducedCopy = tempR2ReducedCopy;

		cout << "We are here in firstPhase 5" << endl;
		// cout << "size of R1 before erase operation in firstPhase: " << R1.size() << endl;
		R1.erase(R1.begin() + I);
		//R1(I, :) = [];
		// cout << "size of R1ReducedCopy before erase operation in firstPhase: " << R1ReducedCopy.size() << endl;
		R1ReducedCopy.erase(R1ReducedCopy.begin() + I);
		//R1ReducedCopy(I, :) = [];
		// cout << "size of unrepairedSymbolsfromNodes before erase operation in firstPhase: " << unrepairedSymbolsfromNodes.size() << endl;
		unrepairedSymbolsfromNodes.erase(std::remove(unrepairedSymbolsfromNodes.begin(), unrepairedSymbolsfromNodes.end(), unrepairedSymbolsfromNodes[I]), unrepairedSymbolsfromNodes.end());
		cout << "We are here in firstPhase 6" << endl;

		// cout << "size of R1: " << R1.size() << endl;
		// cout << "R1 at the end of loop: " << endl;
		// for (size_t r = 0; r < R1.size(); r++)
		// {
		// 	for (size_t c = 0; c < R1[r].size(); c++)
		// 	{
		// 		cout << R1[r][c] << " " ;
		// 	}
		// 	cout << endl;
		// }
	}
	cout << "We are here in firstPhase 7" << endl;
	fprLocal.strParameters = strParameters;
	// cout << "We are here in firstPhase 7_1" << endl;
	// cout << "size of encodedData: " << encodedData.size() << endl;
	fprLocal.encodedData = encodedData;
	// cout << "We are here in firstPhase 7_2" << endl;
	fprLocal.L = L;
	// cout << "We are here in firstPhase 7_3" << endl;
	fprLocal.currentLostLDPCChunkSymbols = currentLostLDPCChunkSymbols;
	// cout << "We are here in firstPhase 7_4" << endl;
	fprLocal.R2 = R2;
	// cout << "We are here in firstPhase 7_5" << endl;
	fprLocal.R2ReducedCopy = R2ReducedCopy;
	// cout << "We are here in firstPhase 7_6" << endl;
	fprLocal.unrepairedSymbolsfromNodes = unrepairedSymbolsfromNodes;
	// cout << "We are here in firstPhase 7_7" << endl;
	fprLocal.unrepairedSymbolsfromBS = unrepairedSymbolsfromBS;
	// cout << "We are here in firstPhase 7_8" << endl;
	fprLocal.usedHelpers = usedHelpers;
	cout << "We are here in firstPhase 8" << endl;
	return fprLocal;
}