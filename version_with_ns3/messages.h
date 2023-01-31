#ifndef messages_H
#define messages_H

// #include <string>
using namespace std;
using namespace ns3;
#include "userDefinedFunctions.h"

//Paketlerin türlerini nasıl ayırırız onunla ilgili kısım gerçekleştiriliyor burada
//NewComer node açısından repair için düşünüldü
enum MType
{
  //Burada ekstra olarak simülatör tarafından newComerNode belirlenirken sen newComerNode oldun diye boş düğüme buradakilerden farklı bir tag de gönderilebilir mesaj tipi olarak.
  REQUESTREPAIRFROMBS = 0, //BS'den requestRepair yapılabilir yani baz istasyonundan paket istenilebilir
  REQUESTREPAIRFROMUE = 1, //User end'den paket istenilebilir
  REPLYREPAIRFROMBS = 2, //BS'den bize cevaplar gelebilir. Yani baz istasyonundan paket gelirken tag bu olacak.
  REPLYREPAIRFROMUE = 3, //User end'den bize cevaplar gelebilir. Yani user end node'lardan paket gelirken tag bu olacak. 
  FIN = 4,
  REQUESTSENDINGFROMUETOBS = 5,
  REPLYSENDINGFROMUETOBS = 6,
  DUMMY =7 // Elif hocanın eklediği satır
};  

//Paketi oluştururken daha düzenli kaydetmek amacıyla kullanacağımız structure. Bu paket encoded veya encoded olmayan paket olabilir 
struct fileChunk
{ 
  enum MType MESSAGETYPE;
  int index;
  int blocksize;
  uint32_t target; //kime gidecek
  uint32_t source; //kimden geliyor
  int filesize;
  int dataSize;
  int totalIndex;
  int temp;
  uint8_t *buffer;//[1400];  //dosyadan okuyacağımız asıl verinin tutulduğu yer
  
  int casual;
  //std::string tempUsedEmptyNodeforRepair;
};

struct fileRepair
{ 
  enum MType MESSAGETYPE;
  int target;
  int source;
  int fileNamesize;
  char fileName[60];  
  
};	

//"Tamire Başla", "Bitir" gibisinden sadece sinyal mesajı göndermek istediğimizde kullanılan structure yapısı
struct fileSIGNAl // For only signal MEssages
{ 
  enum MType MESSAGETYPE;
  int target;
  int source;
};

struct finalFileParameters
{
  enum MType MESSAGETYPE;
  Ptr<Node> senderNode; 
  Ptr<Node> receiverNode;
  Ipv4Address senderAddress;
  Ipv4Address receiverAddress;
  uint16_t servPort;

  Ipv4InterfaceContainer ueIpIface; 
  std::vector<int> currentHelperNodeIndexes; 
  std::vector<std::string> inputFiles;
  int selectedHelperNodeIndex;
  int selectedEmptyNodeIndex;
  int quotient;
  std::string tempUsedEmptyNodeforRepair; 
  std::string baseStation;
  std::vector<int> failedSymbolIDsForRepairFromBS; 
  int maxColLength;
};

struct fileParameters
{
  enum MType MESSAGETYPE;
  Ptr<Node> senderNode; 
  Ptr<Node> receiverNode;
  Ipv4Address senderAddress;
  Ipv4Address receiverAddress;
  uint16_t servPort;

  Ipv4InterfaceContainer ueIpIface; 
  //std::vector<int> currentHelperNodeIndexes; 
  std::vector<std::string> inputFiles;
  int selectedHelperNodeIndex;
  int selectedEmptyNodeIndex;
  int quotient;
  std::string tempUsedEmptyNodeforRepair; 
  std::string baseStation;
  std::vector<int> failedSymbolIDsForRepairFromBS; 
  int maxColLength;

  std::vector<std::vector<int>> R1;
  std::vector<std::vector<int>> R2;
  std::vector<int> L;
  std::vector<int> helperNodes;
  int numberofRoundforBuffer;
  std::vector<int> currentLostLDPCChunkSymbols;
  struct strP strParameters;
  std::vector<int> unrepairedSymbolsfromNodes;
  std::vector<int> unrepairedSymbolsfromBS;
  std::vector<std::vector<int>> allEquationsR2;

  int foundOne;
  std::string repairedFile;
  std::vector<string> totalHelperFiles;
  int cols;
  std::vector<struct ns> nodeStr;
  std::vector<int> aliveLDPCStorageNodes;
  Ptr<Node> remoteHost;
  std::vector<int> allHelperNodeIndexes;
};

struct fileReturnings
{
  enum MType MESSAGETYPE;
  std::vector<string> totalHelperFiles;
  std::vector<struct ns> nodeStr;
  struct strP strParameters;
  std::vector<int> aliveLDPCStorageNodes;
};

typedef struct {
	int chunkIndex; 
	long start;
	long Nbytes;
} chunkInfoType;

//typedef struct {
//	chunkInfoType chunkInfo;
//} lookupTable;

//lookupTable **LookupTable;

#endif 