#include "BitcoinExchange.hpp"

typedef BitcoinExchange::Date Date;

std::pair<Date, float>  parseValue(const std::string &line) {
    std::string dateStr = line.substr(0, line.find(" |"));
    std::string amountStr = line.substr(line.find("| ") + 1);

    if (dateStr.find("-") == dateStr.find_last_of("-") || dateStr.find("-") == dateStr.npos)
        return (std::make_pair(Date(), -1));

    int year = atoi(dateStr.substr(0, dateStr.find("-")).c_str());
    int month = atoi(dateStr.substr(dateStr.find("-") + 1, dateStr.find_last_of("-") - dateStr.find("-") - 1).c_str());
    int day = atoi(dateStr.substr(dateStr.find_last_of("-") + 1).c_str());

    Date    date;
    try {
        date = Date(year, month, day);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (std::make_pair(Date(), -1));
    }
    
    char *error;
    float   amount = std::strtof(amountStr.c_str(), &error);
    if (error[0] || amount < 0 || amount > 1000) {
        std::cerr << "Error: amount not a positive number" << std::endl;
        return (std::make_pair(Date(), -1));
    }
    return (std::make_pair(date, amount));
}


int	main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "Error: Wrong number of arguments" << std::endl;
		return (ENOENT);
	}

	BitcoinExchange database("data.csv");
	std::ifstream values;

	values.open(argv[1]);

	if (!values.is_open()) {
		std::cerr << "Error: Can't open input file" << std::endl;
		return (ENOENT);
	}

	for (std::string entry; std::getline(values, entry);) {
		std::pair<Date, float> value = parseValue(entry);	
	
		if (value.second != -1)
			database.exchange(value);
	}
	

}