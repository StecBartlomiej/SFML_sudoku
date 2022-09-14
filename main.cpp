#include "window.h"

#include <cassert>

int main() {
    Window app(720, 840, "Sudoku");

    while (app.isRunning()){
        app.handleEvent();
        app.display();
    }
    return 0;
}
