NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUGF = -g3
MLX = -L . -lmlx
GNL = srcs/Get_Next_Line/gnl.a
LIBFT = srcs/libft/libft.a
FRAMEWORKS = -framework OpenGl -framework AppKit

OBJECTS =	srcs/main.o \
	srcs/parse_graphic.o \
	srcs/start_parsing.o \
	srcs/parse_map.o \
	srcs/find_character.o \
	srcs/cub_util.o \
	srcs/cub_util_2.o \
	srcs/dda.o \
	srcs/dda_util.o \
	srcs/draw.o \
	srcs/sprite.o \
	srcs/key_update.o \
	srcs/key_hook.o \
	srcs/handle_list.o \
	srcs/bitmap.o \
	srcs/map_efficiency.o \
	srcs/reset_hub.o \
	srcs/sort.o \

all : gnl libft mlx $(NAME)

gnl :
	cd srcs/Get_Next_Line; $(MAKE)

libft :
	cd srcs/libft; $(MAKE) bonus

mlx :
	cd srcs/mlx; $(MAKE)

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(CFLAGS) $(MLX) $(GNL) $(LIBFT) $(FRAMEWORKS) $(OBJECTS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
