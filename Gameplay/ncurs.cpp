#include "Gameplay/ncurs.h"
#include <ncurses.h>
#include "Field/field.h"
#include "Gameplay/gameplay.h"

NCurs::NCurs()
{
	WINDOW *win = initscr( ) ;
	cbreak( ) ;
	curs_set( 0 ) ;
	noecho( ) ;
	start_color( ) ;
	box( stdscr, 0, 0 ) ;
	wrefresh(win) ;
	win_field = newwin( LINES - 7, COLS - 2, 6, 1 ) ;
	win_score = newwin( 5, COLS - 2 , 1 , 1 ) ;
	box( win_field, 0, 0 ) ;
	box ( win_score, 0, 0 ) ;
	wrefresh( win_field ) ;
	mvwprintw(win_score, 1, 1,"") ;
	wrefresh( win_score ) ;
}

NCurs::~NCurs()
{
	delwin( win_field ) ;
	delwin( win_score ) ;
	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr, LINES/2, COLS/2-11,"Thank you! Good bye!!!");
	wrefresh (stdscr);
	getch();
	endwin( ) ;
}

std::shared_ptr<DrawInterface> DrawInterface::CreateDrawInt()
{
	return std::make_shared<NCurs>() ;
}

void NCurs::drawGameField(const std::vector<std::vector<char>>& field, const Game::Coord& yummy, const Game::Coord& head)
{
	init_pair( 1, COLOR_CYAN, COLOR_CYAN ) ;
	init_pair( 2, COLOR_BLACK, COLOR_BLACK ) ;
	init_pair( 3, COLOR_RED, COLOR_RED ) ;
	init_pair( 4, COLOR_BLUE, COLOR_BLUE ) ;
	for (int i = 0; i < field.size(); i++) {
		for (int j = 0; j < field[0].size(); j++) {
			if ( field[i][j] == Field::filledElement ) {
				wattron(win_field,COLOR_PAIR(1)) ;
				mvwaddch( win_field, i + 1, 2*j + 1, Field::filledElement ) ;
				mvwaddch( win_field, i + 1, 2*j + 2, Field::filledElement ) ;
				wattroff(win_field, COLOR_PAIR(1)) ;
			} else {
				wattron(win_field, COLOR_PAIR(2)) ;
				mvwaddch( win_field, i + 1, 2*j + 1, Field::emptyElement ) ;
				mvwaddch( win_field, i + 1, 2*j + 2, Field::emptyElement ) ;
				wattroff(win_field, COLOR_PAIR(2)) ;
			}
		}
	}
	wattron(win_field,COLOR_PAIR(3)) ;
	mvwaddch( win_field, yummy.row + 1, 2*yummy.col + 1, Field::filledElement ) ;
	mvwaddch( win_field, yummy.row + 1, 2*yummy.col + 2, Field::filledElement ) ;
	wattroff(win_field, COLOR_PAIR(3)) ;

	wattron(win_field,COLOR_PAIR(4)) ;
	mvwaddch( win_field, head.row + 1, 2*head.col + 1, Field::filledElement ) ;
	mvwaddch( win_field, head.row + 1, 2*head.col + 2, Field::filledElement ) ;
	wattroff(win_field, COLOR_PAIR(4)) ;

	wrefresh(win_field);
}


void NCurs::printMsg(const std::string& str)
{
	mvwprintw(win_score, 1 , 1, str.c_str()) ;
	wrefresh(win_score) ;
}

void NCurs::printScore(int score, int level)
{
	mvwprintw(win_score, 2 , 1, "Yummies eaten:%i___" , score) ;
	mvwprintw(win_score, 2 , 20, "LEVEL:%i___" , level) ;
	wrefresh(win_score) ;
}

void NCurs::printYummies(int row, int col)
{
	mvwprintw(win_score, 3 , 1, "Yummy row:%i___" , row) ;
	mvwprintw(win_score, 3 , 20, "Yummy col:%i___" , col) ;
	wrefresh(win_score) ;
}
