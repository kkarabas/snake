#ifndef DRAWINTERFACE_H
#define DRAWINTERFACE_H

#include <vector>
#include <string>
#include <memory>
#include"Field/game.h"

class DrawInterface{

protected:
	virtual ~DrawInterface() = default ;
	DrawInterface& operator=(const DrawInterface&) = default ;

public:
	virtual void drawGameField( const std::vector< std::vector<char> > & , const Game::Coord&, const Game::Coord& ) = 0 ;
	static std::shared_ptr<DrawInterface> CreateDrawInt() ;
	virtual void printMsg(const std::string&) = 0 ;
	virtual void printScore(int, int) = 0 ;
	virtual void printYummies (int, int) = 0 ;
};

#endif // DRAWINTERFACE_H
