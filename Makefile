NAME = minishell

MAKEFLAGS = --no-print-directory

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_LIBFT = -I$(LIBFT_DIR)/inc
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

INC_DIR = ./inc
INC = -I$(INC_DIR) -I$(READLINE_PATH)/include

SRC_DIR = src
OBJ_DIR = obj

SRC = main.c $(SRC_DIR)/exec/child_utils.c $(SRC_DIR)/exec/exec_utils.c $(SRC_DIR)/exec/exec_utils2.c \
	  $(SRC_DIR)/exec/execute.c $(SRC_DIR)/exec/redir_utils.c $(SRC_DIR)/exec/redirections.c \
	  $(SRC_DIR)/exec/builtins/cd.c $(SRC_DIR)/exec/builtins/echo.c $(SRC_DIR)/exec/builtins/pwd.c \
	  $(SRC_DIR)/exec/builtins/exit.c $(SRC_DIR)/exec/builtins/export.c $(SRC_DIR)/exec/builtins/export_utils.c \
	  $(SRC_DIR)/exec/builtins/export_sort.c $(SRC_DIR)/exec/builtins/unset.c \
	  $(SRC_DIR)/exec/pipes/child_processes.c $(SRC_DIR)/exec/pipes/heredoc_utils.c $(SRC_DIR)/exec/pipes/heredoc.c \
	  $(SRC_DIR)/exec/pipes/pipe_creation.c $(SRC_DIR)/exec/pipes/pipe_processes.c $(SRC_DIR)/exec/pipes/pipes_utils.c \
	  $(SRC_DIR)/exec/pipes/pipes.c $(SRC_DIR)/pars/expander_handle.c $(SRC_DIR)/pars/expander_tag.c \
	  $(SRC_DIR)/pars/expander_utils.c $(SRC_DIR)/pars/expander.c $(SRC_DIR)/pars/lexer_handle.c \
	  $(SRC_DIR)/pars/lexer_handler.c $(SRC_DIR)/pars/lexer_handler2.c \
	  $(SRC_DIR)/pars/lexer_utils.c $(SRC_DIR)/pars/lexer_utils2.c $(SRC_DIR)/pars/lexer.c $(SRC_DIR)/pars/parse.c \
	  $(SRC_DIR)/pars/parser_utils.c $(SRC_DIR)/pars/parser.c $(SRC_DIR)/pars/read.c $(SRC_DIR)/pars/signal_utils.c \
	  $(SRC_DIR)/pars/signal.c $(SRC_DIR)/utils/cmd_utils.c $(SRC_DIR)/utils/get_value.c $(SRC_DIR)/utils/init_data.c \
	  $(SRC_DIR)/utils/init_data_utils.c $(SRC_DIR)/utils/utils_print.c $(SRC_DIR)/utils/utils.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-gdwarf-4 
LDFLAGS = -lreadline -lhistory
RM = @rm -rf
AR = ar -rcs

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC) $(INC_LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) .shell_history
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
