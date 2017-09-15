#include <stdio.h>
#include "miscell.h"


int fact(int v){
     int t = 1;
    if(v == 0)
         return 1;
    t = v * fact(v-1);
        return t;     
}    

int fibonacci(int v)
{
    if( v == 0)
        return 0;
    if( v == 1)
        return 1;
    return fibonacci(v - 1) + fibonacci(v - 2);       
}
