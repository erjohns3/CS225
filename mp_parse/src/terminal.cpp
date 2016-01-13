#include "terminal.h"

namespace cs225{

	terminal::terminal(double value)
	{
		value_ = value;
	}

	double terminal::value() const
	{
		return value_;
	}

	std::unique_ptr<terminal> make_term(double value)
	{
		return std::unique_ptr<terminal> {new terminal{value}};
	}

}