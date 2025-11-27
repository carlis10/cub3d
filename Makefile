NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -ldl -lglfw -lm -lpthread -lGL

RM = rm -f

SRCS =  main.c render/draw.c render/input.c render/raycast.c render/textures.c render/draw_text_aux.c \
		parsing/parse_colors.c parsing/parse_identifiers.c parsing/parse_map.c parsing/parse_textures.c parsing/parse.c parsing/val_map.c parsing/parse_identifiers_aux.c parsing/val_map_aux.c parsing/read_map.c parsing/load_grid.c parsing/parse_main.c\
		src_errors/error.c \
		libft/get_next_line_bonus.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_calloc.c libft/ft_strncmp.c libft/ft_strrchr.c libft/ft_strjoin.c libft/ft_bzero.c libft/ft_memset.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_putstr_fd.c


INCLUDE = -I ./MLX42/include     ./MLX42/build/libmlx42.a include/cub3d.h

OBJTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJTS)
	@make -C MLX42/build
	$(CC) -o $(NAME) $(OBJTS) $(INCLUDE) $(CFLAGS)

clean:
	@make clean -C MLX42/build
	$(RM) $(OBJTS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJTS)

re: fclean all

.PHONY: all clean fclean re