#include "field.h"
#include <iostream>


Field::Field(){  // задаем размеры поля
    m_field.resize(fieldSize_row);
    for (int i = 0; i < fieldSize_row; i++){
       m_field.at(i).resize(fieldSize_col);
    }

    for (int i = 0; i < fieldSize_row; i++){
       for (int j = 0; j < fieldSize_col; j++){
            m_field[i][j] = emptyElement;
       }
    }
}

void Field::printField() const {
    for (int i = 0; i < fieldSize_col; i++)
        std::cout << '_';
    std::cout << std::endl;
    for (int i = 0; i < fieldSize_row; i++){
        std::cout << '|';
        for (int j = 0; j < fieldSize_col; j++){
            std::cout << m_field[i][j];
       }
        std::cout << '|' << std::endl;
    }
    for (int i = 0; i < fieldSize_col; i++)
        std::cout << '_';
    std::cout << std::endl;
}

const std::vector<std::vector<char>>& Field::getField() const{
    return m_field;
}


