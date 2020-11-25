#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <memory>
#include "Field/game.h"

class DrawInterface ;
class Action ;

class Gameplay
{
public:
	Gameplay() ;
	void run() ;
	~Gameplay() ;

private:
	std::shared_ptr<DrawInterface> m_drawInt ;
	//std::unique_ptr<Game> m_game = std::make_unique <Game>() ;
	Game* m_game ;
	//std::unique_ptr<Action> m_action = std::make_unique <Action>() ;
	Action* m_action ;
	void setNextMove(Game::Coord &, bool) ;
	int m_yummies = 0 ;
	int m_level = 1 ;
};

#endif // GAMEPLAY_H
