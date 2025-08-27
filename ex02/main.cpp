/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:48:36 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/27 19:46:41 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: Minimum one argument pls\n";
		return (1);
	}
	try
	{
		PmergeMe<std::vector<int> > PmVector(argc, argv);
		PmergeMe<std::deque<int> > PmDeque(argc, argv);
		
		PmVector.start();
		PmDeque.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
