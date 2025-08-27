/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:32:25 by trgaspar          #+#    #+#             */
/*   Updated: 2025/08/20 12:17:35 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void printMap(std::map<std::string, std::string> map)
{
	std::map<std::string, std::string>::iterator it;
	for (it = map.begin(); it != map.end(); it++)
	{
		std::cout << it->first << " => " << it->second << std::endl;
	}
}

void Btc::stockData(void)
{
	std::fstream	fs;
	std::string		line;

	fs.open("data.csv", std::fstream::in);
	getline(fs, line);
	while(getline(fs, line))
		_mapData[line.substr(0, 10)] = line.substr(11, line.size());	
	fs.close();
}

bool checkDateFormat(const std::string& dateString)
{
    char one_char;
    std::stringstream ss(dateString);

    struct tm date;
    struct tm newDate;

    ss >> date.tm_year >> one_char >> date.tm_mon >> one_char >> date.tm_mday;
    date.tm_year -= 1900; 
    date.tm_mon -= 1;
    date.tm_hour = 1;
    date.tm_min = 0;
    date.tm_sec = 0;

    newDate = date;
    mktime(&newDate);
    if (date.tm_year == newDate.tm_year && date.tm_mon == newDate.tm_mon && date.tm_mday == newDate.tm_mday)  
    	return (true);
	else
		return (false);
}

float getNumberPostPipe(std::string str)
{
	std::string::iterator 	it;
	std::string				tmp;
	float					fnb;

	it = find(str.begin(), str.end(), '|');
	it++;
	while (it != str.end())
	{
		tmp.push_back(*it);
		it++;
	}
	fnb = atof(tmp.c_str());
	if (fnb < 0)
		throw std::invalid_argument("error: not positif number");
	if (fnb > 1000)
		throw std::invalid_argument("error: too large a number");
	return (fnb);
}

std::string getDatePrePipe(std::string &str)
{
	std::string::iterator	it;
	std::string				result;
	
	it = str.begin();
	while (*it != '|')
	{
		result.push_back(*it);
		it++;
	}
	return (result);
}

void Btc::printOperator()
{
	std::map<std::string, std::string>::iterator it;

	it = _mapData.lower_bound(_strPrePipe);
	if (it->first != _strPrePipe && it != _mapData.begin())
		it--;
	std::cout << _strPrePipe << " => " << _numberPostPipe << " = " << (atof(it->second.c_str()) * _numberPostPipe) << std::endl;
}

void Btc::stockInput(char *str)
{
	std::fstream						fs;
	std::string							line;

	fs.open(str, std::fstream::in);
	getline(fs, line);
	while(getline(fs, line))
	{
		try
		{
			line = checkLine(line);
			_numberPostPipe = getNumberPostPipe(line);
			_strPrePipe = getDatePrePipe(line);
			if (checkDateFormat(_strPrePipe) == false)
				throw std::invalid_argument("error: date isn't valid");
			printOperator();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	fs.close();
}

void	isPipeInStr(std::string str)
{
	std::string::iterator 	it;

	it = find(str.begin(), str.end(), '|');
	if (it == str.end())
	{
		std::string tmp = "Error : bad input => " + str;
		throw std::invalid_argument(tmp);
	}
}

std::string removeWhiteSpaceInString(std::string str)
{
	std::string::iterator 	it_str;
	std::string				tmp;

	it_str = str.begin();
	while (it_str != str.end())
	{
		if (isspace(*it_str) == 0)
			tmp.push_back(*it_str);
		it_str++;
	}
	return (tmp);
}

bool	isNumber(std::string str)
{
	std::string::iterator	it;
	size_t					count = 0;

	it = find(str.begin(), str.end(), '|');
	it++;
	while (it != str.end())
	{
		if (*it == '.')
			count++;
		else if (isdigit(*it) == 0 || count > 1)
			return (false);
		it++;
	}
	return (true);
}

void checkNumberPostPipe(std::string str)
{
	std::string::iterator 	it;
	std::string				tmp;

	it = str.end() - 1;
	if (*it == '|')
		throw std::invalid_argument("Error : bad input");
	it = find(str.begin(), str.end(), '|');
	it++;
	if (*it == '-')
		throw std::invalid_argument("error: not positif number");
	if (isNumber(str) == false)
		throw std::invalid_argument("Error : bad input");
}

std::string Btc::checkLine(std::string str)
{
	std::string::iterator 	it;
	std::string				oldStr;

	oldStr = str;
	str = removeWhiteSpaceInString(str);
	isPipeInStr(oldStr);
	checkNumberPostPipe(str);
	return (str);
}

void Btc::start(char *str)
{
	stockData();
	stockInput(str);
}
