# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 17:43:16 by yzhang2           #+#    #+#              #
#    Updated: 2025/08/28 04:16:47 by yzhang2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = so_long
BNAME  = so_long_bonus

CC     = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./minilibx-linux
MLX_A   = $(MLX_DIR)/libmlx_Linux.a
X11_LIBS= -lXext -lX11 -lm

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

IFLAGS  = -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

MSRCS = $(wildcard src/*.c)
BSRCS = $(filter-out src/so_long.c src/validator.c, $(MSRCS)) $(wildcard bonus/*.c)

OBJS  = $(addprefix obj/,$(notdir $(MSRCS:.c=.o)))
BOBJS = $(addprefix obj_bonus/,$(notdir $(BSRCS:.c=.o)))

VPATH = src bonus

all: $(NAME)
bonus: $(BNAME)

$(NAME): $(LIBFT) $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_A) $(X11_LIBS) -o $@

$(BNAME): $(LIBFT) $(MLX_A) $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) $(LIBFT) $(MLX_A) $(X11_LIBS) -o $@

obj/%.o: %.c | obj
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

obj_bonus/%.o: %.c | obj_bonus
	$(CC) $(CFLAGS) $(IFLAGS) -DBONUS=1 -c $< -o $@

obj:
	mkdir -p obj

obj_bonus:
	mkdir -p obj_bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf obj obj_bonus

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: all bonus clean fclean re
