#include <iostream>
#include <time.h>
#include <regex>
#include <fstream>
//#include <unistd.h>

void Decompress(std::string &input){
  std::regex Expression("\\((\\d*)x(\\d*)(\\))");
  std::smatch match;
  std::string::const_iterator begin = input.begin();
  std::string::const_iterator end = input.end();
  int DistanceThroughString = 0;

  int NumOfCharsToCopy;
  int NumOfRepeats;
  int matchPosition;
  int beginMatchPosition;
  int PatternLength;

  while(std::regex_search(begin, end, match, Expression)){
    matchPosition = match.position(3)+DistanceThroughString;
    beginMatchPosition = match.position(0)+DistanceThroughString;
    PatternLength = match[0].length(); 
    NumOfCharsToCopy = stoi(match[1]);
    std::string substring = input.substr(matchPosition+1, NumOfCharsToCopy);
    NumOfRepeats = stoi(match[2]);
    for (int i=0; i<NumOfRepeats-1; i++){
      input.insert(matchPosition+1, substring);
    }
    input.erase(beginMatchPosition, PatternLength);
    end = input.end();
    begin = input.begin();
    std::advance(begin, matchPosition + 1 + NumOfRepeats*NumOfCharsToCopy - PatternLength);
    DistanceThroughString += match.position(3) + 1 + NumOfRepeats*NumOfCharsToCopy - PatternLength;
  }
}

int main(){
  int timingI;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int NumRuns = 5000;

  StartTime = clock();
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    std::string CompressedString;
    std::ifstream InputFile("input.txt");
    std::getline(InputFile, CompressedString);
    Decompress(CompressedString);
    //std::cout << CompressedString.length() << "\n";
  };
  EndTime = clock();

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
