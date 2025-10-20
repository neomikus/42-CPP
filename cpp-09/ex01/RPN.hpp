#include <iostream>
#include <stack>
#include <stdexcept>
#include <limits>

class RPN
{
	private:
		RPN();
		RPN(const RPN &model);
		RPN	&operator=(const RPN &model);
		~RPN();
	public:
		static double calculate(const std::string &arg);
};
