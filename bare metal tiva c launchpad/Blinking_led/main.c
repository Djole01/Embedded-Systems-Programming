int counter = 0;

int main(){
  
  // initializing gpio port F which is bit 5 (0x20U in hex), 
  //direction register and digital function register
  *((unsigned int *)0x400FE608U) = 0x20U;  
  *((unsigned int *)0x40025400U) = 0x0EU;  
  *((unsigned int *)0x4002551CU) = 0x0EU;  
  
  while(1) {
    // turn led on
    *((unsigned int *)0x400253FCU) = 0x02U; 
    
    // delay
    int counter = 0;
    while (counter < 1000000) {
      ++counter;
    }
    //turn led off
    *((unsigned int *)0x400253FCU) = 0x00U; 
    //delay
    counter = 0;
    while (counter < 1000000) {
      ++counter;
    }
  }
  return 0;
}
