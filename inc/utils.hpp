#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
# include <vector>

# define F_NONE		"\e[37;0m"
# define F_BOLD		"\e[1m"
# define F_ORANGE	"\e[38m"
# define F_RED		"\e[31m"
# define F_YELLOW	"\e[33m"
# define F_GREEN	"\e[32m"
# define F_CYAN		"\e[36m"
# define F_BLUE		"\e[34m"


# define ERROR(x)	std::cerr << x << '\n';
# define MSG(x)		std::cout << x << '\n';
# define DEBUG(x)	std::cout << F_YELLOW << x << F_NONE << '\n';

std::vector<std::string>	split(const std::string &str, char delim);
std::vector<std::string>	split(const std::string &str, const char *set_delim);

#endif