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

Parser::Parser() : _deg(0)
{
}

Parser::Parser(std::string equation) : _deg(0)
{
	auto sides = split(equation, '=');

	if (sides.size() != 2)
	{
		ERROR("The equation is not formatted correctly.")
		exit(EXIT_FAILURE);
	}

	auto side1_coefs = _sideParser(sides[0]);
	auto side2_coefs = _sideParser(sides[1]);

	this->_coefs = side1_coefs - side2_coefs;

	// Detect polynomial degree
	for (auto i = this->_coefs.coefs.begin(); i != this->_coefs.coefs.end(); ++i)
	{
		if (i->first > this->_deg)
			this->_deg = i->first;
	}

	for (auto item : _coefs.coefs)
	{
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

const std::regex matcher("^X\\^.*[0-9]$");

std::string Parser::_removeTrailingZeros(std::string number)
{
	if (number.find('.') == std::string::npos)
	{
		return number;
	}

	auto ret = number;
	for (auto c = ret.rbegin(); c != ret.rend(); ++c)
	{
		if (*c == '0' && *(c + 1) == '.')
		{
			ret.pop_back();
			ret.pop_back();
		}
		else if (*c == '0')
		{
			ret.pop_back();
		}
		else
		{
			break;
		}
	}
	return ret;
}

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

		// Detect sign
		auto pos = side.find(item);
		for (auto i = pos; i >= 0; --i)
		{
			if (side[i] == '-')
			{
				ret.coefs[index] *= -1;
				break;
			}
			else if (side[i] == '+')
			{
				break;
			}
			else if (i == 0)
			{
				break;
			}
		}
		++index;
	}

	return ret;
}

void Parser::printReducedForm(void)
{
	std::string reduced_form;
	for (unsigned int i = 0; i <= this->_deg; ++i)
	{
		if (this->_coefs.coefs[i] >= 0 && i == 0)
		{
			reduced_form.append(_removeTrailingZeros(std::to_string(this->_coefs.coefs[i])));
		}
		else if (this->_coefs.coefs[i] >= 0)
		{
			reduced_form.append("+ ");
			reduced_form.append(_removeTrailingZeros(std::to_string(this->_coefs.coefs[i])));
		}
		else
		{
			reduced_form.append("- ");
			reduced_form.append(_removeTrailingZeros(std::to_string(-this->_coefs.coefs[i])));
		}
		reduced_form += " * ";
		reduced_form += "X^";
		reduced_form.append(std::to_string(i));
		reduced_form += " ";
	}
	MSG("Reduced form: " << reduced_form << "= 0");
}

void Parser::printDegree(void) const
{
	MSG("Polynomial degree: " << this->_deg);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

coefficients Parser::getCoefs(void) const
{
	return _coefs;
}

/* ************************************************************************** */