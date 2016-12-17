#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

bool compare(const std::pair<int, int>&i, const std::pair<int, int>&j){
  if (i.first != j.first){
    return i.first > j.first;    
  }
  else{
    size_t Pos_i, Pos_j;
    int Positon_i, Positon_j;
    std::string Alphabet = {"abcdefghijklmnopqrstuvwxyz"};
    
    Pos_i = Alphabet.find_first_of(i.second);
    Positon_i = (int) Pos_i;
    Pos_j = Alphabet.find_first_of(j.second);
    Positon_j = (int) Pos_j;
    return Positon_i < Positon_j;
    }
}

void SplitLine(std::string Line, std::string & Characters, int & SectorID, std::string & CheckSum){ // need to pass a reference to string in order to change it outside the function - passes copy of string otherwise! - less memory efficient?
  std::string Block;
  std::istringstream LineStream(Line);
  
  Characters = "";
  SectorID = -1;
  
  while (std::getline(LineStream, Block, '-')){
    if (not std::isdigit(Block[0])){ // if not a number/digit
      Characters.append(Block); // add to char string
    }
    else {
      
      SectorID = std::stoi(Block.substr(0, 3));
      CheckSum = Block.substr(4, 5);
    }
  }
  /*  std::cout << Characters << "\n";
  std::cout << SectorID << "\n";
  std::cout << CheckSum << "\n";*/
}

void Get5MostCommonLetters(std::string Characters, char CommonLetters[5], std::string Alphabet, std::vector <std::pair<int, char>> & AlphabetCount){
  // have to pass a reference to a vector to pass it to a function
  int LetterPositon;
  unsigned int i;
  std::size_t Pos;
  for (i=0; i<26; i++){
    AlphabetCount[i].second = Alphabet[i];
    AlphabetCount[i].first = 0;
  }
  for (i=0; i<Characters.length(); i++){
    Pos = Alphabet.find_first_of(Characters[i]);
    LetterPositon = (int) Pos;
    AlphabetCount[LetterPositon].first++;
  }
  std::sort(AlphabetCount.begin(), AlphabetCount.end(), compare);

  for (i=0; i<5; i++){
    CommonLetters[i] = AlphabetCount[i].second;
  }
 }

int TransformNumber(int LetterPositon, int RotationAmount){
  int NewPos = LetterPositon + RotationAmount;
  while (NewPos > 25){
    NewPos -= 26;
  }
  return NewPos;
}

int main(){
  int timingI;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int Total;
  int NumRuns = 100;

  StartTime = clock();
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    std::string Filename = "input.txt";
    std::ifstream InputFileStream(Filename);
    std::string Line;
    char CommonLetters[5];
    std::string Alphabet = {"abcdefghijklmnopqrstuvwxyz"};
    std::string Characters;
    int SectorID;
    std::string CheckSum;
    //    int AlphabetCount[26];
    std::vector <std::pair<int, char>> AlphabetCount;
    int i;
    bool IsCodeCorrect;
    int LetterPositon, NewPos;
    size_t Pos;
    AlphabetCount.resize(26);

    Total = 0;
    for (i=0; i<26; i++){
      AlphabetCount[i].second = Alphabet[i];
      AlphabetCount[i].first = 0;
    }
    
    while (std::getline(InputFileStream, Line)){
      //std::cout << Line << "\n";
      SplitLine(Line, Characters, SectorID, CheckSum);
      Get5MostCommonLetters(Characters, CommonLetters, Alphabet, AlphabetCount);
      IsCodeCorrect = 1;
      for (i=0; i<5; i++){
	IsCodeCorrect = IsCodeCorrect & (CommonLetters[i] == CheckSum[i]);
      }
      //std::cout << IsCodeCorrect << "\n";
      if (IsCodeCorrect){
	//	std::cout << Characters << "\n"; // decrypt and search for northpoleobjects
	for (i=0; i<Characters.length(); i++){
	  Pos = Alphabet.find_first_of(Characters[i]);
	  LetterPositon = (int) Pos;
	  NewPos = TransformNumber(LetterPositon, SectorID);
	  Characters[i] = Alphabet[NewPos];
	}
	if (Characters == "northpoleobjectstorage"){
	  std::cout << SectorID << "\n";
	}
	//	std::cout << Characters << "\n";
      }
    }
  };
  EndTime = clock();

  std::cout << Total << "\n";

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
