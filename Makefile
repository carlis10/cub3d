NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -ldl -lglfw -lm -lpthread -lGL

RM = rm -f

SRCS =  main.c render/draw.c render/input.c render/raycast.c render/textures.c render/draw_text_aux.c \
		parsing/parse_colors.c parsing/parse_identifiers.c parsing/parse_map.c parsing/parse_textures.c parsing/parse.c parsing/val_map.c \
		src_errors/cleanup.c src_errors/error.c src_errors/safe_alloc.c


INCLUDE = -I ./MLX42/include     ./MLX42/build/libmlx42.a include/cub3d.h

OBJTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJTS)
	$(CC) -o $(NAME) $(OBJTS) $(INCLUDE) $(CFLAGS)

clean:
	$(RM) $(OBJTS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJTS)

re: fclean all

.PHONY: all clean fclean re