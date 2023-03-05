#ifndef SDL2_TEST_SUDOKU_H
#define SDL2_TEST_SUDOKU_H

#include <vector>
#include <bitset>

class Sudoku{
public:
    Sudoku();
    [[maybe_unused]] explicit Sudoku(const int (&tab)[9][9]);

    bool solve();

    void setSudoku(const int (&tab)[9][9]);

    void setSudoku(std::size_t i, std::size_t j, int number);

    /// @return value under the tab[i][j]
    [[nodiscard]] int operator() (std::size_t i, std::size_t j)const { return tab_[i][j];}

    void reset();

private:
    void resetResource();

    bool calcEmptyPosSetBits();

    /// sets a (value - 1) bit to setTo in all bitsets
    void changeBitInBitsets(int i, int j, int g, int value, bool setTo = true);

    friend std::ostream& operator<<(std::ostream &oss, const Sudoku &sudoku);

private:
    int tab_[9][9]{};

    /// holds a row, column, group of empty place
    std::vector<int> emptyPos_;
    std::vector<std::bitset<9u>> rows_, columns_, groups_;
};

#endif //SDL2_TEST_SUDOKU_H
