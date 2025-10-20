#include "RPN.hpp"

static bool istoken(char c) {
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return (true);
	return (false);
}

double RPN::calculate(const std::string &arg) {
	std::stack<double>	stack;

	for (size_t i = 0; arg[i]; i++)
	{
		if (isspace(arg[i]))
			continue;
		if (isdigit(arg[i]))
			stack.push(arg[i] - 48);
		else if (istoken(arg[i])) {
			if (stack.size() < 2) {
				std::cerr << "Too many operators" << std::endl;
				return(std::numeric_limits<double>::quiet_NaN());
			}
			double second = stack.top();
			stack.pop();
			switch (arg[i])
			{
				case '+':
					stack.top() = stack.top() + second;
					break;
				case '-':
					stack.top() = stack.top() - second;
					break;
				case '*':
					stack.top() = stack.top() * second;
					break;
				case '/':
					if (!second) {
						std::cerr << "Division by zero" << std::endl;
						return(std::numeric_limits<double>::quiet_NaN());
					}
					stack.top() = stack.top() / second;
					break;
				default:
					break;
			}
		}
		else {
			throw(std::runtime_error("Not a number nor operation"));
		}
	}
	if (stack.size() > 1) {
		std::cerr << "Too many numbers" << std::endl;
		return(std::numeric_limits<double>::quiet_NaN());
	}
	return (stack.top());
}

RPN::RPN(const RPN &model) {
	(void)model;	
}

RPN	&RPN::operator=(const RPN &model) {
	(void)model;
	return (*this);
}

RPN::~RPN() {

}