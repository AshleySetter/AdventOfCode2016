#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265

int countCommas(char* inputString){
  int NoOfCommas = 0;
  int i = 0;
  
  while (inputString[i] != '\0'){
    i++;
    if (inputString[i] == ','){
      NoOfCommas++;
    }
  }
  return NoOfCommas;
}

void splitInstructions(char* Instructions, char* Delimiter, char* DirectionArray, int* DistanceArray){
  char* token;
  char DistanceString[4];
  int i=0;
  token = strtok(Instructions, Delimiter);
  while (token != '\0'){
    //    printf("%s\n", token);
    DirectionArray[i] = token[0];
    memcpy(&DistanceString, &token[1], 3);
    DistanceArray[i] = atoi(DistanceString);
    //    printf("%s\n", DistanceString);
    token = strtok(NULL, Delimiter);
    i++;
  }
  DirectionArray[i] = '\0';
}

float FindDistance(char *filename){
  char* Instructions;
  char* Delimeter = ", ";
  char* DirectionArray;
  int* DistanceArray;
  int NumberOfCommas;
  int NumberOfMovements;
  FILE* fp;
  int x = 0;
  int y = 0;
  int xvel = 0;
  int yvel = 0;
  float AngleFromNorth = 0;
  int distance;
  int* xArray;
  int* yArray;
  int TotalDistanceToTravel;
  int TotalDistanceLeftToTravel;
  int DistanceToTravelThisStep;
  int index;
  
  Instructions = (char *) malloc(1000*sizeof(char));
  fp = fopen(filename, "r");
  fgets(Instructions, 1000, fp);
  fclose(fp);
  //printf("%s \n", Instructions);
  NumberOfCommas = countCommas(Instructions);
  NumberOfMovements = NumberOfCommas + 1;
  DirectionArray = (char *) malloc(NumberOfMovements*(sizeof(char))+1); // extra byte to allow for zero terminator
  DistanceArray = (int *) malloc(NumberOfMovements*sizeof(int));
  splitInstructions(Instructions, Delimeter, DirectionArray, DistanceArray);
  free(Instructions);
  /*printf("%s\n", DirectionArray);
  for(int i=0; i<NumberOfMovements; i++){
    printf("%d ", DistanceArray[i]);
  }
  printf("\n");*/

  TotalDistanceToTravel = 0;
  for (int i=0; i<NumberOfMovements; i++){
    TotalDistanceToTravel += abs(DistanceArray[i]);
  }
  
  xArray = (int *) malloc(TotalDistanceToTravel*sizeof(int));
  yArray = (int *) malloc(TotalDistanceToTravel*sizeof(int));

  TotalDistanceLeftToTravel = TotalDistanceToTravel;
  
  for (int j=0; j<NumberOfMovements; j++){
    if (DirectionArray[j] == 'R') {
      AngleFromNorth += PI/2;
    }
    else if (DirectionArray[j] == 'L') {
      AngleFromNorth -= PI/2;
    }
    xvel = round(sin(AngleFromNorth));
    yvel = round(cos(AngleFromNorth));
    //printf("[%d, %d]\n", xvel, yvel);
    DistanceToTravelThisStep = DistanceArray[j];
    while(DistanceToTravelThisStep > 0){
      x += xvel;
      y += yvel;
      index = TotalDistanceToTravel-TotalDistanceLeftToTravel;
      for (int i=0 ; i<index; i++){
	if (xArray[i] == x && yArray[i] == y){
	  distance = abs(x) + abs(y);
	  
	  free(DirectionArray);
	  free(DistanceArray);
	  return distance;
	}
      }
      //printf("[%d, %d] %d\n", x , y, index);
      xArray[index] = x;
      yArray[index] = y;
      TotalDistanceLeftToTravel--;
      DistanceToTravelThisStep--;
    }
  }

  //printf("[%d, %d]\n", x, y);

  distance = abs(x) + abs(y);
  
  free(DirectionArray);
  free(DistanceArray);
  return distance;
}

int main(){
  int distance;
  char* filename = "input.txt";

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;
  int NumRuns = 10000;

  StartTime = clock();
  for (int i = 0 ; i < NumRuns ; i++){
    distance = FindDistance(filename);
  }
  EndTime = clock();

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%d\n", distance);

  printf("%f seconds for %d runs \n", cpu_time, NumRuns); 
  return 1;
}
