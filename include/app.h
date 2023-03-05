#ifndef SFML_SUDOKU_APP_H
#define SFML_SUDOKU_APP_H

#include "sudoku.h"
#include "window.h"

class App{
public:
    App();

    void run();

private:
    void handleEvents();

private:
    Window window_;
    Sudoku sudoku_;
};

#endif //SFML_SUDOKU_APP_H
