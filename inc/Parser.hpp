#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <string>
# include <regex>
# include "utils.hpp"

struct coefficients {
	std::map<unsigned int, double> coefs;

	coefficients operator-(coefficients rhs);
};

class Parser
{
	public:
		Parser( std::string equation );
		~Parser();

		Parser &		operator=( Parser const & rhs );

	private:
		Parser();
		Parser( Parser const & src );

		coefficients	_sideParser(std::string side) const;

	// Methods
	public:
		coefficients	getCoefs(void) const;

	// Attributes
	private:
		coefficients _coefs;

};

#endif /* ********************************************************** PARSER_H */