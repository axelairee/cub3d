NAME			=   cub3D

SRCS			=   parsing/check_map.c \
					parsing/fill_struct.c \
					parsing/ft_split.c \
					parsing/main.c \
					parsing/utils.c \
					parsing/flood_fill.c \
					parsing/extract_rgb.c \
					parsing/fill_map_utils.c \
					parsing/libft.c \
					parsing/get_next_line.c \
					parsing/get_next_line_utils.c \
					parsing/path.c \
					exec/exec_main.c \
					exec/raycasting.c \
					exec/texture.c \
					exec/move.c \
					exec/manage_keys.c \
					exec/utils.c \
					exec/cam.c \
					exec/draw.c \
					exec/init.c \
					exec/free_all.c

OBJS			=	$(addprefix .build/, $(SRCS:.c=.o))

HEAD			=	-I includes

CC				=   gcc

CFLAGS			=	-Wall -Werror -Wextra

MLX_FILE		=	minilibx-linux/libmlx.a

MLX_FLAG		=	-Iminilibx-linux -Lminilibx-linux -lmlx -lX11 -lXext -lm


.build/%.o: %.c includes/cub3d.h
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

$(NAME): $(OBJS)
				@echo "\033[0;33m\nCOMPILATION DE CUB3D...\n"
				make -sC minilibx-linux
				$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAG) -o $(NAME)
				@echo "\033[1;32mCUB3D créé\n"

all: $(NAME)

clean:
				@rm -rf $(OBJS)
				@rm -rf .build

fclean: clean
				@echo "\033[1;32mNETTOYÉ !\n"
				@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
