NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX = -L . -lmlx
GNL = Get_Next_Line/gnl.a
LIBFT = Libft/libft.a
FRAMEWORKS = -framework OpenGl -framework AppKit

OBJECTS =	cub_util.o \
	parse_map.o \

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(MLX) $(GNL) $(LIBFT) $(FRAMEWORKS) $(OBJECTS) main.c

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
