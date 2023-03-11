NAME = CUB3D

.PHONY: all, clean, fclean, re

SRCS = cub3d.c \
		parsing/init.c parsing/path.c parsing/verif_para.c parsing/verif_map.c parsing/parsing.c parsing/create_map.c parsing/direction_j.c \
		outils/outils.c outils/outils2.c outils/ft_split.c outils/ft_split_s.c outils/outils3.c \
		free/free.c \
		mini_map/draw_mini_map.c mini_map/size_mini_map.c \
		raycasting/move.c raycasting/calcul_rc_h.c raycasting/calcul_rc_v.c raycasting/utils_rc.c

OBJS = $(SRCS:.c=.o)

CC = gcc

LFLAGS	=	-I. -Lmlx -lmlx -framework OpenGL -framework Appkit -g -fsanitize=address

# CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(SRCS)
		$(CC) $(CFLAGS) $(LFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all