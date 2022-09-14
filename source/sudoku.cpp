#include "sudoku.h"

Sudoku::Sudoku() {
    emptyPos_.reserve(64U);
    rows_.reserve(9U);
    columns_.reserve(9U);
    groups_.reserve(9U);
    resetResource();
}

[[maybe_unused]] Sudoku::Sudoku(const int (&tab)[9][9]): Sudoku() {
    setSudoku(tab);
}

bool Sudoku::solve() {
    if(!this->calcEmptyPosSetBits()){
        return false;
    }

    bool numberIsGood, hasReturned = false;

    for (std::size_t pos = 0; pos < emptyPos_.size(); pos++) {
        /// emptyPos_[pos] = i * 100 + j * 10 + g
        int i = (emptyPos_[pos] % 1000) / 100;
        int j = (emptyPos_[pos] % 100) / 10;
        int g = emptyPos_[pos] % 10;

        numberIsGood = false;
        while (!numberIsGood) {
            int &value = tab_[i][j];
            value += 1;

            numberIsGood = true;

            /// remove previously good number from bitsets
            if (hasReturned){
                /// value - 1, cuz it was incremented and we erase a old value
                this->changeBitInBitsets(i, j, g, value - 1, false);
                hasReturned = false;
            }

            if (value > 9) {
                if (pos == 0) ///there is nowhere to return
                    return false;
                else {
                    this->changeBitInBitsets(i, j, g, value, false);
                    pos -= 2;
                    hasReturned = true;
                }
                value = 0;
                break;
            }

            /// checking for collision
            if (rows_[i][value - 1] || columns_[j][value - 1] || groups_[g][value - 1])
                numberIsGood = false;

            /// adding to bitsets
            if (numberIsGood)
                this->changeBitInBitsets(i, j, g, value, true);
        }
    }
    return true;
}

bool Sudoku::calcEmptyPosSetBits() {
    /// Set bitsets and emptyPlace to empty
    resetResource();

    for (std::size_t i = 0; i < 9; i++){
        for(std::size_t j = 0; j < 9; j++){
            if (tab_[i][j] == 0)
                emptyPos_.emplace_back(i * 100 + j * 10 + ((i / 3) * 3 + j / 3));
            else {
                const int &pos = tab_[i][j] - 1;
                if (rows_[i].test(pos) || columns_[j].test(pos) || groups_[(i / 3) * 3 + j / 3].test(pos)){
                    return false;
                }
                rows_[i].set(pos);
                columns_[j].set(pos);
                groups_[(i / 3) * 3 + j / 3].set(pos);
            }
        }
    }
    return true;
}

void Sudoku::setSudoku(const int (&tab)[9][9]) {
    for (std::size_t i = 0; i < 9; ++i){
        for (std::size_t j = 0; j < 9; ++j)
            this->setSudoku(i, j ,tab[i][j]);
    }

}

void Sudoku::setSudoku(std::size_t i, std::size_t j, int number) {
    if (number > 9 || number < 1)
        number = 0;
    tab_[i][j] = number;
}

void Sudoku::resetResource() {
    for (std::size_t i = 0; i < 9; ++i){
        rows_[i].reset();
        columns_[i].reset();
        groups_[i].reset();
    }
    emptyPos_.clear();
}

std::ostream &operator<<(std::ostream &oss, const Sudoku &sudoku) {
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            oss << sudoku.tab_[i][j] << " ";
            if (j == 2 || j == 5 || j == 8)
                oss << " ";
        }
        if (i == 2 || i == 5)
            oss << "\n";
        if (i != 8)
            oss << "\n";
    }
    return oss;
}

void Sudoku::reset() {
    for (auto &row : tab_){
        for (auto &ele : row){
            ele = 0;
        }
    }
}

inline void Sudoku::changeBitInBitsets(int i, int j, int g, int value, bool setTo) {
    rows_[i][value - 1] = setTo;
    columns_[j][value - 1] = setTo;
    groups_[g][value - 1] = setTo;
}




