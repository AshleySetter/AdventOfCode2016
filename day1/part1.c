#include <stdio.h>
#include <stdlib.h>

float FindDistance(char *filename){
  char* instructions;
  FILE* fp;
  int x = 0;
  int y = 0;

  instructions = (char *) malloc(1000);
  fp = fopen(filename, "r");
  fgets(instructions, 1000, fp);
  fclose(fp);
  printf("%s \n", instructions);
  
  free(instructions);
  return 1;
}

int main(){
  char* filename = "input.txt";
  FindDistance(filename);
  return 1;
}
