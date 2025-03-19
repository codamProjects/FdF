
CC= gcc
CFLAGS= -Wall -Wextra -Werror

ifeq ($(shell uname), Darwin)
	LFLAGS= -Iinclude -lglfw -L"/Users/jvorstma/.brew/opt/glfw/lib/"
	IFLAGS= -framework Cocoa -framework OpenGL -framework IOKit
else
	LFLAGS= -Iinclude -L/usr/lib/x86_64-linux-gnu -lglfw -ldl -lm -pthread 
endif

HEADER= fdf.h
RM= rm -f

NAME= fdf

MLX42_DIR= ./include/MLX42
MLX42_B = $(MLX42_DIR)/build
MLX42= $(MLX42_B)/libmlx42.a
LIBFT= libft/libft.a

ODIR= obj

SOURCE= main.c \
		ft_map.c \
		ft_color.c \
		ft_modify.c \
		ft_draw.c \
		ft_error_free.c \

OBJECT= $(addprefix $(ODIR)/,$(SOURCE:.c=.o))

all: libft $(MLX42) $(NAME)

# git_submodule_update:
# 	@git submodule deinit -f libft
# 	rm -rf .git/modules/libft
# 	@git submodule update --init --recursive

libft: #git_submodule_update
	@make -sC ./libft

$(MLX42):
	@if [ ! -d "$(MLX42_DIR)" ]; then \
	   	git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	@cmake $(MLX42_DIR) -B $(MLX42_B) > /dev/null
	@make -sC $(MLX42_B) -j4 > /dev/null

$(NAME): $(OBJECT) $(MLX42) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) $^ $(MLX42) -o $@ $(LFLAGS) -L./libft -lft

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o: %.c $(HEADER)| $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if [ -d "$(MLX42-B)" ]; then \
		@make clean -sC $(MLX42_B) -j4; \
	fi
	@make clean -sC ./libft
	@$(RM) -r $(ODIR)

fclean: clean
	@if [ -d "$(MLX24_B)" ]; then \
		$(RM) -r $(MLX42_B); \
	fi
	@make fclean -sC ./libft
	@$(RM) $(NAME)

re: fclean all

delmlx: fclean
	@if [ -d "$(MLX42_DIR)" ]; then \
		$(RM) -r $(MLX42_DIR);
	fi

.PHONY: all clean fclean re libft delmlx
