#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

unsigned int CountFullLines(std::string Filename){
  std::ifstream InputFileStream(Filename);
  std::string line;
  unsigned int i = 0;
  
  while (std::getline(InputFileStream, line)){
    if (line.empty()){
      break;
    }
    i++;
  }
  return i;
}

void CalculateCode(std::string Filename, std::string* PassCode){
  std::string NumPad[5][5] = {
    {"-", "-", "1", "-", "-"},
    {"-", "2", "3", "4", "-"},
    {"5", "6", "7", "8", "9"},
    {"-", "A", "B", "C", "-"},
    {"-", "-", "D", "-", "-"}
  };
  int Loc[2] = {2, 0};
  std::ifstream InputFileStream(Filename);
  std::string line;
  unsigned int i, CodeNo = 0;
  
  while (std::getline(InputFileStream, line)){
    if (line.empty()){
      break;
    }
    for(i = 0; i<line.length(); i++){
      //      std::cout << line[i] << "\n";
      switch(line[i]){
      case 'L':
	if ((Loc[1] != 0) && (NumPad[Loc[0]][Loc[1]-1] != "-")){
	  Loc[1]--;
	};
	break;
      case 'R':
	if ((Loc[1] != 4) && (NumPad[Loc[0]][Loc[1]+1] != "-")){
	  Loc[1]++;
	};
	break;
      case 'D':
	if ((Loc[0] != 4) && (NumPad[Loc[0]+1][Loc[1]] != "-")){
	  Loc[0]++;
	};
	break;
      case 'U':
	if ((Loc[0] != 0) && (NumPad[Loc[0]-1][Loc[1]] != "-")){
	  Loc[0]--;
	};
	break;
      default :
	break;
      }
      //std::cout << Loc[0] << " " << Loc[1] << " " << NumPad[Loc[0]][Loc[1]] << "\n";
    }
    //std::cout << "EOL " << Loc[0] << " " << Loc[1] << " " << NumPad[Loc[0]][Loc[1]] << "\n";
    PassCode[CodeNo] = NumPad[Loc[0]][Loc[1]];
    CodeNo++;
  }
  
  InputFileStream.close();
}

void GetPassCode(std::string Filename){

}

int main(){
  std::string Filename = "input.txt";
  std::string* PassCode;
  int i;
  int PassCodeLength;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int NumRuns = 10000;

  StartTime = clock();
  for (int i = 0 ; i < NumRuns ; i++){
  PassCodeLength = CountFullLines(Filename);  
  PassCode = new std::string [PassCodeLength];
  CalculateCode(Filename, PassCode);
  };
  EndTime = clock();

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  for(i=0; i<PassCodeLength; i++){
    std::cout << PassCode[i];
  }
  std::cout << "\n";
  //delete PassCode;

  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
