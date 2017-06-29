#fields ************************** DEFINING COLORS ************************************** #

COLOR_CLEAR		= \033[2K
COLOR_UP		= \033[A
COLOR_NOCOLOR	= \033[0m
COLOR_BOLD		= \033[1m
COLOR_UNDERLINE	= \033[4m
COLOR_BLINKING	= \033[5m
COLOR_BLACK		= \033[1;30m
COLOR_RED		= \033[1;31m
COLOR_GREEN		= \033[1;32m
COLOR_YELLOW	= \033[1;33m
COLOR_BLUE		= \033[1;34m
COLOR_VIOLET	= \033[1;35m
COLOR_CYAN		= \033[1;36m
COLOR_WHITE		= \033[1;37m

# **************************************************************************** #
SRC_FILE =	\
	main.c \
	return_failure.c \
\
	env/environ.c \
	env/load_base_env.c \
	env/add_var.c \
	env/remove_var.c \
	env/t_env.c \
	env/prompt.c \
\
	builtin/cd.c \
	builtin/env.c \
	builtin/setenv.c \
	builtin/unsetenv.c \
	builtin/exit.c \
	builtin/exec_builtin.c \
	builtin/echo.c \
\
	exec/exec_bin.c \
	exec/main_loop.c \
	exec/expand_args.c

NAME ?= minishell

# Defining those variables allows auto completion to occure.
APPEND=
ASAN=
TEST_FILE=

LIB_DIR = libft
LIB_INC = -I$(LIB_DIR)/includes
LOCAL_INC = -Iincludes
SRC_DIR = srcs
OBJ_DIR = objs

ifeq ($(ASAN),yes)
	SANITIZER ?= -fsanitize=address -fno-omit-frame-pointer
endif
OPTIMIZATION ?= -O0
CFLAGS ?= -g -Wall -Wextra -Werror
CC ?= gcc
LDFLAGS = -L$(LIB_DIR) -lft -ltermcap
INCLUDES = $(LOCAL_INC) $(LIB_INC)


SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILE:.c=.c))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_FILE:.c=.o))

.PHONY: all test Hello_word lib $(OBJ_DIR) $(NAME) clean fclean re

all: Hello_word lib $(OBJ_DIR) $(NAME)
	@printf "$(COLOR_CLEAR)$(COLOR_GREEN)Successfully created $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"

Hello_word:
	@printf "$(COLOR_VIOLET)$(COLOR_UNDERLINE)Compiling$(COLOR_NOCOLOR) $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"

lib:
	@make -C $(LIB_DIR) APPEND="$(APPEND)" OPTIMIZATION="$(OPTIMIZATION)" CC="$(CC)"

$(NAME): $(OBJS)
	@printf "$(COLOR_GREEN)Successfully created objects files for binary $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"
	@printf "$(COLOR_VIOLET)Creating $(NAME) ... $(COLOR_NOCOLOR)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LDFLAGS) $(INCLUDES) $(SANITIZER) $(APPEND) $(OPTIMIZATION)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)"
	
$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)/builtin
	@/bin/mkdir -p $(OBJ_DIR)/exec
	@/bin/mkdir -p $(OBJ_DIR)/env
	@/bin/mkdir -p $(OBJ_DIR)/line_editing
	@/bin/mkdir -p $(OBJ_DIR)/completion
	@/bin/mkdir -p $(OBJ_DIR)/history
	@/bin/mkdir -p $(OBJ_DIR)/lexer-parser

clean:
	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@printf "$(COLOR_VIOLET)Creating objects files for library $(COLOR_BLUE)$(NAME) ... \n$(COLOR_CYAN)"
	$(CC) $(OPTIMIZATION) $(CFLAGS) $(INCLUDES) $(SANITIZER) $(APPEND) -c -o $@ $^ 
	@printf "\n$(COLOR_NOCOLOR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)"

test: all 
	@printf "$(COLOR_VIOLET)Compiling test $(TEST_FILE) ... $(COLOR_RESET)\n"
	@$(CC) -g $(TEST_FILE) $(INCLUDES) $(LDFLAGS) $(SANITIZER) $(APPEND)
	@printf "$(COLOR_GREEN)Done !!! Launching $(TEST_FILE) now !!!\n$(COLOR_NOCOLOR)"
	@./a.out
