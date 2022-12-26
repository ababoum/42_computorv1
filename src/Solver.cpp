#include "../inc/Solver.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Solver::Solver(Parser &prs) : _parser(prs)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Solver::~Solver()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

void Solver::compute(void)
{
	if (_parser.getDegree() > 2)
	{
		MSG("The polynomial degree is strictly greater than 2, I can't solve.")
		exit(EXIT_SUCCESS);
	}

	auto coefs = _parser.getCoefs().coefs;

	// Solve assertions
	if (_parser.getDegree() == 0)
	{
		if (coefs[0] == 0)
		{
			MSG("Every real number is a solution.")
			exit(EXIT_SUCCESS);
		}
		else
		{
			MSG("No solution: the equation is wrong.")
			exit(EXIT_SUCCESS);
		}
	}

	// Solve 1st degree equations
	if (_parser.getDegree() == 1 ||
		(_parser.getDegree() == 2 && coefs[2] == 0))
	{
		if (coefs[1] == 0 && coefs[0] != 0)
		{
			MSG("No solution: the equation is wrong.")
			exit(EXIT_SUCCESS);
		}
		else if (coefs[1] == 0 && coefs[0] == 0)
		{
			MSG("Every real number is a solution.")
			exit(EXIT_SUCCESS);
		}
		else
		{
			double solution;

			if (coefs[0] == 0)
				solution = 0;
			else
				solution = -coefs[0] / coefs[1];
			MSG("The solution is:\n"
				<< removeTrailingZeros(std::to_string(solution)));
		}
	}

	// Solve 2nd degree equations
	if (_parser.getDegree() == 2 && coefs[2] != 0)
	{
		auto disc = coefs[1] * coefs[1] - 4 * coefs[0] * coefs[2];
		if (disc < 0)
		{
			double imaginary, real;

			imaginary = std::sqrt(-disc) / ( 2 * coefs[2]);
			real = (-coefs[1]) / (2 * coefs[2]);

			auto solution1 = (real == 0 ? "" : removeTrailingZeros(std::to_string(real))) 
				+ (imaginary < 0 ? " - ": " + ")
				+ removeTrailingZeros(std::to_string(imaginary))
				+ " * i";

			auto solution2 = (real == 0 ? "" : removeTrailingZeros(std::to_string(real))) 
				+ (imaginary < 0 ? " + ": " - ")
				+ removeTrailingZeros(std::to_string(imaginary))
				+ " * i";

			MSG("Discriminant is strictly negative, the two solutions are:\n"
				<< solution1 << "\n"
				<< solution2);
			exit(EXIT_SUCCESS);
		}
		else if (disc == 0)
		{
			double solution;

			solution = -coefs[1] / (2 * coefs[2]);
			solution = solution == 0 ? 0 : solution; // takes off the - sign from 0
			
			MSG("Discrimant is equal to zero. The solution is:\n"
				<< removeTrailingZeros(std::to_string(solution)));
		}
		else
		{
			double solution1, solution2;

			solution1 = (-coefs[1] + std::sqrt(disc)) / (2 * coefs[2]);
			solution2 = (-coefs[1] - std::sqrt(disc)) / (2 * coefs[2]);

			solution1 = solution1 == 0 ? 0 : solution1; // takes off the - sign from 0
			solution2 = solution2 == 0 ? 0 : solution2; // takes off the - sign from 0

			MSG("Discriminant is strictly positive, the two solutions are:\n"
				<< removeTrailingZeros(std::to_string(solution1)) << "\n"
				<< removeTrailingZeros(std::to_string(solution2)));
		}
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */