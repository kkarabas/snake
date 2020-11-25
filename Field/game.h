#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include<functional>

class Game{
public:
	static const int fieldSize_row=15 ;
	static const int fieldSize_col=38 ;
	static const char filledElement = '*' ;
	static const char emptyElement = ' ' ;

	enum Direction {
		UP_DIRECTION,
		DOWN_DIRECTION,
		LEFT_DIRECTION,
		RIGHT_DIRECTION
	} ;

	struct Coord {
		int row ;
		int col ;
		Direction dir ;
	} ;

	Game() ;
	void setDirection(Direction) ;
	void setNextMove() ;
	void setNextMove(Direction&) ;
	const Coord& getNextMove() const ;
	Direction getDirection() const ;
	std::list<Coord>& getSnake() ;
	const std::vector<std::vector<char>>& getField() const ;
	const Coord& getYummy() const;
	void addHead() ;
	void removeTail() ;
	void generateYummy() ;
	bool checkSelfEat() ;
	bool checkBoundries() ;
	bool checkYummyEat() ;
	const Coord& getHead() const ;
	const Coord& getTail() const ;
	void changeReverse() ;
	bool isReverse() const ;

private:
	std::vector<std::vector<char>> m_field ;
	std::list<Coord> m_snake ;
	Direction m_direction = RIGHT_DIRECTION ;
	Coord m_nextMove;
	Coord m_yummy ;
	int getRandomNumber(int , int) const ;
	bool checkYummy(int, int) ;
	bool m_reverseMovement = false ;
} ;

#endif // GAME_H
