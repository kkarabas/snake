#include "action.h"

#include <iostream>
#include <cstring>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <sys/types.h>
#include <unistd.h>


Action::Action()
{
	ioctl (STDIN_FILENO, KDSKBMODE, K_MEDIUMRAW) ;
	struct termios tattr ;
	tcgetattr (STDIN_FILENO, &saved_attributes) ;

	tcgetattr (STDIN_FILENO, &tattr) ;
	tattr.c_lflag &= ~(ICANON|ECHO) ;
	tcsetattr (STDIN_FILENO, TCSANOW, &tattr) ;
}

Action::~Action()
{
	tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes) ;
	ioctl(STDIN_FILENO, KDSKBMODE, K_XLATE) ;
}

Action::Action_en Action::getKey()
{
	char buffer[10] ;
	int retval ;
	std::string timeout = "timeout" ;
	fd_set rfds ;
	FD_ZERO(&rfds) ;
	FD_SET(read_fd, &rfds) ;

    retval = select(1, &rfds, NULL, NULL, &m_tv);
	if (retval == 1) {
        int length = read(read_fd, buffer, 10);
        //std::string key_value (buffer, length);
        //std::string key_code;
        //for (int i = 0; i < length; i++) key_code += std::to_string((int)key_value[i]);
		return (getAction (buffer, length)) ;
	} else if (retval == 0) {
		m_tv = m_timeout ;
		return Action_en::Action_TIMEOUT ;
	} else {
		std::cerr << "Select err" ;
		std::exit(1) ;
    }
}

void Action::setTimeout()
{
	m_timeout.tv_sec = 0 ;
	m_timeout.tv_usec *= 0.75 ;
}

void Action::resetTimeout()
{
	m_tv = m_timeout ;
}

void Action::sleepRest()
{
	usleep(m_tv.tv_usec) ;
	m_tv = m_timeout ;
}

int Action::getTV()
{
    return m_tv.tv_usec ;
}

namespace {
    static const std::string key_up   ( "\x1b\x5b\x41" ) ;
    static const std::string key_down ( "\x1b\x5b\x42" ) ;
    static const std::string key_right( "\x1b\x5b\x44" ) ;
    static const std::string key_left ( "\x1b\x5b\x43" ) ;

    static const std::string key_esc ( "\x1b" ) ;
}

Action::Action_en Action::getAction(char* key_code, int length)
{
	std::string str (key_code, length) ;
	if ( str == key_up )         return Action_en::Action_KEY_UP ;
		else if ( str == key_down )  return Action_en::Action_KEY_DOWN ;
		else if ( str == key_left )  return Action_en::Action_KEY_RIGHT ;
		else if ( str == key_right ) return Action_en::Action_KEY_LEFT ;

		else if ( str == key_esc )    return Action_en::Action_KEY_ESC ;
		else return Action_en::Action_UNKNOWN_KEY ;
}
