#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  DirectionArray[i-1] = '\0';
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
  float AngleFromNorth;
  
  Instructions = (char *) malloc(1000);
  fp = fopen(filename, "r");
  fgets(Instructions, 1000, fp);
  fclose(fp);
  printf("%s \n", Instructions);
  NumberOfCommas = countCommas(Instructions);
  NumberOfMovements = NumberOfCommas + 1;
  DirectionArray = (char *) malloc(NumberOfMovements*sizeof(char));
  DistanceArray = (int *) malloc(NumberOfMovements*sizeof(int));
  splitInstructions(Instructions, Delimeter, DirectionArray, DistanceArray);

  printf("%s\n", DirectionArray);
  for(int i=0; i<NumberOfMovements; i++){
    printf("%d ", DistanceArray[i]);
  }
  printf("\n");

  
  
  free(Instructions);
  free(DirectionArray);
  free(DistanceArray);
  return 1.0;
}

int main(){
  char* filename = "input.txt";
  FindDistance(filename);
  return 1;
}
