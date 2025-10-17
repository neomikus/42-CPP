NAME = pmergeme

SRC = main.cpp PmergeMe.cpp PmergeMe.temp.cpp
OBJ = $(SRC:%.cpp=%.o)
CC = c++
RM = rm -f
CPPFLAGS := -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re