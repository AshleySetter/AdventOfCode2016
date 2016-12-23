#include <iostream>
#include <time.h>
#include <string>
#include <openssl/md5.h>
#include <cstring>

int main(){
  int timingI;
  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;  
  int NumRuns = 5;
  
  StartTime = clock();
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    std::string DoorID = "abc";
    unsigned char Hash[MD5_DIGEST_LENGTH];
    char mdString[33];
    int i;
    bool FiveZeros = false;
    int counter = -1;
    std::string StringToHash;
    char CharArrayToHash[50]; // allocates space in memory for 50 chars
    std::string Number;
    char Password[9] = "--------";
    bool DoneGettingPassword = false;
    int numberOfLettersSolved = 0;
    int LetterPosition;
    while (!DoneGettingPassword) {
      FiveZeros = false;
      std::cout << Password << "\r";
      std::cout.flush();
      while (!FiveZeros){
	counter++;
	StringToHash = DoorID + std::to_string(counter);
	for (i=0; i < StringToHash.length(); i++){
	  CharArrayToHash[i] = StringToHash[i];
	}
      
	MD5((unsigned char*)&CharArrayToHash, StringToHash.length(), (unsigned char*)&Hash);
	//      std::cout << CharArrayToHash << "\n";
	for (i = 0; i < 16; i++){
	  sprintf(&mdString[i*2], "%02x", (unsigned int)Hash[i]);
	}

	//	std::cout << counter << " " << CharArrayToHash <<  " " << mdString << "\n";
	FiveZeros = true;
	for (i=0; i < 5; i++){
	  FiveZeros = FiveZeros && (mdString[i] == '0');
	}
	//    while first 5 chars != 00000:
	//    calcMD5Hash(DoorID + IncreasingInteger)
	//      if first 5 chars != 00000:
	//         increment integer added to doorID
      }
      //      std::cout << DoorID + std::to_string(counter) << " " << mdString << "\n";
      LetterPosition = mdString[5] - '0';
      //      std::cout << LetterPosition << " " << mdString[6] << "\n";
      if ((LetterPosition > -1) && (LetterPosition < 8) && Password[LetterPosition]=='-'){
	Password[LetterPosition] = mdString[6];
	numberOfLettersSolved++;
      }
      if (numberOfLettersSolved == 8){
	DoneGettingPassword = true;
      }
    }
    std::cout << Password << "\r";
    std::cout.flush();
    std::cout << "\n";
  };
  EndTime = clock();

  
  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 0;
}
