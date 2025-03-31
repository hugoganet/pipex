NAME = pipex

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
LIBFT_DIR	= ./libft

# Compiler & Flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR)/includes

SRC_FILES	= main.c \
			  exec_cmds.c \
			  init.c \
			  parse_cmd.c \
			  utils.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES)) 
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a

# Default rule
all: $(NAME)

# Executable rule
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Libft rule
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Create .o from .c with matching folder structure
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

# Clean everything
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re