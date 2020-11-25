#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Snake;

class Field{
    public:

        static const int fieldSize_row=20 ;
        static const int fieldSize_col=70 ;
        static const char filledElement = '*' ;
        static const char emptyElement = ' ' ;


        Field();

        void printField() const ;
        const std::vector<std::vector<char>>& getField() const ;
        bool gameOver() ;
    private:
        std::vector<std::vector<char>> m_field ;

};

#endif // FIELD_H
