#include <string>
#include <vector>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
//using namespace std;
using namespace ns3;

#ifndef USERDEFINEDFUNCTIONS_H
#define USERDEFINEDFUNCTIONS_H

class MyApp : public Application
{
public:
  MyApp ();
  virtual ~MyApp ();

  /**
   * Register this type.
   * \return The TypeId.
   */
  static TypeId GetTypeId (void);
  void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void ScheduleTx (void);
  void SendPacket (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  uint32_t        m_packetSize;
  uint32_t        m_nPackets;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;
};

struct strP {
	int numberofReadedSymbolsfromBSforLDPCRepair = 0;
	int numberofReadedSymbolsfromNodesforLDPCRepair = 0;
	int numberofLDPCHelpers = 0;
	double startTimeLDPCRepair = 0.0;
	double endTimeLDPCRepair = 0.0;
	double startTimeLDPCEncoding = 0.0;
	double endTimeLDPCEncoding = 0.0;
	int numberofLDPCRepairswithBaseStation = 0;
	int numberofLDPCRepairswithoutBaseStation = 0;
	int numberofLDPCRepairswithOnlyBaseStation = 0;
	double repairTimeforRemainderSymbols = 0.0;
	std::vector<std::string> usedNodes{};
};

struct ns {
	int nodeID = 0;
	int logicalNodeID = 0;
	std::string fileName = "";
	double arrivalTime = 0;
	double serviceTime = 0;
	double departureTime = 0;
	int isLive = 0;
	int encodingType = 0;
	int repairedNodeID = 0;
	double fileSize = 0;
};

struct departureReturns
{
	std::vector<struct ns> nodeStr;
	std::vector<int> leavingNodes;
	int numberofLDPCStorageNodes;
	std::vector<int> allDepartureNodes;
	std::vector<int> aliveLDPCStorageNodes;
	int numberofLostNodesforInterval;
};

struct repairReturns
{
	int isMultipleRepair;
	std::vector<struct ns> nodeStr;
	int numberofLDPCStorageNodes;
	struct strP strParameters;
	struct strP strParameters2;
	std::vector<int> leavingLDPCStorageNodes;
	std::vector<int> aliveLDPCStorageNodes;
};

struct encodingReturns
{
	int blockSize;
	std::vector<int> aliveLDPCStorageNodes;
	int totalEncodedData;
	std::vector<int> ldpcFileSizes;
	std::vector<struct ns> nodeStr;
};

struct singleRepairAlgorithmV1Returns 
{
	std::vector<std::string> totalHelperFiles;
	std::vector<struct ns> nodeStr;
	struct strP strParameters;
	std::vector<int> aliveLDPCStorageNodes;
};

struct generateHelpersReturns
{
	std::vector<int> helperSymbolIndexes;
	std::vector<std::vector<int>> allEquationsR2;
};

struct firstPhaseReturns
{
	struct strP strParameters;
	std::vector<std::vector<uint8_t>> encodedData;
	std::vector<int> L;
	std::vector<int> currentLostLDPCChunkSymbols;
	std::vector<std::vector<int>> R2;
	std::vector<std::vector<int>> R2ReducedCopy;
	std::vector<int> unrepairedSymbolsfromNodes;
	std::vector<int> unrepairedSymbolsfromBS;
	std::vector<int> usedHelpers;
};

struct secondPhaseReturns
{
	struct strP strParameters;
	std::vector<std::vector<uint8_t>> encodedData;
	int currentColumnIndex;
	int stopState;
};

struct updateRecoveryEquationsReturns
{
	std::vector<int> selectedEquation;
	std::vector<int> selectedEquationReduced;
};

//void display2DVector(std::vector<std::vector<int>>);

//void display1DVector(std::vector<int>);

void runLDPCSims();

void callHildegard(double, int, int, int, int, int, int, std::string, std::string);

std::vector<std::vector<int>> generateH_Array_LDPC(int, int, int);

void hildegardVonBingen(std::vector<std::vector<int>>, std::vector<std::vector<int>>, int, int, int, int, int, double, std::string, int, int, int, int, std::string, std::string);

struct encodingReturns ldpcEncodingforArrrayLDPC(std::vector<std::vector<int>>, int, std::string, std::string, int, int, int, int, std::vector<struct ns>);

std::vector<struct ns> processArrival(int, std::vector<struct ns>, std::vector<double>, std::vector<double>);

struct departureReturns processDeparture(int, std::vector<struct ns>, int, std::vector<int>, int, std::vector<int>, int, std::vector<int>, std::vector<int>, int);

struct repairReturns processRepair(std::vector<std::vector<int>>, std::vector<struct ns>, int, std::vector<int>, int, int, double, std::vector<int>, struct strP, struct strP, int, double, std::vector<int>);

struct singleRepairAlgorithmV1Returns LDPCSingleRepairAlgorithmV1(int, std::string, std::vector<int>, std::vector<std::string>, int, int, std::vector<std::vector<int>>, std::vector<ns> nodeStr, std::vector<int>, struct strP, int, std::vector<int>, double, int);

struct generateHelpersReturns GenerateHelpers(std::vector<std::vector<int>>, int, std::vector<int>, std::vector<std::vector<int>>);

struct firstPhaseReturns FirstPhase(std::vector<int>, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>, struct strP, std::vector<int>, std::vector<int>, std::vector<std::vector<uint8_t>>, std::vector<std::vector<int>>);

struct updateRecoveryEquationsReturns updateRecoveryEquations(int, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>);

struct secondPhaseReturns SecondPhase(std::vector<int>, std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>, struct strP, std::vector<std::vector<uint8_t>>, int, int, int, int);


#endif /* USERDEFINEDFUNCTIONS_H */