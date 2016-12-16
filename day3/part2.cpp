#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>

int main(){
  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;
  int NumRuns = 1000;

  unsigned int NumOfTriangles = 0;
  StartTime = clock();
  for (int i = 0 ; i < NumRuns ; i++){

    std::string Filename = "input.txt";
    std::string Line;
    std::string SideLength;
    int ColNo;
    int LengthArray[3];
    int ColumnCurrentlyOn = 0;
    int SideNo = 0;

    for(ColumnCurrentlyOn=0; ColumnCurrentlyOn<3; ColumnCurrentlyOn++){
      std::ifstream InputFileStream(Filename);
      while (std::getline(InputFileStream, Line)){
	std::istringstream LineStream(Line);
	ColNo = 0;
	while (std::getline(LineStream, SideLength, ' ')){
	  if (SideLength.empty() != 1){
	    //	std::cout << SideLength << "\n";
	    if (ColNo == ColumnCurrentlyOn){
	      LengthArray[SideNo] = std::stoi(SideLength);
	      SideNo++;
	    }	  
	    ColNo++;
	  }
	}
	if (SideNo == 3){
	  /*	  for(int i=0; i<3; i++){
	    printf("%d ", LengthArray[i]);
	  }
	  printf("\n");*/

	  std::sort(LengthArray, LengthArray + 3); // sorts the triangle sides so the two smaller sides are first in the list
	  if (LengthArray[0] + LengthArray[1] > LengthArray[2]){ // triangles require sum of any 2 sides larger than the other
	    NumOfTriangles++;
	  }
	  SideNo = 0;
	}
      }
    }
  }
  EndTime = clock();
  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  std::cout << NumOfTriangles << "\n";

  printf("%e seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);

  return 1;
}
