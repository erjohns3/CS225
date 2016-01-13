#include "unary_op.h"
#include "uplus.h"
#include "uminus.h"

namespace cs225
{

	unary_op::unary_op(std::unique_ptr<node> arg)
	{
		arg_.swap(arg);
	}

	double unary_op::value() const
	{
		return compute(arg_->value());
	}

	std::unique_ptr<node> make_unary_op(const std::string& op, std::unique_ptr<node> arg)
	{
		if(op.compare("#") == 0)
			return std::unique_ptr<node> {new uplus{std::move(arg)}};
		else if(op.compare("~") == 0)
			return std::unique_ptr<node> {new uminus{std::move(arg)}};
	}

}