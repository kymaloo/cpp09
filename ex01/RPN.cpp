/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:05:25 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/15 11:50:03 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(std::string input)
{
	_fullOperation = input;
	if (_fullOperation.find_first_not_of(' ') != false)
		throw std::invalid_argument("Error");
	_size = countWord(_fullOperation);
}

RPN::~RPN()
{
	
}

RPN::RPN(const RPN &cpy)
{
	this->_fullOperation = cpy._fullOperation;
	this->_size = cpy._size;
}

RPN &RPN::operator=(const RPN &cpy)
{
	this->_fullOperation = cpy._fullOperation;
	this->_size = cpy._size;
	return (*this);
}

void RPN::start()
{
	inputInStack();
	reverseStack();
	if (checkOperatorConsecutive() == false)
	{
		std::cerr << "0\n";
		return ;
	}
	algo();
}

void RPN::inputInStack()
{
	std::string *splited;
	int i = 0;
	int	tmp = 0;

	splited = split(_fullOperation, _size);
	while (i < countWord(_fullOperation))
	{
		if (splited[i] != "*" && splited[i] != "/" && splited[i] != "+" && splited[i] != "-")
		{
			if (isdigit(splited[i][0]) == 0)
				return ;
			tmp = atoi(splited[i].c_str());
			if (tmp < 0 || tmp > 9)
				return ;
		}
		_stack.push(splited[i]);
		i++;
	}
	delete []splited;
}

int countWord(std::string str)
{
	std::istringstream myStream(str);
	std::string token;

    size_t pos = -1;
	int count = 0;

    while (myStream >> token)
	{
        while ((pos = token.rfind(',')) != std::string::npos)
            token.erase(pos, 1);
		count++;
	}
	return (count);
}

std::string	*split(std::string str, int size)
{
	std::istringstream myStream(str);
	std::string token;

	std::string *result = new std::string[size];
	int		i = 0;
	size_t pos = -1;

    while (myStream >> token)
	{
        while ((pos = token.rfind(',')) != std::string::npos)
            token.erase(pos, 1);
		result[i] = token;
		i++;
	}
	return (result);
}

void RPN::reverseStack()
{
	std::stack <std::string> tmp;
	
	while (!_stack.empty())
	{
		tmp.push(_stack.top());
		_stack.pop();
	}
	_stack = tmp;
}

bool RPN::algo()
{
	std::string nb;
	std::string nb2;
	int result = 0;
	std::string op;

	nb = _stack.top();
	_stack.pop();
	nb2 = _stack.top();
	_stack.pop();
	op = _stack.top();
	_stack.pop();
	if (isNumber(nb) == false || isNumber(nb2) == false || isOperator(op) == false)
	{
		std::cout << "error\n";
		return (false);
	}
	result = compute(nb, nb2, op);
	_stack.push(to_string(result));
	if (_stack.size() > 2)
		algo();
	else
		std::cout << to_string(result) << std::endl;
	return (true);
}

std::string to_string(const int &value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

bool RPN::isNumber(const std::string& s)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		if (!isdigit(s[i]))
			return (false);
	}
	return (true);
}

bool RPN::isOperator(const std::string& s)
{
	return (s == "+" || s == "-" || s == "*" || s == "/");
}

int RPN::compute(const std::string& a, const std::string& b, const std::string& op)
{
	int n1 = atoi(a.c_str());
	int n2 = atoi(b.c_str());

	if (op == "+")
		return (n1 + n2);
	if (op == "-")
		return (n1 - n2);
	if (op == "*")
		return (n1 * n2);
	if (op == "/")
		return (n1 / n2);
	return (0);
}

bool RPN::checkOperatorConsecutive()
{
	std::stack <std::string> tmp = _stack;
	
	std::string nb;
	std::string nb2;

	while (!tmp.empty() && tmp.size() >= 2)
	{
		nb = tmp.top();
		tmp.pop();
		nb2 = tmp.top();
		tmp.pop();
		if (isOperator(nb) == true && isOperator(nb2) == true)
			return (false);
	}
	return (true);
}
