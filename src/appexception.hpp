#ifndef APPEXCEPTION_HPP
#define APPEXCEPTION_HPP

#include <exception>

class appexception : public std::exception
{
public:

	explicit appexception(char const* const mess) noexcept
		: std::exception(mess) {}

};


#endif // !APPEXCEPTION_HPP
