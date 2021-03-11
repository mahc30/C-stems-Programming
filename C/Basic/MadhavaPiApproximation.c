#include <stdio.h>
#include <math.h>

// I used Madhava's approximation of PI
// to get the first N digits of PI
// The program can get up to
// the first 14 digits with only 27 iterations
// I tried with 160000 iterations but couldn't get
// another digit so... 27 it is
// For more info on Madhava's work: 
// https://en.wikipedia.org/wiki/Madhava_of_Sangamagrama#The_value_of_%CF%80_(pi)

int main(void) {

  const char ACTUALPI[20] = "3.1415926535897932\n";
  double mypi = 0;
  
  for(int i = 0; i < 27; i++){
    mypi += (pow(-3, -i) / (2*i + 1));
  }
  
  mypi *= sqrt(12);
  
  printf("My PI:\t\t%.16f\nActual PI:\t%s\n", mypi, ACTUALPI);
}
