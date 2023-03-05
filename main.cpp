#include "include/window.h"

#include <cassert>

/** TODO
 * Make input handler
 * Make Grid shape using sfml
 * Make buttons
 * Make observant
 * Make Game class that holds all it together
 **/

int main() {
    Window app(720, 840, "Sudoku");

    while (app.isRunning()){
        app.handleEvent();
        app.display();
    }
    return 0;
}
