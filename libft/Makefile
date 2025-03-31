NAME = libft.a

# Directory containing source files
SRC_DIR = src
# Source files
SRC = ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_atoi.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_check_base.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_calloc.c \
			ft_printf.c \
			process_args.c \
			get_next_line.c \
			get_next_line_utils.c \

# Full path to the source files
SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

# Directory where the object files will be stored
OBJ_DIR = obj
# Full path to object files, replacing .c with .o
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Include directory for hedaer files
# - -I flag tells the compiler where to look for header files
# - `includes` contains ft_printf-specific headers
INCLUDES = -Iincludes

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Default rule: Build the library
all: $(NAME)

# Rule to compile source files into object files
# - $< is the first dependency (the source file)
# - $@ is the target (object file)
# - @mkdir -p $(OBJ_DIR)  (Ensure the object directory exists)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@



# Rule to create the library from object files
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Rule to clean object files
clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)

# Rule to clean object files and the library
fclean: clean
	@echo "Cleaning $(NAME)..."
	rm -f $(NAME)

# Rule to clean object files, recompile them, and rebuild the library
re: fclean all

# Prevent make from confusing object files with files of the same name
.PHONY: all clean fclean re