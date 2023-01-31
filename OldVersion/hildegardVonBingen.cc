#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
#include <ctime>
#include <numeric>
#include <random>
#include <math.h> 
#include <list>

#include "userDefinedFunctions.h"

using namespace std;

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
	encodingRs = ldpcEncodingforArrrayLDPC(G, numberofInitialLDPCStorageNodes, rawFileName, baseStation_file, numberofRoundforBuffer, p, m, n, nodeStr);
	
	blockSize = encodingRs.blockSize;
	aliveLDPCStorageNodes = encodingRs.aliveLDPCStorageNodes;
	totalEncodedData = encodingRs.totalEncodedData;
	ldpcFileSizes = encodingRs.ldpcFileSizes;
	nodeStr = encodingRs.nodeStr;

	// cout << "After Encoding:" << endl;
	// for(size_t i = 0; i < nodeStr.size(); i++)
	// {
	// 	// if (nodeStr[i].encodingType == 1 && nodeStr[i].isLive == 0)
	// 	// {
	// 		cout << "nodeStr[i].nodeID: " << nodeStr[i].nodeID << endl;
	// 		cout << "nodeStr[i].logicalNodeID: " << nodeStr[i].logicalNodeID << endl;
	// 		cout << "nodeStr[i].fileName: " << nodeStr[i].fileName << endl;
	// 		cout << "nodeStr[i].isLive: " << nodeStr[i].isLive << endl;
	// 		cout << "nodeStr[i].encodingType: " << nodeStr[i].encodingType << endl;
	// 		cout << "nodeStr[i].repairedNodeID: " << nodeStr[i].repairedNodeID << endl;
	// 	// }
	// }
	// cout << endl;

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

	while (repairTimes.empty() == 0 && arrivalTimes.empty() == 0)
	{
		stateRepair = 0;
		iii = iii + 1;
		
		// double arrv = arrivalTimes.front();
		// double sdep = sortedDepartureTimes.front();

		if (arrivalTimes.front() < sortedDepartureTimes.front()) // Next point is arrival
		{
			if (arrivalTimes.front() < repairTimes.front())
			{
				numberOfNodesIntheCell = numberOfNodesIntheCell + 1;    // Increase cell size

				if (arrivalNodeIndex >= numberofInitialNodes)
				{
					nodeStr = processArrival(arrivalNodeIndex, nodeStr, arrivalTimes, serviceTimes);
					numberofArrivalNodesforInterval = numberofArrivalNodesforInterval + 1;

					// cout << "After Process Arrival:" << endl;
					// for(size_t i = 0; i < nodeStr.size(); i++)
					// {
					// 	// if (nodeStr[i].encodingType == 1 && nodeStr[i].isLive == 0)
					// 	// {
					// 		cout << "nodeStr[i].nodeID: " << nodeStr[i].nodeID << endl;
					// 		cout << "nodeStr[i].logicalNodeID: " << nodeStr[i].logicalNodeID << endl;
					// 		cout << "nodeStr[i].fileName: " << nodeStr[i].fileName << endl;
					// 		cout << "nodeStr[i].isLive: " << nodeStr[i].isLive << endl;
					// 		cout << "nodeStr[i].encodingType: " << nodeStr[i].encodingType << endl;
					// 		cout << "nodeStr[i].repairedNodeID: " << nodeStr[i].repairedNodeID << endl;
					// 	// }
					// }
					// cout << endl;
				}
				else
				{
					if(arrivalNodeIndex < numberofInitialLDPCStorageNodes)
					{
						nodeStr[arrivalNodeIndex].arrivalTime = arrivalTimes.front();
						nodeStr[arrivalNodeIndex].serviceTime = serviceTimes.front();
						nodeStr[arrivalNodeIndex].departureTime = arrivalTimes.front() + serviceTimes.front();
					}
					else
					{
						nodeStr = processArrival(arrivalNodeIndex, nodeStr, arrivalTimes, serviceTimes);
						// nodeStr[arrivalNodeIndex].nodeID = arrivalNodeIndex;
						// nodeStr[arrivalNodeIndex].logicalNodeID = 0;
						// nodeStr[arrivalNodeIndex].fileName = "";
						// nodeStr[arrivalNodeIndex].arrivalTime = arrivalTimes.front();
						// nodeStr[arrivalNodeIndex].serviceTime = serviceTimes.front();
						// nodeStr[arrivalNodeIndex].departureTime = arrivalTimes.front() + serviceTimes.front();
						// nodeStr[arrivalNodeIndex].isLive = 1;
						// nodeStr[arrivalNodeIndex].encodingType = 0;
						// nodeStr[arrivalNodeIndex].repairedNodeID = 0;
						// nodeStr[arrivalNodeIndex].fileSize = 0;
					}

				}
				arrivalNodeIndex = arrivalNodeIndex + 1;
				// Remove First Element From Vector
				cout << "We are here in loop" << endl;
				// cout << "size of arrivalTimes: " << arrivalTimes.size() << endl;
				// cout << "size of serviceTimes: " << serviceTimes.size() << endl;
				// cout << "size of arrivalTimes before erase operation in hildegardVonBingen: " << arrivalTimes.size() << endl;
				arrivalTimes.erase(arrivalTimes.begin());      // Next arrival time is passed
				cout << "We are here in loop 2" << endl;
				// cout << "size of serviceTimes before erase operation in hildegardVonBingen: " << serviceTimes.size() << endl;
				serviceTimes.erase(serviceTimes.begin());      // Next service time is passed
				// cout << "We are here in loop 3" << endl;
			}
			else
				stateRepair = 1;
			cout << "We are here in loop 4" << endl;
		}
		else             // Next point is departure
		{
			if (sortedDepartureTimes.front() < repairTimes.front())
			{
				numberOfNodesIntheCell = numberOfNodesIntheCell - 1;    // Decrease cell size
				// departureNodeIndex = departureNodeIndex + 1;
				// counter = counter + 1;
				//counterLeavingNodes = counterLeavingNodes + 1;
				cout << "We are here in loop 5" << endl;
				// cout << "size of arrivalTimes: " << arrivalTimes.size() << endl;
				// cout << "size of serviceTimes: " << serviceTimes.size() << endl;
				// cout << "size of sortedDepartureTimes: " << sortedDepartureTimes.size() << endl;
				departureRs = processDeparture(departureNodeIndex, nodeStr, counter, allDepartureNodes, counterLeavingNodes, leavingNodes, numberofLDPCStorageNodes, sortedDepartureNodeIndexes, aliveLDPCStorageNodes, numberofLostNodesforInterval);
				//[nodeStr, leavingNodes, numberofLDPCStorageNodes, allDepartureNodes, aliveLDPCStorageNodes, numberofLostNodesforInterval] = processDeparture(departureNodeIndex, nodeStr, counter, allDepartureNodes, counterLeavingNodes, leavingNodes, numberofLDPCStorageNodes, sortedDepartureNodeIndexes, aliveLDPCStorageNodes, numberofLostNodesforInterval);
				cout << "We are here in loop 6" << endl;
				departureNodeIndex = departureNodeIndex + 1;
				counter = counter + 1;
				counterLeavingNodes = counterLeavingNodes + 1;

				nodeStr = departureRs.nodeStr;
				leavingNodes = departureRs.leavingNodes;
				numberofLDPCStorageNodes = departureRs.numberofLDPCStorageNodes;
				allDepartureNodes = departureRs.allDepartureNodes;
				aliveLDPCStorageNodes = departureRs.aliveLDPCStorageNodes;
				numberofLostNodesforInterval = departureRs.numberofLDPCStorageNodes;

				// cout << "After Process Departure:" << endl;
				// for(size_t i = 0; i < nodeStr.size(); i++)
				// {
				// 	// if (nodeStr[i].encodingType == 1 && nodeStr[i].isLive == 0)
				// 	// {
				// 		cout << "nodeStr[i].nodeID: " << nodeStr[i].nodeID << endl;
				// 		cout << "nodeStr[i].logicalNodeID: " << nodeStr[i].logicalNodeID << endl;
				// 		cout << "nodeStr[i].fileName: " << nodeStr[i].fileName << endl;
				// 		cout << "nodeStr[i].isLive: " << nodeStr[i].isLive << endl;
				// 		cout << "nodeStr[i].encodingType: " << nodeStr[i].encodingType << endl;
				// 		cout << "nodeStr[i].repairedNodeID: " << nodeStr[i].repairedNodeID << endl;
				// 	// }
				// }
				// cout << endl;

				// cout << "size of sortedDepartureTimes before erase operation in hildegardVonBingen: " << sortedDepartureTimes.size() << endl;
				sortedDepartureTimes.erase(sortedDepartureTimes.begin());               // Next departure time is passed    
			}
			else
				stateRepair = 1;
		}
		cout << "We are here in loop 7" << endl;
		if (stateRepair == 1)
		{
			cout << "We are here in hildegardVonBingen before processRepair" << endl;
			repairRs = processRepair(Hsys, nodeStr, counterLeavingNodes, leavingNodes, numberofLDPCStorageNodes, numberofInitialLDPCStorageNodes, baseStationSize, ldpcFileSizes, strParameters, strParameters2, numberofRoundforBuffer, blockSize, aliveLDPCStorageNodes);
			cout << "We are here in hildegardVonBingen after processRepair" << endl;
			isMultipleRepair = repairRs.isMultipleRepair;
			nodeStr = repairRs.nodeStr;
			numberofLDPCStorageNodes = repairRs.numberofLDPCStorageNodes;
			strParameters = repairRs.strParameters;
			strParameters2 = repairRs.strParameters2;
			leavingLDPCStorageNodes = repairRs.leavingLDPCStorageNodes;
			aliveLDPCStorageNodes = repairRs.aliveLDPCStorageNodes;
			cout << "We are here in hildegardVonBingen 2" << endl;
			// cout << "After Process Repair:" << endl;
			// for(size_t i = 0; i < nodeStr.size(); i++)
			// {
			// 	// if (nodeStr[i].encodingType == 1 && nodeStr[i].isLive == 0)
			// 	// {
			// 		cout << "nodeStr[i].nodeID: " << nodeStr[i].nodeID << endl;
			// 		cout << "nodeStr[i].logicalNodeID: " << nodeStr[i].logicalNodeID << endl;
			// 		cout << "nodeStr[i].fileName: " << nodeStr[i].fileName << endl;
			// 		cout << "nodeStr[i].isLive: " << nodeStr[i].isLive << endl;
			// 		cout << "nodeStr[i].encodingType: " << nodeStr[i].encodingType << endl;
			// 		cout << "nodeStr[i].repairedNodeID: " << nodeStr[i].repairedNodeID << endl;
			// 	// }
			// }
			// cout << endl;

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
					timeforRepairperNode = timeforRepairperNode + strParameters.endTimeLDPCRepair / leavingLDPCStorageNodes.size();
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
			cout << "We are here in hildegardVonBingen 3" << endl;
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
			cout << "We are here in hildegardVonBingen 4" << endl;
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
			cout << "We are here in hildegardVonBingen 5" << endl;
			counterLeavingNodes = 0;
			leavingNodes.clear();
			// cout << "size of repairTimes before erase operation in hildegardVonBingen: " << repairTimes.size() << endl;
			repairTimes.erase(repairTimes.begin());
			cout << "We are here in hildegardVonBingen 6" << endl;
			// cout << "stateRepair: " << stateRepair << endl;
		}
	}
	cout << "We are here in hildegardVonBingen 7" << endl;
	ldpcFileSize = totalEncodedData / numberofInitialLDPCStorageNodes;
	averageTimeforRepairsperNode = timeforRepairperNode / (double)numberofRepairs;
	averageTimeforRepairsResidualperNode = timeforRepairResidualperNode / (double)numberofRepairs;
	averageTimeforRepairsperSymbol = averageTimeforRepairsperNode / ldpcFileSize;
	averageTimeforRepairsResidualperSymbol = averageTimeforRepairsResidualperNode / ldpcFileSize;
	numberofTotalLDPCRepairs = strParameters.numberofLDPCRepairswithBaseStation + strParameters.numberofLDPCRepairswithoutBaseStation + strParameters.numberofLDPCRepairswithOnlyBaseStation;
	cout << "We are here in hildegardVonBingen 8" << endl;
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
	cout << "We are here in hildegardVonBingen 9" << endl;
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
			fprintf(allFilesResultsAlg1, "%.6f\n", (double)totalEncodedData);
			fclose(allFilesResultsAlg1);
		}
	}
	cout << "We are here in hildegardVonBingen 10" << endl;
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
			fprintf(allFilesResultsAlg2, "%.6f\n", (double)totalEncodedData);
			fclose(allFilesResultsAlg2);
		}
	}
	cout << "We are here in hildegardVonBingen 11" << endl;
}
