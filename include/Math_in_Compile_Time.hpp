#pragma once
#ifndef _PRAC_MATH_IN_COMPILE_TIME_
#define _PRAC_MATH_IN_COMPILE_TIME_


#include <limits>
#include <type_traits>


namespace prac::math
{
	
	enum class BLANK;

	template<class T>
	struct is_BLANK
	{
		static bool constexpr value = std::is_same_v< std::decay_t<T>, BLANK >;
	};

	template<class T>
	static bool constexpr is_BLANK_v = is_BLANK<T>::value;


	template<class A, class Q>
	using Real 
	=	std::conditional_t
		<	is_BLANK_v<A>
		,	std::conditional_t
			<	std::is_floating_point_v<Q>
			,	Q
			,	std::conditional_t
				<	std::is_integral_v<Q>
				,	double
				,	void
				>
			>
		,	A
		>;


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Abs(T const t) noexcept-> R
	{
		return t < 0 ? -t : t;
	}


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Exp(T const x, int k = 0, R const pow_term = 1, R const res = 0) 
	noexcept-> R
	{
		return
		[	=
		,	finish = Abs<R>(pow_term) <= std::numeric_limits<R>::epsilon()
		,	next_term = pow_term*x/(k+1)
		,	next_result = res + pow_term
		]() constexpr-> R
		{
			return finish ? next_result : Exp<R>(x, k+1, next_term, next_result);
		}();
	}


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Cos(T const x, int const k = 0, R const pow_term = 1, R const res = 0) 
	noexcept-> R
	{
		return
		[	=
		,	finish = Abs<R>(pow_term) <= std::numeric_limits<R>::epsilon()
		,	next_term = -pow_term*x*x/( (2*k+2)*(2*k+1) )
		,	next_result = res + pow_term
		]() constexpr-> R
		{
			return finish ? next_result : Cos<R>(x, k+1, next_term, next_result);
		}();
	}


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Sin(T const x, int const k = 0, R const pow_term = 1, R const res = 0) 
	noexcept-> R
	{
		return
		[	=
		,	finish = Abs<R>(pow_term) <= std::numeric_limits<R>::epsilon()
		,	next_term = -pow_term*x*x/( (2*k+3)*(2*k+2) )
		,	next_result = res + pow_term
		]() constexpr-> R
		{
			return finish ? x*next_result : Sin<R>(x, k+1, next_term, next_result);
		}();	
	}


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Tan(T const x) noexcept-> R
	{
		return Sin(x)/Cos(x);
	}

}
//========//========//========//========//=======#//========//========//========//========//=======#


#endif // end of #ifndef _PRAC_MATH_IN_COMPILE_TIME_