#include "userDefinedFunctions.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iterator>
//#include <fstream>

using namespace std;

//sizeof(arr) = j*p;
//sizeof(arr[0]) = k*p;

// Function to calculate sum of specific row
//int row_sum(int **arr, int rowIndex)
//int row_sum(int *arr, int rowIndex)
int row_sum(std::vector<std::vector<int>> arr, int rowIndex)
{
	int sum = 0;
	// finding the row sum
	for (size_t i = 0; i < sizeof(arr[0]); ++i) 
	{
		// Add the element
		if (arr[rowIndex][i] == 1)
			sum = sum + arr[rowIndex][i];
		//if (arr[rowIndex* sizeof(arr[0]) +i] == 1)
		//	sum = sum + arr[rowIndex* sizeof(arr[0]) +i];
	}
	return sum;
}

// Function to calculate sum of specific column
//int column_sum(int **arr, int columnIndex)
//int column_sum(int *arr, int columnIndex)
int column_sum(std::vector<std::vector<int>> arr, int columnIndex)
{
	int sum = 0;

	// finding the column sum
	for (size_t i = 0; i < sizeof(arr); ++i) 
	{
		// Add the element
		if (arr[i][columnIndex] == 1)
			sum = sum + arr[i][columnIndex];
		//if (arr[i+columnIndex* sizeof(arr)] == 1)
		//	sum = sum + arr[i+columnIndex* sizeof(arr)];
	}
	return sum;
}

void display2DVector(std::vector<std::vector<int>> a)
{
	for (size_t i = 0; i < a.size(); ++i)
	{
		for (size_t j = 0; j < a[0].size(); ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void display1DVector(std::vector<int> a)
{
	for (size_t i = 0; i < a.size(); ++i)
		cout << a[i] << " ";
	cout << endl;
}

void callHildegard(double delta, int N, int nOriginal, int kOriginal, int p, int numberofInitialNodes, int numberofInitialLDPCStorageNodes, std::string fileNameAlg1, std::string fileNameAlg2)
{
	int j, k;
	std::vector<int> numberofWCsforH, numberofWRsforH, numberofWCsforG, numberofWRsforG;
	j = (nOriginal - kOriginal) / p;
	k = nOriginal / p;

	std::vector<std::vector<int>> H(j*p, std::vector<int>(k*p));
	std::vector<std::vector<int>> G(j*p, std::vector<int>(k*p));
/*	for (int i = 0; i < j*p; i++)
	{ 
		H[i].resize(k*p);
		G[i].resize(k*p);
	}*/
	//int **H = generateH_Array_LDPC(p, j, k);
	//int **G = H;

/*	cout << "n is " << nOriginal << endl;
	cout << "k is " << kOriginal << endl;
	cout << "p is " << p << endl;
	cout << "j is " << j << endl;
	cout << "k is " << k << endl;*/

	// cout << "H before:" << endl;
	// display2DVector(H);

	H = generateH_Array_LDPC(p, j, k);
	G = H;

	cout << "H:" << endl;
	display2DVector(H);

	int sumofWcforH, sumofWrforH, sumofWcforG, sumofWrforG;
	for (size_t co = 0; co < H[0].size(); co++)
	{
		sumofWcforH = 0;
		for (size_t ro = 0; ro < H.size(); ro++)
		{
			if(H[ro][co] == 1)
				sumofWcforH += 1; 
		}
		numberofWCsforH.push_back(sumofWcforH);
	}

	for (size_t ro = 0; ro < H.size(); ro++)
	{
		sumofWrforH = 0;
		for (size_t co = 0; co < H[0].size(); co++)
		{
			if(H[ro][co] == 1)
				sumofWrforH += 1; 
		}
		numberofWRsforH.push_back(sumofWrforH);
	}

	for (size_t co = 0; co < G[0].size(); co++)
	{
		sumofWcforG = 0;
		for (size_t ro = 0; ro < G.size(); ro++)
		{
			if(H[ro][co] == 1)
				sumofWcforG += 1; 
		}
		numberofWCsforG.push_back(sumofWcforG);
	}

	for (size_t ro = 0; ro < G.size(); ro++)
	{
		sumofWrforG = 0;
		for (size_t co = 0; co < G[0].size(); co++)
		{
			if(H[ro][co] == 1)
				sumofWrforG += 1; 
		}
		numberofWRsforG.push_back(sumofWrforG);
	}

/*	//for (int co = 1; co < sizeof(H[0]); co++)
	for (size_t co = 1; co < H[0].size(); co++)
		numberofWCsforH.insert(numberofWCsforH.begin() + co, column_sum(H, co));

	//for (int ro = 1; ro < sizeof(H); ro++)
	for (size_t ro = 1; ro < H.size(); ro++)
		numberofWRsforH.insert(numberofWRsforH.begin() + ro, row_sum(H, ro));

	//for (int co = 1; co < sizeof(G[0]); co++)
	for (size_t co = 1; co < G[0].size(); co++)
		numberofWCsforG.insert(numberofWCsforG.begin() + co, column_sum(G, co));

	//for (int ro = 1; ro < sizeof(G); ro++)
	for (size_t ro = 1; ro < G.size(); ro++)
		numberofWRsforG.insert(numberofWRsforG.begin() + ro, row_sum(G, ro));*/

	// cout<<"Second"<<endl;
	// cout << "numberofWCsforH:" << endl;
	// display1DVector(numberofWCsforH);
	// cout << "numberofWRsforH:" << endl;
	// display1DVector(numberofWRsforH);
	// cout << "numberofWCsforG:" << endl;
	// display1DVector(numberofWCsforG);
	// cout << "numberofWRsforG:" << endl;
	// display1DVector(numberofWRsforG);

	//M = size(G, 1);
	//limit = 10000;
	[[maybe_unused]] int numberofRoundforBuffer = 10000;
	//lambda = 1;
	//a = M*lambda;
	[[maybe_unused]] int a = 1;                              //Arrival rate
	[[maybe_unused]] int b = 1;                              //Departure rate
	//N = 100;                              //Length of simulation
	//numberofInitialNodes = 40;            //Initial number of nodes in the cell
	//numberofInitialLDPCStorageNodes = 8;
	//h = 7;                                //Download locality
	//r = 7;                                //Repair locality
	//w = 10;                               //Request rate
	//delta = 0.9;                          //Interval time between two repairs
	//delta = ones(1, N + M) * 0.2;         //Interval time between two repairs
	//alpha = 100;                          //Each storage node is exactly alpha bits(bytes)

	//string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen/";
	string root_directory = "scratch/testFolder";
	string rawFileName = root_directory + "/TestFile_128KB.bin";
	//string rawFileName = "TestFile_128KB.bin";
	time_t startTimeSimulator, endTimeSimulator; 
	startTimeSimulator = time(0);
	hildegardVonBingen(H, G, N, a, b, numberofInitialNodes, numberofInitialLDPCStorageNodes, delta, rawFileName, numberofRoundforBuffer, p, j, k, fileNameAlg1, fileNameAlg2);
	endTimeSimulator = time(0);
	[[maybe_unused]] double elapsedTimeSimulator = difftime(startTimeSimulator, endTimeSimulator);

	cout << "We are here in callHildegard after hildegardVonBingen" << endl;

	//string root_directory = "C:\\Users/Erdi/Documents/Visual Studio 2015/Projects/HildegardvonBingen/HildegardvonBingen";
	//string root_directory = "scratch/testFolder";
	string basic_directory = root_directory + "/files";
	FILE * bookofAccountIDV2;
	FILE * bookofAccountIDV3;

	string current_directory = basic_directory + "/ledgerV2.txt";	
	//std::ofstream bookofAccountIDV2(current_directory);
	//if (bookofAccountIDV2.is_open())
	//{
	//	bookofAccountIDV2 << "Column weights of H matrix\n";
	//	std::ostream_iterator<std::string> output_iterator(bookofAccountIDV2, " ");
	//	std::copy(numberofWCsforH.begin(), numberofWCsforH.end(), output_iterator);
	//	bookofAccountIDV2 << "\t";

	//	bookofAccountIDV2 << "\nRow weights of H matrix\n";
	//	std::copy(numberofWRsforH.begin(), numberofWRsforH.end(), output_iterator);
	//	bookofAccountIDV2 << "\t\n\n\n";

	//	bookofAccountIDV2 << "\nColumn weights of G matrix\n";
	//	std::copy(numberofWCsforG.begin(), numberofWCsforG.end(), output_iterator);
	//	bookofAccountIDV2 << "\t";

	//	bookofAccountIDV2 << "\nRow weights of G matrix\n";
	//	std::copy(numberofWRsforG.begin(), numberofWRsforG.end(), output_iterator);
	//	bookofAccountIDV2 << "\t";

	//	bookofAccountIDV2.close();
	//}
	bookofAccountIDV2 = fopen(current_directory.c_str(), "a");
	if (bookofAccountIDV2 != NULL)
	{
		fprintf(bookofAccountIDV2, "Column weights of H matrix\n");
		for (size_t i = 0; i < numberofWCsforH.size(); i++)
			fprintf(bookofAccountIDV2, "%d ", numberofWCsforH[i]);
		fprintf(bookofAccountIDV2, "\t");
		//fprintf(bookofAccountIDV2, "%d\t", numberofWCsforH);
		fprintf(bookofAccountIDV2, "\nRow weights of H matrix\n");
		for (size_t i = 0; i < numberofWRsforH.size(); i++)
			fprintf(bookofAccountIDV2, "%d ", numberofWRsforH[i]);
		fprintf(bookofAccountIDV2, "\t");
		//fprintf(bookofAccountIDV2, "%d\t", numberofWRsforH);
		fprintf(bookofAccountIDV2, "\n\n\n");
		fprintf(bookofAccountIDV2, "\nColumn weights of G matrix\n");
		for (size_t i = 0; i < numberofWCsforG.size(); i++)
			fprintf(bookofAccountIDV2, "%d ", numberofWCsforG[i]);
		fprintf(bookofAccountIDV2, "\t");
		//fprintf(bookofAccountIDV2, "%d\t", numberofWCsforG);
		fprintf(bookofAccountIDV2, "\nRow weights of G matrix\n");
		for (size_t i = 0; i < numberofWRsforG.size(); i++)
			fprintf(bookofAccountIDV2, "%d ", numberofWRsforG[i]);
		fprintf(bookofAccountIDV2, "\t");
		//fprintf(bookofAccountIDV2, "%d\t", numberofWRsforG);
		fclose(bookofAccountIDV2);
	}

	current_directory = basic_directory + "/ledgerV4.txt";

	//std::ofstream bookofAccountIDV3(current_directory);
	//if (bookofAccountIDV3.is_open())
	//{
	//	bookofAccountIDV3 << "Column weights of H matrix\n";
	//	std::ostream_iterator<std::string> output_iterator(bookofAccountIDV3, " ");
	//	std::copy(numberofWCsforH.begin(), numberofWCsforH.end(), output_iterator);
	//	bookofAccountIDV3 << "\t";

	//	bookofAccountIDV3 << "\nRow weights of H matrix\n";
	//	std::copy(numberofWRsforH.begin(), numberofWRsforH.end(), output_iterator);
	//	bookofAccountIDV3 << "\t\n\n\n";

	//	bookofAccountIDV3 << "\nColumn weights of G matrix\n";
	//	std::copy(numberofWCsforG.begin(), numberofWCsforG.end(), output_iterator);
	//	bookofAccountIDV3 << "\t";

	//	bookofAccountIDV3 << "\nRow weights of G matrix\n";
	//	std::copy(numberofWRsforG.begin(), numberofWRsforG.end(), output_iterator);
	//	bookofAccountIDV3 << "\t";

	//	bookofAccountIDV3.close();
	//}

	bookofAccountIDV3 = fopen(current_directory.c_str(), "a");
	if (bookofAccountIDV3 != NULL)
	{
		fprintf(bookofAccountIDV3, "Column weights of H matrix\n");
		for (size_t i = 0; i < numberofWCsforH.size(); i++)
			fprintf(bookofAccountIDV3, "%zu ", i);
		fprintf(bookofAccountIDV3, "\t");
		//fprintf(bookofAccountIDV3, "%d\t", numberofWCsforH);
		fprintf(bookofAccountIDV3, "\nRow weights of H matrix\n");
		for (size_t i = 0; i < numberofWRsforH.size(); i++)
			fprintf(bookofAccountIDV3, "%zu ", i);
		fprintf(bookofAccountIDV3, "\t");
		//fprintf(bookofAccountIDV3, "%d\t", numberofWRsforH);
		fprintf(bookofAccountIDV3, "\n\n\n");
		fprintf(bookofAccountIDV3, "\nColumn weights of G matrix\n");
		for (size_t i = 0; i < numberofWCsforG.size(); i++)
			fprintf(bookofAccountIDV3, "%zu ", i);
		fprintf(bookofAccountIDV3, "\t");
		//fprintf(bookofAccountIDV3, "%d\t", numberofWCsforG);
		fprintf(bookofAccountIDV3, "\nRow weights of G matrix\n");
		for (size_t i = 0; i < numberofWRsforG.size(); i++)
			fprintf(bookofAccountIDV3, "%zu ", i);
		fprintf(bookofAccountIDV3, "\t");
		//fprintf(bookofAccountIDV3, "%d\t", numberofWRsforG);
		fclose(bookofAccountIDV3);
	}

	fcloseall();
	cout << "We are at the end of callHildegard" << endl;
	// exit(0);
}