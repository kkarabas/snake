#ifndef ACTION_H
#define ACTION_H

#include <termios.h>
#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <unistd.h>

class Action
{
public:
	struct termios saved_attributes ;
	const int read_fd = STDIN_FILENO ;

	enum Action_en {
		Action_KEY_UP,
		Action_KEY_DOWN,
		Action_KEY_LEFT,
		Action_KEY_RIGHT,
		Action_KEY_ESC,
		Action_TIMEOUT,
		Action_UNKNOWN_KEY
	};

	Action() ;
	~Action() ;

	void setTimeout() ;
	void resetTimeout() ;
	Action::Action_en getKey () ;
	Action_en getAction(char*, int) ;
	void sleepRest() ;
	int getTV() ;

private:
	struct timeval m_tv {0, 250000} ;
	struct timeval m_timeout {0, 250000} ;

	void reset_input_mode () ;
	void set_input_mode () ;

};

#endif // ACTION_H
