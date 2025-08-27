NAME		:= RPN

CXX			:= c++
CXXFLAGS	:= -Wall -Werror -Wextra -std=c++98 -g3

RED		:= \033[31m
YELLOW	:= \033[33m
GREEN	:= \033[32m
BLUE	:= \033[34m
RESET	:= \033[0m

SRCS	:=	main.cpp	\
			RPN.cpp		\
			
OBJS	:= $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $< || (echo "$(BLUE)$(NAME): $(RED) $< Compilation failure$(RESET)" && return 1)

$(NAME): $(OBJS)
	@echo "$(BLUE)$(NAME): Compiling $(OBJS) $(NAME)$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BLUE)$(NAME): $(GREEN)$(NAME) Compiled!$(RESET)"

clear:
	clear

clean:
	@echo "$(BLUE)$(NAME): Cleaning object files$(RESET)"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(BLUE)$(NAME): Cleaning $(NAME)$(RESET)"
	@rm -rf $(NAME)

re: clear fclean all

.PHONY: all clean fclean re clear