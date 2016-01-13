#include "binary_op.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "exponent.h"
#include "terminal.h"

namespace cs225
{

	binary_op::binary_op(std::unique_ptr<node> left, std::unique_ptr<node> right)
	{
		left_.swap(left);
		right_.swap(right);
	}

	double binary_op::value() const
	{
		return combine(left_->value(), right_->value());
	}

	std::unique_ptr<node> make_binary_op(const std::string& op, std::unique_ptr<node> left, std::unique_ptr<node> right)
	{
		if(op.compare("+") == 0)
			return std::unique_ptr<node> {new plus{std::move(left), std::move(right)}};
		else if(op.compare("-") == 0)
			return std::unique_ptr<node> {new minus{std::move(left), std::move(right)}};
		else if(op.compare("*") == 0)
			return std::unique_ptr<node> {new times{std::move(left), std::move(right)}};
		else if(op.compare("/") == 0)
			return std::unique_ptr<node> {new divide{std::move(left), std::move(right)}};
		else if(op.compare("^") == 0)
			return std::unique_ptr<node> {new exponent{std::move(left), std::move(right)}};
	}

}