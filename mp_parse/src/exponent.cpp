#include "exponent.h"
#include <math.h> 

namespace cs225
{

	double exponent::combine(double right, double left) const
	{
		return pow(right, left);
	}

}