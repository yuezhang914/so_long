# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 17:43:16 by yzhang2           #+#    #+#              #
#    Updated: 2025/08/28 00:29:10 by yzhang2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME   = so_long
BNAME  = so_long_bonus

CC     = cc
CFLAGS = -Wall -Wextra -Werror
# 调试时可打开：
# CFLAGS += -g -fsanitize=address

MLX_DIR = ./minilibx-linux
MLX_A   = $(MLX_DIR)/libmlx_Linux.a
X11_LIBS= -lXext -lX11 -lm

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

IFLAGS  = -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

# ========= 源文件 =========
# Mandatory：src 下所有 .c
MSRCS = $(wildcard src/*.c)

# Bonus：src 下所有 .c + bonus 下所有 .c
# 但为避免两个 main 冲突，排除 src/so_long.c
BSRCS = $(filter-out src/so_long.c src/validator.c, $(MSRCS)) $(wildcard bonus/*.c)

# ========= 目标文件 =========
OBJS  = $(addprefix obj/,$(notdir $(MSRCS:.c=.o)))
BOBJS = $(addprefix obj_bonus/,$(notdir $(BSRCS:.c=.o)))

# 让模式规则能在 src/ 与 bonus/ 找到源文件
VPATH = src bonus

# =========================
# 目标
# =========================
all: $(NAME)
bonus: $(BNAME)

$(NAME): $(LIBFT) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_A) $(X11_LIBS) -o $@

$(BNAME): $(LIBFT) $(MLX_A) $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) $(LIBFT) $(MLX_A) $(X11_LIBS) -o $@

# =========================
# 编译规则
# =========================
obj/%.o: %.c | obj
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

obj_bonus/%.o: %.c | obj_bonus
	$(CC) $(CFLAGS) $(IFLAGS) -DBONUS=1 -c $< -o $@

obj:
	mkdir -p obj

obj_bonus:
	mkdir -p obj_bonus

# =========================
# 第三方库
# =========================
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

# =========================
# 清理
# =========================
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf obj obj_bonus

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: all bonus clean fclean re
