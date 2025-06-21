CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f

# SRCS = builtins/built_cd.c builtins/built_echo.c builtins/built_pwd.c builtins/built_env.c \
# 	   builtins/built_exit.c builtins/built_export.c builtins/built_unset.c \
# 	#    utils/libft.c 
# 	#    utils/ft_split.c execusion/main.c execusion/pipe_to_file.c execusion/execute_2cmd.c \
# 	#    utils/ft_malloc.c main.c execute_cmd.c 

PARSE = parsing/garbage_collector.c parsing/main.c  parsing/parce_tree.c parsing/syntax_erros.c parsing/test.c parsing/print_tree.c  parsing/libft.c \
  parsing/ft_split.c  execute_cmd.c  builtins/built_echo.c
#   builtins/built_cd.c builtins/built_echo.c builtins/built_pwd.c 

# OBJS = $(SRCS:.c=.o)
OB = $(PARSE:.c=.o)

# NAME = execute
NOM = parse

all: $(NOM) 
# $(NAME)

# $(NAME): $(OBJS) $(OB)
# 	$(CC) $(CFLAGS) $(OBJS) $(OB) -lreadline -o $(NAME)


$(NOM): $(OB)
	$(CC) $(CFLAGS) $(OB) -o $(NOM) -lreadline

# $(OBJS): executer.h
$(OB): parsing/minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)  $(OB) *.d

fclean: clean
	$(RM) $(NOM)

re: fclean all
