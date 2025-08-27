/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:05:20 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/19 15:12:14 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#pragma once

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <sstream>
# include <stack>
# include <cstdlib>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

class RPN
{
	private:
		std::string _fullOperation;
		int			_size;
		std::stack	<std::string> _stack;
	private:
		void		inputInStack(void);
		void		reverseStack(void);
		bool		algo(void);
		bool 		isNumber(const std::string& s);
		bool		isOperator(const std::string& s);
		int			compute(const std::string& a, const std::string& b, const std::string& op);
		bool		checkOperatorConsecutive(void);
	public:
		RPN(std::string input);
		~RPN();
		RPN(const RPN &cpy);
		RPN &operator=(const RPN &cpy);
		void start(void);
};
std::string *split(std::string, int size);
int countWord(std::string str);
std::string to_string(const int &value);
#endif