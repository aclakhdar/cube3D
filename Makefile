SRC = main.c game/game_init.c utils/itoa.c game/event_handling.c game/drawing.c \
	game/event_handling2.c \
	game/event_handling3.c \
	game/mouse_exit.c \
	game/utils1.c \
	game/utils2.c \
	game/utils3.c \
	pars_mapvalidation/parse1.c \
	pars_mapvalidation/no_so_we_ea.c \
	pars_mapvalidation/check_map.c \
	pars_mapvalidation/utils1.c \
	pars_mapvalidation/utils2.c \
	pars_mapvalidation/utils3.c \
	utils/get_next_line_utils.c \
    utils/get_next_line.c \
    utils/ft_split.c
FLAGS = #-pg #-Wall -Wextra -Werror
DFLAGS = -MMD -MP
INCLUDES	:= -I./includes -I/usr/local/include
FLAGS += -ggdb
CC = cc
NAME = cub3D
DEPS	:= $(OBJS:.o=.d)
LIBS = -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
all: $(NAME)

-include $(DEPS)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(DFLAGS) $(SRC) $(LIBS)  $(INCLUDES) -o $(NAME)
clean:
	rm -f *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
