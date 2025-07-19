CC = cc 
READLINE_DIR = $(shell brew --prefix readline)

CFLAGS = -Wall -Wextra -Werror -I$(READLINE_DIR)/include #-fsanitize=address -g3
LDFLAGS = -L$(READLINE_DIR)/lib -lreadline
RM = rm -f


PARSE = parsing/expand_0.c parsing/expand_1.c parsing/expand_2.c parsing/expand_3.c parsing/expand_4.c parsing/ft_split.c \
    parsing/garbage_collector.c parsing/libft_1.c parsing/libft_2.c parsing/libft_3.c \
	parsing/parce_tree_0.c parsing/parce_tree_1.c parsing/quotes.c parsing/splite_expand.c   \
	parsing/syntax_errors_0.c parsing/syntax_errors_1.c parsing/tokenisation.c  parsing/signle.c parsing/handel.c\
  execusion/execute_cmd.c execusion/path.c builtins/built_exit.c execusion/libft.c   builtins/for_cd.c  builtins/for_export.c \
  builtins/built_cd.c builtins/built_echo.c builtins/built_pwd.c builtins/built_env.c   builtins/built_export.c builtins/built_unset.c execusion/exec.c execusion/handle_redirs.c  \
	 minishell.c  execusion/check_cmd.c builtins/for_env.c execusion/heredoc.c execusion/for_heredoc.c execusion/execute_pipe.c \

OB = $(PARSE:.c=.o)


NOM = minishell

all: $(NOM) 


$(NOM): $(OB)
	$(CC) $(CFLAGS) $(OB) -o $(NOM) $(LDFLAGS) -lncurses

$(OB): minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)  $(OB) *.d

fclean: clean
	$(RM) $(NOM)

re: fclean all
