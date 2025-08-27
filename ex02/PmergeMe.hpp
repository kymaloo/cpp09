/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:14:12 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/27 19:45:47 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <sstream>
# include <cstdlib>
# include <vector>
# include <deque>
# include <math.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

template <typename T>
class PmergeMe
{
	private:
		std::string			*_input;
		std::stringstream	_before;
		size_t				_inputSize;
		T					_container;
	private:
		void	parse(void);
		void	stockBefore(void);
		void	fillContainer(void);
		void	fordJohnson(T& _cont);
		void	printContainer(T& cont);
		void	insertByJacob(T &cont, T &loser);
	public:
		void start(void);
		PmergeMe(int argc, char **input);
		~PmergeMe(){delete [] _input;};
};
bool isNumber(const std::string &s);
bool checkOverflow(const std::string &s);
size_t	indexForJacobsthal(size_t size);
size_t	nForJacobsthal(size_t n);


template <typename T>
PmergeMe<T>::PmergeMe(int argc, char **input)
{
	int	j;

	j = 1;
	_input = new std::string[argc - 1];
	for (int i = 0; j != argc; i++)
	{
		_input[i] = input[j];
		j++;
	}
	_inputSize = argc - 1;
}

template <typename T>
void	PmergeMe<T>::stockBefore()
{
	_before << "Before: ";
	for (size_t i = 0; i != _inputSize; i++)
	{
		_before << _input[i];
		if (i + 1 != _inputSize)
			_before << " ";
	}
}

template <typename T>
void PmergeMe<T>::parse()
{
	for (size_t i = 0; i != _inputSize; i++)
	{
		if (isNumber(_input[i]) == false)
			throw std::invalid_argument("Error: Not number");
		if (checkOverflow(_input[i]) == false)
			throw std::invalid_argument("Error: The number is too long");
		if (atoi(_input[i].c_str()) < 0)
			throw std::invalid_argument("Error: The number isn't positif");
	}
}

template <typename T>
void PmergeMe<T>::start()
{
	parse();
	stockBefore();
	fillContainer();
	fordJohnson(_container);
	printContainer(_container);
}

template <typename T>
void PmergeMe<T>::fillContainer()
{
	for (size_t i = 0; i != _inputSize; i++)
		_container.push_back(atoi(_input[i].c_str()));
}

template <typename T>
void PmergeMe<T>::fordJohnson(T& cont)
{
    size_t n = cont.size();

	T winner;
	T loser;
	
    if (n <= 1)
        return ;
    for (size_t i = 0; i < n - 1; i += 2)
	{
        if (cont[i] > cont[i + 1])
		{
            winner.push_back(cont[i]);
        	loser.push_back(cont[i + 1]);
        }
		else
		{
            winner.push_back(cont[i + 1]);
            loser.push_back(cont[i]);
        }
    }
    if (n % 2 != 0)
		loser.push_back(cont[n - 1]);
	// std::cout << "\nNo i'm loser\n";
	// printContainer(loser);
	// std::cout << "Let's gooo\n";
	// printContainer(winner);
    fordJohnson(winner);
	cont = winner;
	//indexForJacobsthal(loser.size());
	//nForJacobsthal(5);
	// for (size_t i = 0; i < loser.size(); ++i)
    // {
    //     typename T::iterator it = std::lower_bound(cont.begin(), cont.end(), loser[i]);
    //     cont.insert(it, loser[i]);
    // }
	insertByJacob(cont, loser);
}

template <typename T>
void PmergeMe<T>::printContainer(T& cont)
{
    for (size_t i = 0; i < cont.size(); ++i)
	{
        std::cout << cont[i] << " ";
    }
    std::cout << std::endl;
}

// ! recup index
// ! recup la taille par rapport a l'index
// ! tant que i est diff de l'index
// ! mettre le inieme element dans le winner


// template <typename T>
// void PmergeMe<T>::insertByJacob(T &cont, T &loser)
// {
// 	size_t i;
// 	size_t j;
// 	size_t tmp;

// 	i = 0;
// 	j = indexForJacobsthal(loser.size());
// 	while (i != j)
// 	{
// 		tmp = nForJacobsthal(i);
// 		typename T::iterator it = std::lower_bound(cont.begin(), cont.end(), loser[tmp]);
//         cont.insert(it, loser[tmp]);
// 		i++;
// 	}
// }

template <typename T>
void PmergeMe<T>::insertByJacob(T &cont, T &loser)
{
    std::vector<bool> inserted(loser.size(), false);  // Garder trace des éléments insérés
    size_t i = 0;
    size_t j = indexForJacobsthal(loser.size());
    
    while (i < j && i < loser.size())
    {
        size_t index = nForJacobsthal(i);
        if (index < loser.size() && !inserted[index])
        {
            typename T::iterator it = std::lower_bound(cont.begin(), cont.end(), loser[index]);
            cont.insert(it, loser[index]);
            inserted[index] = true;
        }
        i++;
    }
    for (size_t i = 0; i < loser.size(); i++)
    {
        if (!inserted[i])
        {
            typename T::iterator it = std::lower_bound(cont.begin(), cont.end(), loser[i]);
            cont.insert(it, loser[i]);
        }
    }
}
