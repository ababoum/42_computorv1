#include "../inc/Parser.hpp"

/*
** ------------------------------- ACCESSORIES --------------------------------
*/

coefficients coefficients::operator-(coefficients rhs)
{
	coefficients ret;

	for (unsigned int index = 0; index < this->coefs.size(); ++index)
	{
		ret.coefs.insert(
			std::make_pair(index, this->coefs[index] - rhs.coefs[index]));
	}

	return ret;
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Parser::Parser()
{
}

Parser::Parser(std::string equation)
{
	auto sides = split(equation, '=');

	if (sides.size() != 2)
	{
		ERROR("The equation is not formatted correctly.")
		exit(EXIT_FAILURE);
	}

	auto side1_coefs = _sideParser(sides[0]);
	auto side2_coefs = _sideParser(sides[1]);

	_coefs = side1_coefs - side2_coefs;

	for (auto item: _coefs.coefs) {
		DEBUG(item.first << ": " << item.second);
	}
}

Parser::Parser(const Parser &src)
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Parser::~Parser()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Parser &Parser::operator=(Parser const &rhs)
{
	if (this != &rhs)
	{
		(void)rhs;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

const std::regex matcher("^X\\^.?[0-2]$");

coefficients Parser::_sideParser(std::string side) const
{
	coefficients ret;
	auto items = split(side, "+-");
	int index = 0;

	for (auto &item : items)
	{
		auto elements = split(item, " *");
		if (elements.size() != 2)
		{
			ERROR("The equation is not formatted correctly: exponents must be written as 'coef * X^n'")
			exit(EXIT_FAILURE);
		}

		if (std::regex_match(elements[1], matcher))
		{
			if (elements[1][2] - '0' == index)
			{
				ret.coefs[index] = std::stod(elements[0]);
			}
			else
			{
				ERROR("The equation is not formatted correctly: exponents must be organized and present")
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			ERROR("The equation is not formatted correctly: exponents must be written as 'coef * X^n'")
			exit(EXIT_FAILURE);
		}
		++index;
	}

	return ret;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

coefficients Parser::getCoefs(void) const
{
	return _coefs;
}

/* ************************************************************************** */