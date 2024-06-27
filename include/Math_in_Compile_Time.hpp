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
	static auto constexpr Power_term(T const x, int const k) noexcept-> R
	{
		return 
		(	k == 0 ?	R(1) 
		:	k < 0 ? 1 / Power_term<R>(x, -k)
		:	Power_term<R>(x, k - 1) * x/k
		);
	}


	static auto constexpr Alternated(int const k) noexcept-> int
	{
		return k % 2 == 0 ? 1 : -1;
	}


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Exp(T const x, int const k = 0, R const res = 0) noexcept-> R
	{
		return
		[err = Power_term<R>(x, k), x, k, res]() constexpr-> R
		{
			return
			(	Abs<R>(err) <= std::numeric_limits<R>::epsilon() ? res 
			:	Exp<R>(x, k+1, res + err)
			);
		}();
	}


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Cos(T const x, int const k = 0, R const res = 0) noexcept-> R
	{
		return
		[err = Power_term<R>(x, 2*k), x, k, res]() constexpr-> R
		{
			return
			(	Abs<R>(err) <= std::numeric_limits<R>::epsilon() ? res
			:	Cos<R>( x, k+1, res + err*Alternated(k) )
			);
		}();
	}


	template< class A = BLANK, class T, class R = Real<A, T> >
	static auto constexpr Sin(T const x, int const k = 0, R const res = 0) noexcept-> R
	{
		return
		[err = Power_term<R>(x, 2*k + 1), x, k, res]() constexpr-> R
		{
			return
			(	Abs<R>(err) <= std::numeric_limits<R>::epsilon() ? res
			:	Sin<R>( x, k+1, res + err*Alternated(k) )
			);
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