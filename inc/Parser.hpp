#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <regex>
#include "utils.hpp"

struct coefficients
{
	std::map<unsigned int, double> coefs;

	coefficients operator-(coefficients rhs);
};

class Parser
{
public:
	Parser(std::string equation);
	~Parser();

private:
	coefficients _sideParser(std::string side) const;

	// Methods and accessors
public:
	coefficients getCoefs(void) const;
	unsigned int getDegree(void) const;
	void printReducedForm(void);
	void printDegree(void) const;

	// Attributes
private:
	coefficients _coefs;
	unsigned int _deg;
};

#endif /* ********************************************************** PARSER_H */