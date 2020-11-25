#include "gameplay.h"
#include "Field/game.h"
#include "Action/action.h"
#include "Gameplay/drawinterface.h"
#include <string>
#include<iostream>

Gameplay::Gameplay()
{
	m_drawInt = DrawInterface::CreateDrawInt() ;
	m_game = new Game() ;
	m_action = new Action() ;
}

Gameplay::~Gameplay()
{
	delete m_game ;
	delete m_action ;
}

// Мы записываем в лист направления, когда змейка двигается в прямом направлении
// Если змейка двигается в обратном направлении, то
// 1) если произошло изменение направления, то следующий ход мы должны расчитать из этого направления,
//    а в змеку записать записать обратное ("прямое") направление
// 2) если змейка двигается по таймауту, то должно  придти need_to_reverse_direction = true, и
//    следующий ход мы расчитываем из текущего направления, конвертировав его в обратное, а в змейку записываем "прямое"
// Если змейка двигается в прямом направлении, то просто расчитываем следующий ход из текущего направления
void Gameplay::setNextMove(Game::Coord& temp, bool need_to_reverse_direction)
{
	if (m_game -> isReverse()) {
		Game::Direction reverse_dir ;
			switch (m_game -> getDirection()) {
			case Game::Direction::UP_DIRECTION:
				reverse_dir = Game::Direction::DOWN_DIRECTION ;
				break ;
			case Game::Direction::DOWN_DIRECTION:
				reverse_dir = Game::Direction::UP_DIRECTION ;
				break ;
			case Game::Direction::LEFT_DIRECTION:
				reverse_dir = Game::Direction::RIGHT_DIRECTION ;
				break ;
			case Game::Direction::RIGHT_DIRECTION:
				reverse_dir = Game::Direction::LEFT_DIRECTION ;
				break ;
			}
		if (need_to_reverse_direction) {
			m_game -> setNextMove(reverse_dir) ;
			temp = { m_game -> getNextMove().row, m_game -> getNextMove().col , m_game -> getDirection() } ;
		} else {
			m_game -> setNextMove() ;
			temp = { m_game -> getNextMove().row, m_game -> getNextMove().col , reverse_dir } ;
		}
	} else {
		m_game -> setNextMove() ;
		temp = {m_game -> getNextMove().row, m_game -> getNextMove().col , m_game -> getDirection() } ;
	}
}


void Gameplay::run()
{
	Action::Action_en key ;
	bool keyEsc = false ;
	bool gameover = false ;
	bool need_to_reverse_direction = false ;
	Game::Coord temp_next_move ;
	m_game -> generateYummy() ;

	m_drawInt -> printScore(m_yummies, m_level ) ;
	while (true) {
		bool changeDirection = false ;
		m_drawInt -> drawGameField( m_game -> getField() , m_game -> getYummy() , m_game -> getHead() ) ;
		key = m_action -> getKey() ;
		switch (key) {
		case  Action::Action_en::Action_KEY_UP:
//Прямое направление и напрвление вверх - break
//Обратное направление и направление вниз (т.е. реальное направление вверх)  - break
			if ( ( !(m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::UP_DIRECTION) )
				 ||( (m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::DOWN_DIRECTION) ) )
				break ;
//Смена направления на обратное (прямое)
			if ( ( !(m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::DOWN_DIRECTION) )
				 || ( (m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::UP_DIRECTION) ) ) {
				need_to_reverse_direction = true ;
				changeDirection = true ;
				m_game -> changeReverse() ;
				break ;
			}
			m_game -> setDirection( Game::Direction::UP_DIRECTION ) ;
			changeDirection = true ;
			break ;

		case Action::Action_en::Action_KEY_DOWN:
			if ( ( !(m_game -> isReverse()) && m_game -> getDirection() == Game::Direction::DOWN_DIRECTION )
				 || ( (m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::UP_DIRECTION) ) ) {
				break ;
			}
			if ( ( !(m_game -> isReverse()) && m_game -> getDirection() == Game::Direction::UP_DIRECTION )
				 || ( (m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::DOWN_DIRECTION) ) ) {
				need_to_reverse_direction = true ;
				changeDirection = true ;
				m_game -> changeReverse() ;
				break ;
			}
			m_game -> setDirection( Game::Direction::DOWN_DIRECTION ) ;
			changeDirection = true ;
			break ;

		case Action::Action_en::Action_KEY_LEFT:
			if ( ( !(m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::LEFT_DIRECTION) )
				 || ( m_game -> isReverse() && (m_game -> getDirection() == Game::Direction::RIGHT_DIRECTION) ) ) {
				break ;
			}
			if ( ( !(m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::RIGHT_DIRECTION) )
				 || ( (m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::LEFT_DIRECTION) ) ) {
				need_to_reverse_direction = true ;
				changeDirection = true ;
				m_game -> changeReverse() ;
				break ;
			}
			m_game -> setDirection( Game::Direction::LEFT_DIRECTION ) ;
			changeDirection = true ;
			break ;

		case Action::Action_en::Action_KEY_RIGHT:
			if ( ( !(m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::RIGHT_DIRECTION) )
				 ||( (m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::LEFT_DIRECTION) ) ) {
				break ;
			}
			if ( ( !(m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::LEFT_DIRECTION) )
				 || ( (m_game -> isReverse()) && (m_game -> getDirection() == Game::Direction::RIGHT_DIRECTION) ) ) {
				need_to_reverse_direction = true ;
				changeDirection = true ;
				m_game -> changeReverse() ;
				break ;
			}
			m_game -> setDirection( Game::Direction::RIGHT_DIRECTION ) ;
			changeDirection = true ;
			break ;

		case Action::Action_en::Action_TIMEOUT:
			need_to_reverse_direction = true ;
			break;

		case Action::Action_en::Action_KEY_ESC:
			keyEsc = true ;
			break ;

		default: break ;
		}
// Если направление не сменилось, но key не равно timeout (нажата кнопка в том же направлении), continue
		if (!changeDirection && !(key == Action::Action_en::Action_TIMEOUT) ) continue ;
// если произошла смена направления на обратное, берем направление из новой головы змейки
		if (need_to_reverse_direction)
			m_game -> setDirection( m_game -> getHead().dir ) ;
// расчитываем следующий ход и записываем в temp
		setNextMove(temp_next_move, need_to_reverse_direction) ;
		need_to_reverse_direction = false ;
// Проверка ESC
		if (keyEsc) break ;
// Если при следующем ходе не происходит пересечения границ и самопоедания, то ОК, иначе gameover
		if ( (m_game -> checkBoundries()) || (m_game -> checkSelfEat()) ) {
			gameover = true ;
			break ;
		}
// Если съели вкусняшку
		if ( m_game -> checkYummyEat() ) {
			m_yummies++ ;

//Генерируем новую вкусняшку на поле
			m_game -> generateYummy() ;
//Изменение уровни и таймаута
			if (  (m_yummies > 5) && (m_level == 1) ) {
				m_action -> setTimeout() ;
				m_level ++ ;
			} else if ( (m_yummies > 10) && (m_level == 2) ) {
				m_action -> setTimeout() ;
				m_level ++ ;
			} else if ( (m_yummies > 15) && (m_level == 3) ) {
				m_action -> setTimeout() ;
				m_level ++ ;
			} else if ( (m_yummies > 20) && (m_level == 4) ) {
				m_action -> setTimeout() ;
				m_level ++ ;
			} else if ( (m_yummies > 25) && (m_level == 5) ) {
				m_action -> setTimeout() ;
				m_level ++ ;
			}
			m_drawInt -> printScore(m_yummies, m_level ) ;
// Если не съели вкусняшку
		} else {
//Убираем хвост с поля
			m_game -> removeTail() ;
//Удаляем хвост из змейки
			if (m_game -> isReverse()) m_game -> getSnake().pop_back() ;
			else m_game -> getSnake().pop_front() ;
		}

// Если реверсивное направление, то добавляем "следующий ход" в начало std::list, иначе в конец
		if (m_game -> isReverse()) m_game -> getSnake().push_front( temp_next_move ) ;
		else m_game -> getSnake().push_back( temp_next_move ) ;
//добавляем голову змейки на поле
		m_game -> addHead() ;
		m_drawInt -> drawGameField( m_game -> getField() , m_game -> getYummy(), m_game -> getHead()) ;
//Если в результате нажатия кнопок произошло изменение направления, то ждем остаток таймаута
		if ( changeDirection ) m_action -> sleepRest() ;
	}
}
