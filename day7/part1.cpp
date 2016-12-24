#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <regex>
#include <fstream>

bool CheckStringForPattern(std::string Input){
  bool PatternPresent = false;
  unsigned int i;
  for (i=0; i<Input.length()-3; i++){
    if ((Input[i] == Input[i+3]) && (Input[i+1] == Input[i+2]) && (Input[i] != Input[i+1])){
      PatternPresent = true;
    }
  }
  
  return PatternPresent;
}

bool CheckIf_TLS_Supported(std::string IPAddress){
  bool PatternPresent;
  std::string IPAddressStripped;
  std::regex pattern ("\\[[a-z]+\]"); // pattern matches a [ char followed by any number of lower case letters in range a-z followed by a ] char (the \\[ and \] are needed because [ and ] are special characters in regex and must be escaped using the \ escape character
    
  //std::cout << IPAddress << "\n";
  //std::cout << std::regex_replace (IPAddress,pattern,"") << "\n"; 

  std::sregex_iterator iter(IPAddress.begin(), IPAddress.end(), pattern);
  std::sregex_iterator end;

  while(iter != end){
    for(unsigned i = 0; i < iter->size(); ++i){
      //      std::cout << "the " << i + 1 << "th match" << ": " << (*iter)[i] << std::endl;
      if (CheckStringForPattern((*iter)[i])){
	//	std::cout << "false" << "\n";
	return false;
      }
    }
    ++iter;
  }
  
  IPAddressStripped = std::regex_replace (IPAddress, pattern, "-");
  std::stringstream IPAddressStrippedStream(IPAddressStripped);
  std::string section;
  PatternPresent = false;
  while (std::getline(IPAddressStrippedStream, section, '-')){
    PatternPresent = PatternPresent || CheckStringForPattern(section);
  }
  return PatternPresent;
}

int main(){
  int timingI;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int NumRuns = 10;
  
  StartTime = clock();
  int NumSupportedIPAddresses = 0;
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    bool PatternPresent;
    std::string IPAddress;
    std::string Filename = "input.txt";
    std::ifstream InputFile (Filename);
    NumSupportedIPAddresses = 0;
    while (std::getline(InputFile, IPAddress)){
      PatternPresent = CheckIf_TLS_Supported(IPAddress);
      if (PatternPresent){
	//	std::cout << "bang" << "\n";
	//	std::cout << IPAddress << "\n";
	NumSupportedIPAddresses++;
      }
      //      std::cout << "\n";
    }
    //    std::cout << NumSupportedIPAddresses << "\n";
  };
  EndTime = clock();

  std::cout << NumSupportedIPAddresses << "\n";

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
