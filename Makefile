# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 17:43:16 by yzhang2           #+#    #+#              #
#    Updated: 2025/08/12 15:36:51 by yzhang2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = so_long
CC        = cc
CFLAGS    = -Wall -Wextra -Werror

# 目录
MLX_DIR   = ./minilibx-linux
LIBFT_DIR = libft

# 库文件
LIBFT     = $(LIBFT_DIR)/libft.a
MLX_A     = $(MLX_DIR)/libmlx_Linux.a   # ★ 直接用 Linux 版静态库

# 头文件搜索路径
IFLAGS    = -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

# X11 依赖（Linux）
X11_LIBS  = -lXext -lX11 -lm

# 源文件（mandatory）
SRCS = so_long.c \
       game.c map.c validator.c pathfind.c image.c render.c hooks.c error.c

# 目标文件放 obj/
OBJS = $(addprefix obj/,$(SRCS:.c=.o))

# ========= 目标 =========
all: $(NAME)

# 链接：先对象，再 libft，再 MLX，再 X11
$(NAME): $(LIBFT) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_A) $(X11_LIBS) -no-pie -o $@

# 编译 .c -> obj/*.o
obj/%.o: %.c | obj
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# 生成 obj/ 目录
obj:
	mkdir -p obj

# 先把 libft 和 mlx 编出来
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

# 清理
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf obj

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
