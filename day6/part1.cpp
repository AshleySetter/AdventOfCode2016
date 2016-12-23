#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>

int GetNumberOfLines(std::string Filename){
  std::ifstream InputFile(Filename);
  std::string Line;
  int NumOfLines = 0;
  while (std::getline(InputFile, Line)){
    NumOfLines++;
  }
  return NumOfLines;
}

int GetNumberOfChars(std::string Filename){
  std::ifstream InputFile(Filename);
  std::string Line;
  std::getline(InputFile, Line);
  int NumOfChars=0;
  unsigned int i;
  for(i=0; i<Line.length(); i++){
    NumOfChars++;
  }
  return NumOfChars;
}

bool compare(const std::pair<int, int>&i, const std::pair<int, int>&j){
  return i.first > j.first;
}


char GetMostCommonLetters(char **Characters, int NumberOfLines, int CharNumber){
  // have to pass a reference to a vector to pass it to a function
  std::vector <std::pair<int, char>> AlphabetCount;
  int LetterPositon;
  unsigned int i;
  std::size_t Pos;
  std::string Alphabet = {"abcdefghijklmnopqrstuvwxyz"};
  AlphabetCount.resize(26);
  for (i=0; i<26; i++){
    AlphabetCount[i].second = Alphabet[i];
    AlphabetCount[i].first = 0;
  }
  for (i=0; i<NumberOfLines; i++){
    Pos = Alphabet.find_first_of(Characters[CharNumber][i]);
    LetterPositon = (int) Pos;
    AlphabetCount[LetterPositon].first++;
  }
  std::sort(AlphabetCount.begin(), AlphabetCount.end(), compare);

  return AlphabetCount[0].second;
}


int main(){
  int timingI;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int NumRuns = 100000;

  StartTime = clock();
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    std::string Filename = "input.txt";
    int NumberOfLines = GetNumberOfLines(Filename);
    int NumberOfChars = GetNumberOfChars(Filename);
    std::ifstream InputFile(Filename);
    int LineNo = 0;
    unsigned int i;
    std::string Line;
    char** CharacterArray;
    CharacterArray = new char*[NumberOfChars];
    for (i=0; i<NumberOfChars; i++){
      CharacterArray[i] = new char[NumberOfLines];
    }
    
    while (std::getline(InputFile, Line)){
      for(i=0; i<Line.length(); i++){
	CharacterArray[i][LineNo] = Line[i];
      }
      LineNo++;
    }
    /*    for(i=0; i<NumberOfLines; i++){
	  for(unsigned int j=0; j<NumberOfChars; j++){
	  std::cout << CharacterArray[j][i];
	  }
	  std::cout << "\n";
      }*/
    /*    for (i=0; i<NumberOfChars; i++){
	  std::cout << GetMostCommonLetters(CharacterArray, NumberOfLines, i);
    }
    std::cout << "\n";*/
  }
  EndTime = clock();

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
