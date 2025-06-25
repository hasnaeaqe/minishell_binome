CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRCS = garbage_collector.c libft.c main.c parce_tree.c  print_tree.c syntax_erros.c expand.c  \
		built_env.c built_export.c quotes.c


OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline  -o $(NAME)

$(OBJS): minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all