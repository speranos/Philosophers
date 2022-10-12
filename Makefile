
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c philo_utils.c

all : $(NAME)

$(NAME) : $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo YOUR ARE READY TO GO !!!
clean :
	@rm -rf $(NAME)
	@echo CLEAN !!!
fclean :
	@rm -rf $(NAME)
	@echo RESET ...
re : fclean all