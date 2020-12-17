#include <iostream>
#include <ctime>
#include "Gameplay/gameplay.h"
#include <fstream>

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();

    std::streambuf *bak;
    std::ofstream file;

    file.open("./log.txt") ;
    if(!file) std::cout << "error";

    bak = std::cout.rdbuf();  // сохраняем

    std::cout.rdbuf(file.rdbuf()); // перенапраляем в файл

    Gameplay* gameplay = new Gameplay() ;
    gameplay -> run() ;

    delete gameplay ;


    std::cout.rdbuf(bak); //
    return 0;
}
