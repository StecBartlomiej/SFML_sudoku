#ifndef SFML_SUDOKU_WINDOW_H
#define SFML_SUDOKU_WINDOW_H

#include "SFML/Graphics.hpp"
#include <string>
#include "sudoku.h"
#include <iostream>

/// Should only be display !
class Window {
public:
    explicit Window(uint32_t width = 720, uint32_t height = 840, const std::string &title = "Sudoku");

    void handleEvent();

    void display();

    [[nodiscard]] bool isRunning() const { return window_.isOpen();}
private:
    void printSudoku();

    void printBoard();

    void printButton();

    static sf::Text renderNumber(int number, int charSize = 60);

    /// User input method
    void mouseLeftClick(int x, int y);

    void mouseRightCLick(int x, int y);
private:
    sf::RenderWindow window_;
    Sudoku sudoku;
    static inline sf::Font font{};
    static inline auto backgroundColor = sf::Color(220, 220, 220);
};


#endif //SFML_SUDOKU_WINDOW_H
