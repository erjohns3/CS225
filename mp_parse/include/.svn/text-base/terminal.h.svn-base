#ifndef CS225_TERMINAL_H_
#define CS225_TERMINAL_H_
#include "node.h"
#include <iostream>

namespace cs225
{
	class terminal: public node
	{
		
	public:

		terminal(double value);

		double value() const;

	private:

		double value_;

	};

	std::unique_ptr<terminal> make_term(double value);

}
#endif