#include <iostream>
#include "ConsoleUI.h" 
#include "Tests.h"

int main() {
    runTests();
    ConsoleUI<int> ui;
    ui.run();
    return 0;
}