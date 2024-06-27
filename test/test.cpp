#include "Math_in_Compile_Time.hpp"
#include <cmath>
#include <cassert>


template<class T>
static bool Are_close(T const a, T const b, T const eps = 8*std::numeric_limits<T>::epsilon()) noexcept
{
	return std::abs(a - b) <= eps;
}


int main()
{
	using namespace prac::math;

	{
		auto constexpr 
			exp_n2 = Exp(-2),
			exp_n1 = Exp(-1),
			exp_0 = Exp(0),
			exp_1 = Exp(1),
			exp_2 = Exp(2);

		assert
		(	::Are_close( exp_n2, std::exp(-2) ) 
		&&	::Are_close( exp_n1, std::exp(-1) )
		&&	::Are_close( exp_0, std::exp(0) )
		&&	::Are_close( exp_1, std::exp(1) )
		&&	::Are_close( exp_2, std::exp(2) )
		);
	}
	{
		auto constexpr 
			cos_n2 = Cos(-2),
			cos_n1 = Cos(-1),
			cos_0 = Cos(0),
			cos_1 = Cos(1),
			cos_2 = Cos(2);		
		
		assert
		(	::Are_close( cos_n2, std::cos(-2) ) 
		&&	::Are_close( cos_n1, std::cos(-1) )
		&&	::Are_close( cos_0, std::cos(0) )
		&&	::Are_close( cos_1, std::cos(1) )
		&&	::Are_close( cos_2, std::cos(2) )
		);
	}
	{
		auto constexpr 
			sin_n2 = Sin(-2),
			sin_n1 = Sin(-1),
			sin_0 = Sin(0),
			sin_1 = Sin(1),
			sin_2 = Sin(2);		
		
		assert
		(	::Are_close( sin_n2, std::sin(-2) ) 
		&&	::Are_close( sin_n1, std::sin(-1) )
		&&	::Are_close( sin_0, std::sin(0) )
		&&	::Are_close( sin_1, std::sin(1) )
		&&	::Are_close( sin_2, std::sin(2) )
		);
	}
	{
		auto constexpr 
			tan_n2 = Tan(-2),
			tan_n1 = Tan(-1),
			tan_0 = Tan(0),
			tan_1 = Tan(1),
			tan_2 = Tan(2);		
		
		assert
		(	::Are_close( tan_n2, std::tan(-2) ) 
		&&	::Are_close( tan_n1, std::tan(-1) )
		&&	::Are_close( tan_0, std::tan(0) )
		&&	::Are_close( tan_1, std::tan(1) )
		&&	::Are_close( tan_2, std::tan(2) )
		);
	}


	return 0;
}