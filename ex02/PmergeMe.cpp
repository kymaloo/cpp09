/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:39:22 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/27 19:42:34 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool isNumber(const std::string &s)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		if (!isdigit(s[i]))
			return (false);
	}
	return (true);
}

bool checkOverflow(const std::string &s)
{
	long nb;

	nb = atol(s.c_str());
	if (nb > INT_MAX || nb < INT_MIN)
		return (false);
	return (true);
}

size_t	indexForJacobsthal(size_t size)
{
	size_t j0 = 0;
	size_t j1 = 1;
	size_t i = 1;

	size_t jn = 0;

	while (jn <= size)
	{
		jn = j1 + (2 * j0);
		j0 = j1;
		j1 = jn;
		i++;
	}
	//std::cout << i << std::endl;
	return (i);
}

size_t	nForJacobsthal(size_t n)
{
	size_t jn = (pow(2, n) - pow(-1, n)) / 3;
	
	//std::cout << jn << std::endl;
	return (jn);
}
