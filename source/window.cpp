#include "window.h"
#include "FontID.hpp"

Window::Window(uint32_t width, uint32_t height, const std::string &title) : gridRect_{}, sudoku_{}, fontHolder_{}
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window_.create(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    window_.setVerticalSyncEnabled(true);

    fontHolder_.load(FontID::calibri, "../lib/font/calibri-regular.ttf");
}

void Window::handleEvent()
{
    sf::Event event{};
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            resize(event.size.width, event.size.height);
        }

            /// will be delegated to new function (?)
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mouseLeftClick(event.mouseButton.x, event.mouseButton.y);
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                mouseRightCLick(event.mouseButton.x, event.mouseButton.y);
            }
        }

    }
}

void Window::display()
{
    window_.clear(backgroundColor);

    printBoard();
    printSudoku();
    printGrid();
    printButton();

    window_.display();
}

void Window::printBoard()
{
    float rectSize = window_.getSize().y * 0.8f / 9.f;

    // one sudoku_ square
    sf::RectangleShape rect{sf::Vector2<float>{rectSize, rectSize}};
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(sf::Color::Black);
    rect.setFillColor(backgroundColor);

    sf::Vector2f center{window_.getSize().x / 2.f - rectSize * 4.5f, 0};

    gridRect_ = {center.x, center.y, rectSize * 9, rectSize * 9};

    for (int i = 0; i < 9; ++i)
    {
        rect.setPosition(center.x, rectSize * static_cast<float>(i) + center.y);
        for (int j = 0; j < 9; ++j)
        {
            rect.setPosition(center.x + rectSize * static_cast<float>(j), rect.getPosition().y);
            window_.draw(rect);
        }
    }
}

void Window::mouseLeftClick(int x, int y)
{
    if (x >= gridRect_.left && x <= gridRect_.left + gridRect_.width &&
        y >= gridRect_.top && y <= gridRect_.top + gridRect_.height)
    {
        x = (x - gridRect_.left) / (gridRect_.width / 9);
        y = (y - gridRect_.top) / (gridRect_.height / 9);

        int num = (sudoku_(y, x)) % 9 + 1;
        //printf("mouseLeftClick, y: %d, x: %d, nm:%d\n", y, x, num);
        sudoku_.setSudoku(y, x, num);
    }
    /// TODO - buttons!
}

void Window::mouseRightCLick(int x, int y)
{
    if (x >= gridRect_.left && x <= gridRect_.left + gridRect_.width &&
        y >= gridRect_.top && y <= gridRect_.top + gridRect_.height)
    {
        x = (x - gridRect_.left) / (gridRect_.width / 9);
        y = (y - gridRect_.top) / (gridRect_.height / 9);

        sudoku_.setSudoku(y, x, 0);
    }
}

void Window::printSudoku()
{
    uint32_t charSize = (gridRect_.width / 9) * 0.8;
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (sudoku_(i, j) == 0) { continue; }

            sf::Text text = renderNumber(fontHolder_.get(FontID::calibri),sudoku_(i, j), charSize);

            text.setPosition(gridRect_.left + j * (gridRect_.width / 9) + charSize / 3.0f,
                             gridRect_.top + i * (gridRect_.height / 9));

            window_.draw(text);
        }
    }
}

/// TODO
void Window::printButton()
{

}

void Window::resize(uint32_t width, uint32_t height)
{
    sf::View area(sf::FloatRect(0, 0, 0, 0));

    if (width >= height * 0.8)
    {
        area.reset(sf::FloatRect(0, 0, width, height));
    }
    else
    {
        window_.setSize(sf::Vector2u(height * 0.8, height));
        area.reset(sf::FloatRect(0, 0, window_.getSize().x, window_.getSize().y));
    }
    window_.setView(area);
}

void Window::printGrid()
{
    constexpr float outerThickness = 4.0f;
    constexpr float insideThickness = 1.6f;

    float x = gridRect_.left;
    float y = gridRect_.top;
    float width = gridRect_.width;
    float height = gridRect_.height;

    sf::RectangleShape rect(sf::Vector2f(width, height));

    /// Outer grid
    rect.setPosition(x, y);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(outerThickness);
    rect.setFillColor(sf::Color::Transparent);
    window_.draw(rect);

    /// Inside grid
    rect.setSize(sf::Vector2f(width, 0.0f));
    rect.setOutlineThickness(insideThickness);

    for (std::size_t i = 1; i <= 2; ++i)
    {
        rect.setPosition(x, y + ((height / 9) * 3 * i));
        window_.draw(rect);
    }

    rect.setSize(sf::Vector2f(0.0f, height));
    for (std::size_t i = 1; i <= 2; ++i)
    {
        rect.setPosition(x + ((width / 9) * 3 * i), y);
        window_.draw(rect);
    }

}

sf::Text renderNumber(const sf::Font& font,int number, uint32_t size)
{
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(number));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(size);
    return text;
}

