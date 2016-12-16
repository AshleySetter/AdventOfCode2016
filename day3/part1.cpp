#include <iostream>
#include <fstream>
#include <sstream>


int main(){
  std::string Filename = "inputlite.txt";
  std::ifstream InputFileStream(Filename);
  std::string Line;
  std::string SideLength;
  int SideNo, i;
  int LengthArray[3];
  
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
    for (i=0; i<3; i++){ 
      std::cout << LengthArray[i] << " ";
    }
    std::cout << "\n";
  }
  return 1;
}
