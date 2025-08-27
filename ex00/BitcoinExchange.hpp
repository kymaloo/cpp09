/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:32:23 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/20 13:13:14 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <sstream>
# include <algorithm>

class Btc
{
	private:
		std::map<std::string, std::string>	_mapData;
		float								_numberPostPipe;
		std::string							_strPrePipe;
	private:
		std::string checkLine(std::string str);
		void		stockInput(char *str);
		void 		stockData(void);
		void		printOperator(void);
	public:
		Btc(){};
		Btc(const Btc &cpy){_mapData = cpy._mapData; _numberPostPipe = cpy._numberPostPipe; _strPrePipe = cpy._strPrePipe;};
		Btc &operator=(const Btc &ref){_mapData = ref._mapData; _numberPostPipe = ref._numberPostPipe; _strPrePipe = ref._strPrePipe; return (*this);};
		~Btc(){};
		void start(char *str);
};

#endif