#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "equal.hpp"
# include "iterator_traits.hpp"


namespace ft
{	
	// [ ITERATOR ]
	template < class U >
	class iterator
	{
		public:

			typedef std::ptrdiff_t							difference_type;
			typedef U										value_type;
			typedef U*										pointer;
			typedef const U*								const_pointer;
			typedef U&										reference;
			typedef const U&								const_reference;
			typedef ft::random_access_iterator_tag			iterator_category;
			typedef iterator< const U >						const_iterator;

			iterator(void)					:	_it()		{};
			iterator(pointer it)			:	_it(it) 	{};
			iterator(const iterator& it)	:	_it(it._it) {};
			~iterator(void)									{};

			pointer			base() const 	{	return  _it;	};

			iterator	operator = (const iterator& r)				{	_it = r.base();	return  *this;		};
			iterator	operator + (difference_type n) const		{	return  iterator(base() + n);		};
			iterator&	operator ++ ()								{	_it += 1;	return  *this;			};
			iterator	operator ++ (int)							{	iterator tmp= *this; _it += 1; return  tmp;	};
			iterator&	operator += (difference_type n)				{	_it += n;	return  *this;			};

			iterator	operator - (difference_type n) const 		{ 	return  iterator(base() - n); 		};
			iterator&	operator -- ()								{	_it -= 1; return  *this;			};
			iterator	operator -- (int)							{	iterator tmp= *this; _it--; return  tmp;	}; // to check
			iterator	operator-=(difference_type n)				{	_it -= n;	return  *this;			};

			reference		operator*() 							{	return  *_it;						};
			const_reference	operator*() const 						{	return  *_it;						};

			pointer			operator->() 							{	return &(operator*());				};
			const_pointer	operator->() const 						{	return &(operator*());				};

			reference		operator[] (difference_type n) 			{	return  base()[n];					};
			const_reference	operator[] (difference_type n) const 	{ 	return  base()[n];					};

			friend bool		operator == (const iterator& l, const iterator& r) 		{	return  l.base() == r.base();	};
			friend bool		operator != (const iterator& l, const iterator& r)		{	return  l.base() != r.base();	};
			friend bool		operator > (const iterator& l, const iterator& r) 		{	return  l.base() > r.base();	};
			friend bool		operator <= (const iterator& l, const iterator& r) 		{	return  l.base() <= r.base();	};
			friend bool		operator < (const iterator& l, const iterator& r) 		{	return  l.base() < r.base();	};
			friend bool 	operator >= (const iterator& l, const iterator& r) 		{	return  l.base() >= r.base();	};

			operator 		const_iterator () const									{	return const_iterator(_it);		};

		private:
			pointer	_it;
	};

/////////////////////////////////////////////////////////////////////////

	// [	NON MEMBER FUNCTIONS	]
	template <class Iter>
	iterator<Iter>	operator + ( typename iterator<Iter>::difference_type n,
										 const iterator<Iter>& it )									{		return  it + n;			};

	template <class Iter1, class Iter2>
	typename iterator<Iter1>::difference_type operator - ( const iterator<Iter1>& l,	
																   const iterator<Iter2>& r )		{		return  l.base() - r.base(); };

	// [	REVERSE ITERATOR	]
	template <class iterator>
	class reverse_iterator
	{
		public:
			
			typedef iterator												iterator_type;
			typedef typename iterator_traits<iterator>::value_type			value_type;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			typedef typename iterator_traits<iterator>::pointer				pointer;
			typedef typename iterator_traits<iterator>::reference			reference;
			typedef std::random_access_iterator_tag							iterator_category;

		private:
			iterator _it;

		public:
			reverse_iterator()										:	_it() 					{};
			reverse_iterator(iterator_type it)						:	_it(it) 				{};
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> & rev_it)	:	_it(rev_it.base()) 		{};

			template <class Iter>
			reverse_iterator&	operator = (const reverse_iterator<Iter>& other)			{		_it = other.base(); return  *this;		};
			~reverse_iterator()																{};

			iterator_type		base() const 												{ 		return _it; 							};

			reverse_iterator	operator + (difference_type n) const 			{ 		return  reverse_iterator(_it - n); 							};
			reverse_iterator&	operator ++ ()									{		--_it;	return  *this;										};
			reverse_iterator	operator ++ (int)								{		reverse_iterator tmp = *this; --_it; return  tmp;			};
			reverse_iterator&	operator += (difference_type n)					{		_it -= n;	return  *this;									};
			reverse_iterator	operator - (difference_type n) const 			{		return  reverse_iterator(_it + n); 							};
			reverse_iterator&	operator -- ()									{		++_it;	return  *this;										};
			reverse_iterator	operator -- (int)								{		reverse_iterator tmp = *this; ++_it; return  tmp;			};
			reverse_iterator	operator -= (difference_type n)					{		_it += n;	return  *this;									};

			reference			operator*() const								{		iterator_type	tmp = _it;	return *(--tmp);				};
			pointer				operator->() const 								{		return &(operator*());										};
			reference			operator[] (difference_type n) const 			{		return  base()[-n - 1];										};

	};

	template <class Iter1, class Iter2>
	bool	operator == ( const iterator<Iter1>& l,
						const iterator<Iter2>& r ) 				{	return  l.base() == r.base();	};

	template <class Iter1, class Iter2>
	bool	operator == ( const reverse_iterator<Iter1>& l,
						const reverse_iterator<Iter2>& r ) 				{	return  l.base() == r.base();	};

	template <class Iter1, class Iter2>
	bool	operator != ( const reverse_iterator<Iter1>& l,
						const reverse_iterator<Iter2>& r )				{	return  l.base() != r.base();	};

	template <class Iter1, class Iter2>
	bool	operator < ( const reverse_iterator<Iter1>& l,
						const reverse_iterator<Iter2>& r ) 				{	return  l.base() > r.base();	};

	template <class Iter1, class Iter2>
	bool	operator <= ( const reverse_iterator<Iter1>& l,
						const reverse_iterator<Iter2>& r ) 				{	return  l.base() >= r.base();	};

	template <class Iter1, class Iter2>
	bool	operator > ( const reverse_iterator<Iter1>& l,
						const reverse_iterator<Iter2>& r ) 				{	return  l.base() < r.base();	};

	template <class Iter1, class Iter2>
	bool 	operator >= ( const reverse_iterator<Iter1>& l,
						const reverse_iterator<Iter2>& r ) 				{	return  l.base() <= r.base();	};

	template <class Iter>
	reverse_iterator<Iter>	operator + ( typename reverse_iterator<Iter>::difference_type n,
										 const reverse_iterator<Iter>& rev_it)								{		return  rev_it + n;			};

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator - ( const reverse_iterator<Iter1>& l,
																   const reverse_iterator<Iter2>& r )		{		return  r.base() - l.base(); };
};

#endif