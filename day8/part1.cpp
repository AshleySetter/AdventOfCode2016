#include <iostream>
#include <time.h>
#include <regex>
#include <fstream>

#define SCREENWIDTH 50
#define SCREENHEIGHT 6

int SumTotalPixels(bool Screen[SCREENWIDTH][SCREENHEIGHT]){
  int Sum=0;
  for (int j=0; j<SCREENHEIGHT; j++){
    for (int i=0; i<SCREENWIDTH; i++){
      Sum+=Screen[i][j];
    }
  }
  return Sum;
}

void printScreen(bool Screen[SCREENWIDTH][SCREENHEIGHT]){
  for (int j=0; j<SCREENHEIGHT; j++){
    for (int i=0; i<SCREENWIDTH; i++){
      std::cout << ((Screen[i][j]) ? '@' : ' ');
    }
    std::cout << "\n";
  }
}

void RotateRow(bool Screen[SCREENWIDTH][SCREENHEIGHT], int RowNo, int Movement){
  bool RowCopy[SCREENWIDTH];
  for (int i=0; i<SCREENWIDTH; i++){
    RowCopy[i] = Screen[i][RowNo];
  }
  for (int i=0; i < SCREENWIDTH-Movement; i++){
    //    std::cout << i+Movement << "\n";
    Screen[i+Movement][RowNo] = RowCopy[i];
  }
  for (int i=0; i < Movement; i++){
    //    std::cout << Movement-1-i << "\n";
    Screen[Movement-1-i][RowNo] = RowCopy[SCREENWIDTH-1-i];
  }
}

void RotateColumn(bool Screen[SCREENWIDTH][SCREENHEIGHT], int ColumnNo, int Movement){
  bool RowCopy[SCREENHEIGHT];
  for (int i=0; i<SCREENHEIGHT; i++){
    RowCopy[i] = Screen[ColumnNo][i];
  }
  for (int i=0; i < SCREENHEIGHT-Movement; i++){
    //    std::cout << i+Movement << "\n";
    Screen[ColumnNo][i+Movement] = RowCopy[i];
  }
  for (int i=0; i < Movement; i++){
    //    std::cout << Movement-1-i << "\n";
    Screen[ColumnNo][Movement-1-i] = RowCopy[SCREENHEIGHT-1-i];
  }
}


int main(){
  int timingI;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int NumRuns = 100;

  StartTime = clock();
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    bool Screen[SCREENWIDTH][SCREENHEIGHT];
    //    std::string Line = "rotate column x=1 by 1";
    std::regex RectExpression("rect (\\d*)x(\\d*)");
    std::regex RotateExpression("rotate (\\w+) \\w=(\\d*) by (\\d*)");
    std::smatch match;
    std::string Line;
    std::string Filename = "input.txt";
    
    for (int j=0; j<SCREENHEIGHT; j++){
      for (int i=0; i<SCREENWIDTH; i++){
	Screen[i][j] = false;
      }
    }

    std::ifstream InputFile(Filename);
    
    while (std::getline(InputFile, Line)){      
      const std::string ConstLine = Line;
      if (std::regex_search(ConstLine.begin(), ConstLine.end(), match, RectExpression)){
	//	std::cout << "match: " << match[1] << " " << match[2] << '\n';
	for(int j=0; j < std::stoi(match[2]); j++){
	  for(int i=0; i < std::stoi(match[1]); i++){
	    //std::cout << j << " " << i << "\n";
	    Screen[i][j] = true;
	  }
	}
      }

      if (std::regex_search(ConstLine.begin(), ConstLine.end(), match, RotateExpression)){
	//	std::cout << "match: " << match[1] << " " << match[2] << " " <<  match[3] << '\n';
	if (match[1] == "row"){
	  RotateRow(Screen, std::stoi(match[2]), std::stoi(match[3]));
	}
	else if (match[1] == "column"){
	  RotateColumn(Screen, std::stoi(match[2]), std::stoi(match[3]));
	}
      }      
      //printScreen(Screen);
    }
    printScreen(Screen);
    //std::cout << SumTotalPixels(Screen) << "\n";
  };
  EndTime = clock();
  
  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
