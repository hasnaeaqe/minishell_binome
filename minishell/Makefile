CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f


PARSE = parsing/garbage_collector.c parsing/main.c  parsing/parce_tree.c parsing/syntax_erros.c parsing/test.c parsing/print_tree.c  parsing/my_libft.c \
  parsing/ft_split.c  execusion/execute_cmd.c   execusion/path.c builtins/built_exit.c execusion/libft.c   builtins/for_cd.c  builtins/for_export.c\
  builtins/built_cd.c builtins/built_echo.c builtins/built_pwd.c builtins/built_env.c   builtins/built_export.c builtins/built_unset.c \
 	parsing/ft_itoa.c\
	parsing/expand.c parsing/quotes.c minishell.c execusion/put_err.c execusion/check_cmd.c\

OB = $(PARSE:.c=.o)


NOM = minishell

all: $(NOM) 



$(NOM): $(OB)
	$(CC) $(CFLAGS) $(OB) -o $(NOM) -lreadline

$(OB): minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)  $(OB) *.d

fclean: clean
	$(RM) $(NOM)

re: fclean all
