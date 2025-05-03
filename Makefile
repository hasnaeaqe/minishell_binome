CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS = builtins/built_cd.c builtins/built_echo.c builtins/built_pwd.c builtins/built_env.c builtins/built_exit.c builtins/built_export.c builtins/built_unset.c
OBJS = $(SRCS:.c=.o)
NAME = execute

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): executer.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
