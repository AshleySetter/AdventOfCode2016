#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>

int main(){
  std::string Filename = "input.txt";
  std::ifstream InputFileStream(Filename);
  std::string Line;
  std::string SideLength;
  int SideNo;
  int LengthArray[3];
  unsigned int NumOfTriangles = 0;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;
  int NumRuns = 100000000;

  StartTime = clock();
  for (int i = 0 ; i < NumRuns ; i++){
    while (std::getline(InputFileStream, Line)){
      std::istringstream LineStream(Line);
      SideNo = 0;
      while (std::getline(LineStream, SideLength, ' ')){
	if (SideLength.empty() != 1){
	  //	std::cout << SideLength << "\n";
	  LengthArray[SideNo] = std::stoi(SideLength);
	  SideNo++;
	}
      }
      std::sort(LengthArray, LengthArray + 3); // sorts the triangle sides so the two smaller sides are first in the list
      if (LengthArray[0] + LengthArray[1] > LengthArray[2]){ // triangles require sum of any 2 sides larger than the other
	NumOfTriangles++;
      }
    }
  }
  EndTime = clock();
  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  std::cout << NumOfTriangles << "\n";

  printf("%e seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);

  return 1;
}
