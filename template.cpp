#include <iostream>
#include <time.h>

int main(){
  int timingI;

  clock_t StartTime;
  clock_t EndTime;
  double cpu_time;

  int NumRuns = 1;

  StartTime = clock();
  for (timingI = 0 ; timingI < NumRuns ; timingI++){
    
  };
  EndTime = clock();

  cpu_time = ((double) (EndTime - StartTime)) / CLOCKS_PER_SEC;
  
  printf("%f seconds for 1 run averaged over %d runs \n", cpu_time/NumRuns, NumRuns);
  
  return 1;
}
