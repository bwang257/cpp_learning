/*
Exploration of initialization of undefined static memory and stack variables
*/

#include <iostream>

int i;
int x;

// Global variables: reside in static memory and are zero-initialized by default. 
// Local variables are initialized on the stack and are default-initialized to gunk. 
int main(){
  int j;
  std::cout << i << " " << x << " " << j << std::endl;
}