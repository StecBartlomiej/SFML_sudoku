#include "window.h"

Window::Window(uint32_t width, uint32_t height, const std::string &title): sudoku{} {
    //sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;

    //window_.create(sf::VideoMode(width, height), title, sf::Style::Default &(~sf::Style::Resize), settings);
    window_.create(sf::VideoMode(width, height), title);
    window_.setFramerateLimit(30);

    if (!font.loadFromFile("../lib/font/calibri-regular.ttf")){
        sf::err();
    }
}

void Window::handleEvent() {

    sf::Event event{};
    if(window_.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        /// will be delegated to new function (?)
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left){
                mouseLeftClick(event.mouseButton.x, event.mouseButton.y);
            }
            else if(event.mouseButton.button == sf::Mouse::Right){
                mouseRightCLick(event.mouseButton.x, event.mouseButton.y);
            }
        }

    }
}

void Window::display() {
    window_.clear(backgroundColor);

    printBoard();
    printSudoku();
    printButton();

    window_.display();
}

/// TODO - fix left border
void Window::printBoard() {
    constexpr float size = 80.f;

    // bold lines between groups
    sf::RectangleShape boldYLine{sf::Vector2<float>{4.f, 720.f}};
    sf::RectangleShape boldXLine{sf::Vector2<float>{720.f, 4.f}};
    boldYLine.setFillColor(sf::Color::Black);
    boldXLine.setFillColor(sf::Color::Black);

    // one sudoku square
    sf::RectangleShape rect{sf::Vector2<float>{size, size}};
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(sf::Color::Black);
    rect.setFillColor(backgroundColor);

    for (int i = 0; i < 9; ++i){
        rect.setPosition(0, size * static_cast<float>(i));
        for (int j = 0; j < 9; ++j){
            rect.setPosition(size * static_cast<float>(j), rect.getPosition().y);
            window_.draw(rect);
        }
    }

    for (int i = 1; i <= 3; ++i){
        boldYLine.setPosition(size * 3 * (i % 3), 0);
        boldXLine.setPosition(0.f, size * 3 * i);
        window_.draw(boldYLine);
        window_.draw((boldXLine));
    }
}

void Window::mouseLeftClick(int x, int y) {
    if (x <= 720 && y <= 720){
        x /= 80;
        y /= 80;
        int num = (sudoku(y, x)) % 9 + 1;
        printf("mouseLeftClick, y: %d, x: %d, nm:%d\n", y, x, num);
        sudoku.setSudoku(y, x, num);
    }
    else if (y > 740 && y < 820){
        /// Solve button clicked!
        if (x > 30 && x < 300){
            printf("%d\n", sudoku.solve());
        }
        else if(x > 390 && x < 690){
            sudoku.reset();
            printf("Sudoku reset!\n");
        }
    }

}

void Window::mouseRightCLick(int x, int y) {
    x /= 80;
    y /= 80;
    sudoku.setSudoku(y, x, 0);
}

sf::Text Window::renderNumber(int number, int charSize) {
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(number));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(charSize);
    return text;
}

void Window::printSudoku() {
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (sudoku(i, j) == 0) { continue;}
            sf::Text text = renderNumber(sudoku(i, j), 60);
            text.setPosition(j * 80.f + 20, i * 80.f);
            window_.draw(text);
        }
    }
}

void Window::printButton() {
    sf::RectangleShape rect(sf::Vector2<float>{300.f, 80.f});
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(sf::Color::Black);

    sf::Text text;
    text.setFillColor(sf::Color::Black);
    text.setFont(font);

    /// Solve button
    rect.setPosition(30.f, 740.f);
    text.setString("Solve");
    text.setPosition(30 + 100, 760);
    window_.draw(text);
    window_.draw(rect);

    /// Reset button
    rect.setPosition(30.f + 360.f, 740.f);
    text.setPosition(30 + 360.f + 100.f, 760.f);
    text.setString("Reset");
    window_.draw(text);
    window_.draw(rect);


}

