NAME = philo
CFLAGS = -Wall -Werror -Wextra -g
CC = cc
#UTILS_DIR = ./utils
#CORE_DIR = ./core
PRINTF_DIR = ./ft_printf
#ERRORS_DIR = ./errors
MAIN = main.c
COMMON_SRC = $(wildcard ./*c $(PRINTF_DIR)/*.c) # Expands to all .c files in directories
OBJ = $(COMMON_SRC:.c=.o) #$(MAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)

	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Program is ready!!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Object files have been cleaned successfully"

fclean: clean
	@rm -f $(NAME)
	@echo "Objects and executables removed"

re: fclean all