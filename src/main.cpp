#include "main.h"

int main(){
    const char* title = "test";
    Madd* gameContext = new Madd(800,600,title);
    gameContext->Start(); 
    return 0;
}