#include <iostream>
#include <map>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>

class BitcoinExchange
{
	public:
		class Date {
			private:
				unsigned int _year;
				unsigned int _month;
				unsigned int _day;
				
			public:
				Date();
				Date(unsigned int year, unsigned int month, unsigned int day);
				Date(std::string &date, char delimiter);
				Date(const BitcoinExchange::Date &model);
				Date	&operator=(const BitcoinExchange::Date &model);
				~Date();

				unsigned int getYear() const;
				unsigned int getMonth() const;
				unsigned int getDay() const;

				bool operator>(const Date &to_compare) const;
				bool operator<(const Date &to_compare) const;
				bool operator>=(const Date &to_compare) const;
				bool operator<=(const Date &to_compare) const;
				bool operator==(const Date &to_compare) const;
				bool operator!=(const Date &to_compare) const;
		};

		BitcoinExchange(std::string filename);
		BitcoinExchange(const BitcoinExchange &model);
		BitcoinExchange	&operator=(const BitcoinExchange &model);
		~BitcoinExchange();

		std::pair<Date, float>	parseValue(const std::string &line);
		void					exchange(std::pair<Date, float> &entry);

	private:
		BitcoinExchange();
		std::map<Date, float>	database;

};
    
std::ostream	&operator<<(std::ostream &stream, const BitcoinExchange::Date &model);