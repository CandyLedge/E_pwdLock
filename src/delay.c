#include "delay.h"
void delay(uint tick){
    uint i,j;
    for(i=tick;i>0;i--)
      for(j=247;j>0;j--);
}