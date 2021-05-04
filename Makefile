NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX = -L . -lmlx
GNL = srcs/Get_Next_Line/gnl.a
LIBFT = srcs/libft/libft.a
FRAMEWORKS = -framework OpenGl -framework AppKit

OBJECTS =	srcs/cub_util.o \
	srcs/parse_graphic.o \
	srcs/parse_map.o \
	srcs/main.o \
	srcs/start_parsing.o \

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
