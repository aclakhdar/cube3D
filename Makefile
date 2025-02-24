SRC = main.c game/game_init.c utils/itoa.c game/event_handling.c game/drawing.c \
	pars_mapvalidation/parse1.c \
	pars_mapvalidation/no_so_we_ea.c \
	pars_mapvalidation/check_map.c \
	utils/get_next_line_utils.c \
    utils/get_next_line.c \
    utils/ft_split.c
FLAGS = -g #-pg #-Wall -Wextra -Werror
CC = cc
NAME = cube

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
clean:
	rm -f *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
