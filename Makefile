# Nom de l'exécutable
NAME = philo

# Répertoires
SRCDIR = srcs
INCDIR = include

# Fichiers source et objets
SRCS = main.c init.c parsing.c time.c philosophe.c kill.c
OBJ = $(addprefix $(SRCDIR)/, $(SRCS:.c=.o))

# Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I$(INCDIR)

# Règles
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
