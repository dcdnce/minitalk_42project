SRCS_CLI = client.c
SRCS_SRV = server.c
BONUS_SRCS_CLI = bonus/client_bonus.c
BONUS_SRCS_SRV = bonus/server_bonus.c

OBJS_CLI = $(SRCS_CLI:.c=.o)
OBJS_SRV = $(SRCS_SRV:.c=.o)
BONUS_OBJS_CLI = $(BONUS_SRCS_CLI:.c=.o)
BONUS_OBJS_SRV = $(BONUS_SRCS_SRV:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = Minitalk
NAME_CLI = client
NAME_SRV = server
BONUS_NAME = Minitalk_bonus
BONUS_NAME_CLI = client_bonus
BONUS_NAME_SRV = server_bonus


.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

##################################################################
all : $(NAME_SRV) $(NAME_CLI)

$(NAME_CLI): $(OBJS_CLI)
	$(MAKE) -s -C ./libft
	$(CC) -o $@ $^ -L libft/ -lft
	@echo ">> $(NAME_Y_STRING) make $(NAME_CLI) $(OK_Y_STRING)"

$(NAME_SRV): $(OBJS_SRV)
	$(MAKE) -s -C ./libft
	$(CC) -o $@ $^ -L libft/ -lft
	@echo ">> $(NAME_Y_STRING) make $(NAME_SRV) $(OK_Y_STRING)"

##################################################################
bonus : $(BONUS_NAME_SRV) $(BONUS_NAME_CLI)

$(BONUS_NAME_CLI): $(BONUS_OBJS_CLI)
	$(MAKE) -s -C ./libft
	$(CC) -o $@ $^ -L libft/ -lft
	@echo ">> $(BONUS_NAME_Y_STRING) make $(NAME_CLI) $(OK_Y_STRING)"

$(BONUS_NAME_SRV): $(BONUS_OBJS_SRV)
	$(MAKE) -s -C ./libft
	$(CC) -o $@ $^ -L libft/ -lft
	@echo ">> $(BONUS_NAME_Y_STRING) make $(NAME_SRV) $(OK_Y_STRING)"

##################################################################
clean:
	$(MAKE) clean -s -C ./libft
	rm -f $(OBJS_SRV) $(OBJS_CLI) $(BONUS_OBJS_SRV) $(BONUS_OBJS_CLI)
	@echo ">> $(NAME_Y_STRING) make clean $(OK_Y_STRING)"

fclean: clean
	$(MAKE) fclean -s -C ./libft
	rm -f $(NAME_SRV) $(NAME_CLI) $(BONUS_NAME_SRV) $(BONUS_NAME_CLI)
	@echo ">> $(NAME_Y_STRING) make fclean $(OK_Y_STRING)"

re: fclean all

.PHONY: all clean fclean re



#COLORS
NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m
WARN_COLOR=\033[33;01m
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
OK_Y_STRING=$(WARN_COLOR)[OK]$(NO_COLOR)
NAME_Y_STRING=$(WARN_COLOR)[$(NAME)]$(NO_COLOR)
BONUS_NAME_Y_STRING=$(WARN_COLOR)[$(BONUS_NAME)]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)
