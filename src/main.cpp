#include "main.h"
#include "helpmerender.h"
#include <iostream>


int main(){
    const char* title = "test";
    //Madd* gameContext = new Madd(800,600,title);
    //gameContext->Start(); 
    triangle b(xyz(1,1,1),xyz(2,2,2),xyz(3,3,3));
    std::cout<<b<<std::endl;
    float b_array[] = TO_C_ARRAY(b);
    return 0;
}