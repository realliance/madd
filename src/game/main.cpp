#include "main.h"

int main() {
    Game* gameContext = new Game();
    gameContext->Run();
    delete gameContext;
  return 0;
}