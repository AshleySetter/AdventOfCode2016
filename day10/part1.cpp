#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <regex>


class Bot{
public:
  Bot(int BotNumber); // prototype of constructor
  const int BotNo;
  std::vector<int> Chips;
  void GiveChip(int ChipValue); // prototype of GiveChip member function
  int TakeLowerValueChip();
  int TakeHigherValueChip();
};

Bot::Bot(int BotNumber)
  : BotNo(BotNumber) // initialisation list initialises BotNo to BotNumber when contructor is called
{
  //
}

void Bot::GiveChip(int ChipValue){
  Chips.push_back(ChipValue);
}

int Bot::TakeLowerValueChip(){
  auto MinElement = std::min_element(Chips.begin(), Chips.end());
  int LowerChipValue = *MinElement;
  Chips.erase(MinElement);
  return LowerChipValue;
}

int Bot::TakeHigherValueChip(){
  auto MaxElement = std::max_element(Chips.begin(), Chips.end());
  int HigherChipValue = *MaxElement;
  Chips.erase(MaxElement);
  return HigherChipValue;
}

    int main(){
    int timingI;

    clock_t StartTime;
    clock_t EndTime;
    double cpu_time;

    int NumRuns = 1;

    StartTime = clock();
    for (timingI = 0 ; timingI < NumRuns ; timingI++){
      std::vector<Bot> BotVector;
      std::string Filename = "testinput.txt";
      std::regex GiveExpression("value (\\d*) goes to bot (\\d*)");
      std::smatch match;
      std::ifstream InputFile(Filename);
      std::string Line;

      for(int i=0; i<3; i++){
	Bot TempBot(i);
	BotVector.push_back(TempBot);
	std::cout << BotVector[i].BotNo << "\n";
      }
    
      while (std::getline(InputFile, Line)){
	const std::string ConstLine = Line;
	if (std::regex_search(ConstLine.begin(), ConstLine.end(), match, GiveExpression)){
	  int BotNo = std::stoi(match[2]);
	  int ChipValue = std::stoi(match[1]);
	  std::cout << "match: " << ChipValue << " goes to Bot " << BotNo << '\n';
	  BotVector[BotNo].GiveChip(ChipValue);
	}      
      }
      int ChipValue;
      ChipValue = BotVector[2].TakeHigherValueChip();
      std::cout << "Chip Taken: " << ChipValue << "\n";
      //    std::cout << BotVector[0].BotNo << "\n";
      //    BotVector[0].Chips.push_back(5);
      for (auto BotIt : BotVector){
	std::cout << BotIt.BotNo << ": ";
	for (auto i : BotIt.Chips){
	  std::cout << i << " , ";
	}
	std::cout << "\n";
      }
    };
    EndTime = clock();

    cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
    printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
    return 1;
  }
