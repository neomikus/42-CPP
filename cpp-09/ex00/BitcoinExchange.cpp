#include "BitcoinExchange.hpp"

typedef BitcoinExchange::Date Date;

BitcoinExchange::BitcoinExchange() {

};

std::pair<Date, float>  BitcoinExchange::parseValue(const std::string &line) {
    std::string dateStr = line.substr(0, line.find(","));
    std::string valueStr = line.substr(line.find(",") + 1);

    if (dateStr.find("-") == dateStr.find_last_of("-") || dateStr.find("-") == dateStr.npos) {
        std::cerr << "Error on CSV date: not a date" << std::endl;
        return (std::make_pair(Date(), -1));
    }

    int year = atoi(dateStr.substr(0, dateStr.find("-")).c_str());
    int month = atoi(dateStr.substr(dateStr.find("-") + 1, dateStr.find_last_of("-") - dateStr.find("-") - 1).c_str());
    int day = atoi(dateStr.substr(dateStr.find_last_of("-") + 1).c_str());

    Date    date;
    try {
        date = Date(year, month, day);
    } catch (std::exception &e) {
        std::cerr << "Error on CSV date: " << e.what() << std::endl;
        return (std::make_pair(Date(), -1));
    }
    
    char *error;
    float   value = std::strtof(valueStr.c_str(), &error);
    if (error[0] || value < 0) {
        std::cerr << "Error on CSV value: Value not a number or outside of range" << std::endl;
        return (std::make_pair(Date(), -1));
    }
    return (std::make_pair(date, value));
}

BitcoinExchange::BitcoinExchange(std::string filename) {
    std::ifstream databaseFile;

    databaseFile.open(filename);

    if (!databaseFile.is_open()) {
        std::cout << "Can't open CSV database" << std::endl;
        return;
    }

    for (std::string line; std::getline(databaseFile, line);) {
        std::pair<Date, float> parsed = parseValue(line);

        if (parsed.second != -1)
            database.insert(parsed);
    }

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &model) {
    for (std::map<Date, float>::const_iterator it = model.database.begin();
        it != model.database.end(); it++) {
            database.insert(*it);
        }
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &model) {
    for (std::map<Date, float>::const_iterator it = model.database.begin();
        it != model.database.end(); it++) {
            database.insert(*it);
        }
    return (*this); 
}

BitcoinExchange::~BitcoinExchange() {

}

void    BitcoinExchange::exchange(std::pair<Date, float> &entry) {
    std::map<Date, float>::iterator current = database.find(entry.first);

    if (current == database.end()) {
        current = --database.lower_bound(entry.first);
    }
    std::cout << "You have: $" << entry.second * current->second << " on " << entry.first << std::endl;
}

/* DATE CLASS */

BitcoinExchange::Date::Date() {
	_year = 1970;
	_month = 1;
	_day = 1;
}

BitcoinExchange::Date::Date(unsigned int year, unsigned int month, unsigned int day) {
    if (!year)
        throw std::out_of_range("Year not valid");
	_year = year;
	if (!month || month > 12)
		throw std::out_of_range("Month not valid");
	_month = month;
	if (day > 31 || (day > 30 && (month == 4 || month == 9 || month == 11)) || (day > 29 && month == 2))
		throw std::out_of_range("Day not valid");
	if (day > 28 && month == 2 && (year % 4 || (year % 100 && !year % 400)))
		throw std::out_of_range("Not leap year");
	_day = day;
}

long	checkLValue(const std::string &str) {
	char *endptr;
	long	retval = strtol(str.c_str(), &endptr, 10);
	if (endptr == str.c_str())
		throw (std::runtime_error("Not a number"));
	if (*endptr != '\0')
		throw (std::runtime_error("Not a number"));
	return (retval);
}


BitcoinExchange::Date::Date(std::string &date, char delimiter) {
	size_t i = 0;
	
	for (size_t pos = 0; pos != date.npos;)
	{
		try {
			std::cout << date.substr(pos, date.find(pos, delimiter)) << std::endl;
			switch (i) {
				case 0:
					_year = checkLValue(date.substr(pos, date.find(pos, delimiter)));
					break;
				case 1:
					_month = checkLValue(date.substr(pos, date.find(delimiter, pos)));
					break;
				case 2:
					_day = checkLValue(date.substr(pos, date.size()));
					break;
			}
		} catch(const std::exception& e) {
			throw (std::runtime_error("Wrong Date"));
		}
		pos = date.find(delimiter) + 1;
		i++;
	}
}

BitcoinExchange::Date::Date(const BitcoinExchange::Date &model) {
	_year = model._year;
	_month = model._month;
	_day = model._day;
}

BitcoinExchange::Date	&BitcoinExchange::Date::operator=(const BitcoinExchange::Date &model) {
	_year = model._year;
	_month = model._month;
	_day = model._day;
	return (*this);
}

BitcoinExchange::Date::~Date() {

}

unsigned int BitcoinExchange::Date::getYear() const {
	return (_year);
}

unsigned int BitcoinExchange::Date::getMonth() const {
	return (_month);
}

unsigned int BitcoinExchange::Date::getDay() const {
	return (_day);
}

bool	BitcoinExchange::Date::operator>(const Date &to_compare) const {
	if (_year > to_compare._year)
		return (true);
	if (_year == to_compare._year) {
		if (_month > to_compare._month)
			return (true);
		if (_month == to_compare._month) {	
			if (_day > to_compare._day)
				return (true);
		}
	}
	return (false);
}

bool	BitcoinExchange::Date::operator<(const Date &to_compare) const {
	if (_year > to_compare._year)
		return (false);
	if (_year == to_compare._year) {
		if (_month > to_compare._month)
			return (false);
		if (_month == to_compare._month) {	
			if (_day >= to_compare._day)
				return (false);
		}
	}
	return (true);
}

bool	BitcoinExchange::Date::operator>=(const Date &to_compare) const {
	if (_year > to_compare._year)
		return (true);
	if (_year == to_compare._year) {
		if (_month > to_compare._month)
			return (true);
		if (_month == to_compare._month) {	
			if (_day >= to_compare._day)
				return (true);
		}
	}
	return (false);
}

bool	BitcoinExchange::Date::operator<=(const Date &to_compare) const {
	if (_year > to_compare._year)
		return (false);
	if (_year == to_compare._year) {
		if (_month > to_compare._month)
			return (false);
		if (_month == to_compare._month) {	
			if (_day > to_compare._day)
				return (false);
		}
	}
	return (true);
}

bool	BitcoinExchange::Date::operator==(const Date &to_compare) const {
	return ((_year == to_compare._year && _month == to_compare._month && 
			_day == to_compare._day));
}

bool	BitcoinExchange::Date::operator!=(const Date &to_compare) const {
	return (!(_year == to_compare._year && _month == to_compare._month && 
			_day == to_compare._day));
}

std::ostream	&operator<<(std::ostream &stream, const BitcoinExchange::Date &model) {
	stream << model.getYear() << "/" << model.getMonth() << "/" << model.getDay();
	return (stream);
}