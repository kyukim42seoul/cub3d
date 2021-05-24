NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(DEBUGF) -fsanitize=address
DEBUGF = -g3
MLX = -L . -lmlx
GNL = srcs/Get_Next_Line/gnl.a
LIBFT = srcs/libft/libft.a
FRAMEWORKS = -framework OpenGl -framework AppKit

OBJECTS =	srcs/main.o \
	srcs/parse_graphic.o \
	srcs/parse_map.o \
	srcs/start_parsing.o \
	srcs/cub_util.o \
	srcs/dda.o \
	srcs/draw.o \
	srcs/sprite.o \
	srcs/key.o \
	srcs/handle_list.o \

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
