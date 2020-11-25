#ifndef NCURS_H
#define NCURS_H

#include "Gameplay/drawinterface.h"
#include <ncurses.h>
#include <memory>

class Gameplay;

class NCurs: public DrawInterface
{
public:
	NCurs() ;
	~NCurs() ;
	void drawGameField( const std::vector< std::vector<char> > & , const Game::Coord&, const Game::Coord& ) override ;
	void printMsg(const std::string&) override ;
	void printScore(int, int) override ;
	void printYummies(int, int) override ;

private:
	WINDOW *win_field ;
	WINDOW *win_score;
};

#endif // NCURS_H
