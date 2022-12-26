#include "../inc/Parser.hpp"

/*
** ------------------------------- ACCESSORIES --------------------------------
*/

coefficients coefficients::operator-(coefficients rhs)
{
	coefficients ret;

	for (unsigned int index = 0;
		 index < this->coefs.size() || index < rhs.coefs.size();
		 ++index)
	{
		ret.coefs.insert(
			std::make_pair(index, this->coefs[index] - rhs.coefs[index]));
	}

	return ret;
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

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
		if (i->first > this->_deg && i->second != 0)
			this->_deg = i->first;
	}
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

/*
** --------------------------------- METHODS ----------------------------------
*/

const std::regex matcher("^X\\^.*[0-9]$");

coefficients Parser::_sideParser(std::string side) const
{
	coefficients ret;
	auto items = split(side, "+-");
	int index = 0;

	// clean the vector if the side begins with '-' or '+'

	if (items.size() >= 1 && trim_copy(items[0]).size() == 0)
	{
		items.erase(items.begin());
	}

	for (auto &item : items)
	{
		auto elements = split(item, " *");
		if (elements.size() != 2)
		{
			ERROR("The equation is not formatted correctly: exponents must be written as 'coef * X^n'.")
			exit(EXIT_FAILURE);
		}

		if (std::regex_match(elements[1], matcher))
		{
			if (elements[1][2] - '0' == index)
			{
				try
				{
					ret.coefs[index] = std::stod(elements[0]);
				}
				catch (std::exception e)
				{
					ERROR("The equation is not formatted correctly: coefficients must be convertable to a double type.")
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				ERROR("The equation is not formatted correctly: exponents must be organized and present.")
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			ERROR("The equation is not formatted correctly: exponents must be written as 'coef * X^n'.")
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
			reduced_form.append(removeTrailingZeros(std::to_string(this->_coefs.coefs[i])));
		}
		else if (this->_coefs.coefs[i] >= 0)
		{
			reduced_form.append("+ ");
			reduced_form.append(removeTrailingZeros(std::to_string(this->_coefs.coefs[i])));
		}
		else
		{
			reduced_form.append("- ");
			reduced_form.append(removeTrailingZeros(std::to_string(-this->_coefs.coefs[i])));
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

unsigned int Parser::getDegree(void) const
{
	return _deg;
}

/* ************************************************************************** */