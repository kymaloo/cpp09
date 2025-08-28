/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:48:36 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/28 17:54:02 by trgaspar         ###   ########.fr       */
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
		long double timeVec;
		long double timeDeq;

		PmergeMe<std::vector<int> > PmVector(argc, argv);
		PmergeMe<std::deque<int> > PmDeque(argc, argv);

		PmVector.start();
		PmDeque.start();
		
		timeVec = PmVector.getTime();
		timeDeq = PmDeque.getTime();

		std::cout << PmVector.getBefore() << std::endl;
		PmVector.printContainer();
		std::cout << "Time to process a range of 5 elements with std::vector : " << timeVec << " us" <<std::endl;
		std::cout << "Time to process a range of 5 elements with std::deque : " << timeDeq << " us" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
