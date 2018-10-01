NAME = expert
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++11
SRC = INode.cpp main.cpp setup.cpp support.cpp output.cpp graph.cpp restart.cpp
OBJ = $(SRC:.cpp=.o)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re:	fclean all
