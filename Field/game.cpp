#include "game.h"
#include "Field/game.h"

#include <random>

Game::Game()
{
// задаем размеры поля
	m_field.resize(fieldSize_row) ;
	for (int i = 0 ; i < fieldSize_row ; i++) {
		m_field.at(i).resize(fieldSize_col) ;
	}

	for (int i = 0 ; i < fieldSize_row ; i++) {
		for (int j = 0 ; j < fieldSize_col ; j++) {
			m_field[i][j] = emptyElement ;
		}
	}

// Создаем посередине поля змейку из 5 элементов.
// направление по умолчанию направо.
	for ( auto i = 0 ; i < 5 ; i++ ) {
		Coord temp { Game::fieldSize_row/2 , i + Game::fieldSize_col/4 - 3 , Game::Direction::RIGHT_DIRECTION } ;
		m_snake.push_back(temp) ;
	}

//добавляем змейку на поле
	for (auto& element: m_snake)
		m_field [element.row][element.col] = filledElement ;

//Задаем следущий ход
	m_nextMove.row = m_snake.back().row ;
	m_nextMove.col =  m_snake.back().col  + 1 ;
}

int Game::getRandomNumber(int min, int max) const
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0) ;
	return static_cast<int>(rand() * fraction * (max - min + 1) + min) ;
}

const Game::Coord& Game::getHead() const
{
	if (m_reverseMovement) return m_snake.front() ;
	else return m_snake.back() ;
}

const Game::Coord& Game::getTail() const
{
	if (m_reverseMovement) return m_snake.back() ;
	else return m_snake.front() ;
}

bool Game::checkYummy(int row, int col)
{
	for (auto& element: m_snake) {
		if ( (element.row == row) && (element.col == col) )
			return true ;
	}
	return false ;
}

//генерируем и добавляем вкусняшку
void Game::generateYummy() {
	do {
		m_yummy.row = getRandomNumber(0, Game::fieldSize_row-1) ;
		m_yummy.col = getRandomNumber(0, Game::fieldSize_col-1) ;
	}
	while ( checkYummy( m_yummy.row , m_yummy.col ) ) ;
	m_field.at(m_yummy.row).at(m_yummy.col) = filledElement ;
}

void Game::setDirection(Direction dir)
{
	m_direction = dir ;
}

Game::Direction Game::getDirection() const
{
	return m_direction ;
}

const Game::Coord& Game::getYummy() const
{
	return m_yummy ;
}

const std::vector<std::vector<char>>& Game::getField() const
{
	return m_field ;
}

std::list<Game::Coord>& Game::getSnake()
{
	return m_snake ;
}

void Game::setNextMove()
{
	switch (m_direction) {
	case Direction::UP_DIRECTION:
		m_nextMove.row = getHead().row - 1 ;
		m_nextMove.col = getHead().col ;
		break ;
	case Direction::DOWN_DIRECTION:
		m_nextMove.row = getHead().row + 1 ;
		m_nextMove.col = getHead().col ;
		break ;
	case Direction::LEFT_DIRECTION:
		m_nextMove.row = getHead().row ;
		m_nextMove.col = getHead().col - 1 ;
		break ;
	case Direction::RIGHT_DIRECTION:
		m_nextMove.row = getHead().row ;
		m_nextMove.col = getHead().col + 1 ;
		break ;
	}
}

void Game::setNextMove(Direction &dir)
{
	switch (dir) {
	case Direction::UP_DIRECTION:
		m_nextMove.row = getHead().row - 1 ;
		m_nextMove.col = getHead().col ;
		break ;
	case Direction::DOWN_DIRECTION:
		m_nextMove.row = getHead().row + 1 ;
		m_nextMove.col = getHead().col ;
		break ;
	case Direction::LEFT_DIRECTION:
		m_nextMove.row = getHead().row ;
		m_nextMove.col = getHead().col - 1 ;
		break ;
	case Direction::RIGHT_DIRECTION:
		 m_nextMove.row = getHead().row ;
		m_nextMove.col = getHead().col + 1 ;
		break ;
	}
}

const Game::Coord& Game::getNextMove() const
{
	return m_nextMove ;
}

bool Game::checkSelfEat()
{
	for (auto element: m_snake) {
		if ( (m_nextMove.row == element.row) && (m_nextMove.col == element.col) )
			return true ;
	}
	return false ;
}

bool Game::checkBoundries()
{
	if ( (m_nextMove.row == fieldSize_row)
		|| (m_nextMove.row < 0)
		|| (m_nextMove.col == fieldSize_col)
		|| (m_nextMove.col < 0) )
        return true ;
    else return false ;
}

bool Game::checkYummyEat()
{
	if ( (m_nextMove.row == m_yummy.row) && (m_nextMove.col == m_yummy.col) )
		return true ;
	else return false ;
}

void Game::addHead()
{
	m_field [m_nextMove.row][m_nextMove.col] = filledElement ;
}

void Game::removeTail()
{
	m_field [getTail().row][getTail().col] = emptyElement ;
}

void Game::changeReverse()
{
	m_reverseMovement = !m_reverseMovement ;
}

bool Game::isReverse() const
{
	return m_reverseMovement ;
}
