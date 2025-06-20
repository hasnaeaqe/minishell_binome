CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -f


PARSE = parsing/garbage_collector.c parsing/main.c  parsing/parce_tree.c parsing/syntax_erros.c parsing/test.c parsing/print_tree.c  parsing/libft.c \
  parsing/ft_split.c  execute_cmd.c   path.c \
  builtins/built_cd.c builtins/built_echo.c builtins/built_pwd.c builtins/built_env.c libft.c  builtins/built_export.c builtins/built_unset.c 


OB = $(PARSE:.c=.o)


NOM = parse

all: $(NOM) 



$(NOM): $(OB)
	$(CC) $(CFLAGS) $(OB) -o $(NOM) -lreadline

$(OB): parsing/minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)  $(OB) *.d

fclean: clean
	$(RM) $(NOM)

re: fclean all
