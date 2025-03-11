# ================== VARIABLES ==================
# Nom de l'exécutable
NAME = philo.a

# Dossier contenant les fichiers sources
SRC_DIR = sources

# Liste des fichiers source
SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/ft_allocate_memory.c \
	$(SRC_DIR)/ft_free_error.c \
	$(SRC_DIR)/ft_init_vars.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/ft_parsing.c

OBJS =		$(SRCS:.c=.o)

# Compilation
CC		=		gcc
FLAGS	=		-Wall -Werror -Wextra
RM		=		rm -f

# ================== REGLES ==================
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

# Compilation des fichiers .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
		$(CC) $(FLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re