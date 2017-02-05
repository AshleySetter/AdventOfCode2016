#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>

void printMap(std::vector< std::vector<bool> > map){
  int NoRows = map.size();
  int NoCols = map[0].size();
  for(int i=0; i<NoRows; i++){
    for(int j=0; j<NoCols; j++){
      std::cout << map[i][j];
    }
    printf("\n");
  }
  printf("\n");
}

int SumMap(std::vector< std::vector<bool> > map){
  int Sum = 0;
  int NoRows = map.size();
  int NoCols = map[0].size();
  for(int i=0; i<NoRows; i++){
    for(int j=0; j<NoCols; j++){
      Sum += map[i][j];
    }
  }
  return Sum;
}

int main(){
  int timingI;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int NumRuns = 3;

  StartTime = clock();
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    int NumRows = 400000;
    int NumCols = 0;
    int Sum, NumOfSafeTiles;
    std::string Filename = "input.txt";
    std::string Line;
    std::ifstream InputFile(Filename);
    std::getline(InputFile, Line);
    std::vector< std::vector<bool> > TileMap; // initialise empty 2D (0x0) vector
    NumCols = Line.length();
    TileMap.resize(NumRows+2, std::vector<bool>(NumCols+2, false));
    // resize 2D vector to be (NumRows+2 x NumCols+2)
    // everything starts of false - i.e. assumed to be safe
    // true = trapped, false = safe
    // + 2 is to allow for padding of the arrays with non-trapped tiles
    for (int i=0; i<NumCols+1; i++){
      TileMap[0][i] = false;
      TileMap[NumRows+1][i] = false;
    };
    for (int j=0; j<NumRows+1; j++){
      TileMap[j][0] = false;
      TileMap[j][NumCols+1] = false;
    };
    // true is safe, false is trapped
    for (int i=1; i<NumCols+1; i++){
      if (Line[i-1] == '^') {
	TileMap[1][i] = true;
      }
    }
    for(int Row=2; Row<NumRows+1; Row++){
      for(int Col=1; Col<NumCols+1; Col++){
	if ((TileMap[Row-1][Col-1] == true) and (TileMap[Row-1][Col] == true) and (TileMap[Row-1][Col+1] == false)){
	  TileMap[Row][Col] = true;
	}
	else if ((TileMap[Row-1][Col-1] == false) and (TileMap[Row-1][Col] == true) and (TileMap[Row-1][Col+1] == true)){
	  TileMap[Row][Col] = true;
	}
	else if ((TileMap[Row-1][Col-1] == true) and (TileMap[Row-1][Col] == false) and (TileMap[Row-1][Col+1] == false)){
	  TileMap[Row][Col] = true;
	}
	else if ((TileMap[Row-1][Col-1] == false) and (TileMap[Row-1][Col] == false) and (TileMap[Row-1][Col+1] == true)){
	  TileMap[Row][Col] = true;
	}
      }
    }
    //printMap(TileMap);
    Sum = SumMap(TileMap);
    NumOfSafeTiles = NumRows*NumCols - Sum;
    //std::cout << NumOfSafeTiles << "\n";
  };
  EndTime = clock();

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
