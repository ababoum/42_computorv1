#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <iostream>
# include <string>
# include <cmath>
# include "Parser.hpp"

class Solver
{

public:
	Solver(Parser &prs);
	~Solver();

	// Methods
	void	compute(void);

private:

	Parser	& _parser;
};

#endif /* ********************************************************** SOLVER_H */