/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:14:12 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/28 18:47:24 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <sstream>
# include <cstdlib>
# include <vector>
# include <deque>
# include <math.h>
# include <ctime>
# include <sys/time.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

template <typename T>
class PmergeMe
{
	private:
		std::string			*_input;
		std::stringstream	_before;
		long double 		_endChrono;
		long double			_startChrono;
		size_t				_inputSize;
		T					_container;
	private:
		void	parse(void);
		void	stockBefore(void);
		void	fillContainer(void);
		void	fordJohnson(T& _cont);
		void	insertByJacob(T &cont, T &loser);
		void	binaryInsert(T& sorted, const int value) ;
	public:
		void printContainer();
		void start(void);
		long double getTime(void);
		std::string getBefore(void);
		T	getContainer(void) const;
		PmergeMe(int argc, char **input);
		~PmergeMe(){delete [] _input;};
		PmergeMe(const PmergeMe &cpy){_before = cpy._before; _endChrono = cpy._endChrono; _startChrono = cpy._startChrono; _container = cpy._container;};
		PmergeMe &operator=(const PmergeMe &ref){_before = ref._before; _endChrono = ref._endChrono; _startChrono = ref._startChrono; _container = ref._container; return (*this);};
};
bool isNumber(const std::string &s);
bool checkOverflow(const std::string &s);
size_t	indexForJacobsthal(size_t size);
size_t	nForJacobsthal(size_t n);

template <typename T>
PmergeMe<T>::PmergeMe(int argc, char **input)
{
	timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	_startChrono = ts.tv_nsec;
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
	size_t tmp = _inputSize;
	_before << "Before: ";
	if (_inputSize > 5)
		tmp = 5;
	for (size_t i = 0; i != tmp; i++)
	{
		_before << _input[i];
		if (i + 1 != _inputSize)
			_before << " ";
	}
	if (_inputSize > 5)
		_before << "[...]";
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
	timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	_endChrono = ts.tv_nsec;
}

template <typename T>
std::string PmergeMe<T>::getBefore()
{
	return (_before.str());
}

template <typename T>
long double PmergeMe<T>::getTime()
{
	return (_endChrono - _startChrono);
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
    fordJohnson(winner);
	cont = winner;
	insertByJacob(cont, loser);
}

template <typename T>
void PmergeMe<T>::printContainer()
{
	size_t tmp = _container.size();
	std::cout << "After:  ";
	if (tmp > 5)
		tmp = 5;
    for (size_t i = 0; i < tmp; ++i)
	{
        std::cout << _container[i] << " ";
    }
	if (_container.size() > 5)
		std::cout << "[...]";
    std::cout << std::endl;
}

template <typename T>
void PmergeMe<T>::insertByJacob(T &cont, T &loser)
{
    std::vector<bool> inserted(loser.size(), false);
    size_t i = 0;
    size_t j = indexForJacobsthal(loser.size());
    
    while (i < j && i < loser.size())
    {
        size_t index = nForJacobsthal(i);
        if (index < loser.size() && !inserted[index])
        {
            binaryInsert(cont, loser[index]);
            inserted[index] = true;
        }
        i++;
    }
    for (size_t i = 0; i < loser.size(); i++)
    {
        if (!inserted[i])
        {
            binaryInsert(cont, loser[i]);
        }
    }
}

template <typename T>
void PmergeMe<T>::binaryInsert(T& sorted, const int value) 
{
    typename T::iterator low = sorted.begin();
    typename T::iterator high = sorted.end();

    while (low != high) 
    {
        typename T::iterator mid = low + (high - low) / 2;
        if (value < *mid)
            high = mid;
        else
            low = mid + 1;
    }
    sorted.insert(low, value);
}
