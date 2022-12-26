#include "../inc/Parser.hpp"
#include "../inc/Solver.hpp"
#include "../inc/utils.hpp"

int main(int ac, char **av)
{
	std::string input;

	if (ac > 2)
	{
		ERROR("Wrong number of arguments.\n"
			<< "usage: ./computor \"c * X^0 + b * X^1 + a * X^2 = ...\"")
		return (EXIT_FAILURE);
	}
	else if (ac == 1)
	{
		while (input.empty())
		{
			MSG("Enter the equation you want to solve."
				<< "format: \"c * X^0 + b * X^1 + a * X^2 = ...\"")
			std::getline(std::cin, input);
			if (std::cin.eof()) {
				MSG("Exiting...");
				exit(EXIT_SUCCESS);
			}
		}
	}
	else
	{
		input = std::string(av[1]);
	}
	Parser prs(input);

	prs.printReducedForm();
	prs.printDegree();

	Solver solver(prs);

	solver.compute();

	return (EXIT_SUCCESS);
}