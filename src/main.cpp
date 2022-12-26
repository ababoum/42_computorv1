#include "../inc/Parser.hpp"
#include "../inc/utils.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		ERROR("Wrong number of arguments.\nusage: ./computor \"a * X^2 + b * X^1 + c * X^0 = ...\"")	
		return (EXIT_FAILURE);
	}
	Parser prs((std::string(av[1])));

	prs.printReducedForm();
	prs.printDegree();
	return (EXIT_SUCCESS);
}