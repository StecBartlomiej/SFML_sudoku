#ifndef SFML_SUDOKU_WINDOW_H
#define SFML_SUDOKU_WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "sudoku.h"
#include <iostream>

#include "FontID.hpp"
#include "ResourceHolder.hpp"

/// Should only be display !
class Window {
public:
    explicit Window(uint32_t width = 720, uint32_t height = 840, const std::string &title = "Sudoku");

    /// SRP rule violated!
    void handleEvent();

    void display();

    [[nodiscard]] bool isRunning() const { return window_.isOpen();}

private:

    void resize(uint32_t width, uint32_t height);

    /// Graphics method
    void printSudoku();

    void printGrid();

    void printBoard();

    void printButtons();

    /// User input method
    void mouseLeftClick(int x, int y);

    void mouseRightCLick(int x, int y);

private:
    sf::RenderWindow window_;
    sf::FloatRect gridRect_; // area where the sudoku is
//    sf::FloatRect solveButton_;
//    sf::FloatRect resetButton_;
    Sudoku sudoku_;

    ResourceHolder<sf::Font, FontID> fontHolder_{};

    static inline const auto backgroundColor = sf::Color(220, 220, 220);
};

sf::Text renderNumber(const sf::Font& font, int number, uint32_t size = 64);


#endif //SFML_SUDOKU_WINDOW_H
