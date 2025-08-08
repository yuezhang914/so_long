/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:54:13 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/09 00:10:50 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img
{
	void	*ptr;
	int		w;
	int		h;
}			t_img;

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

typedef struct s_game
{
	void	*mlx;
	void	*win;

	char	**map;
	int		map_w;
	int		map_h;

	int		tile;

	t_pos	player_pos;
	int		collectibles;
	int		collected;

	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	collect;
	t_img	exit;

	int		fd;
}			t_game;

char		**load_map(char *file);
void		free_map(char **map);
int			validate_map(char **map);
int			is_path_valid(char **map);
void		zero_game(t_game *g);
int			load_and_prepare(t_game *g, char *file);
void		clean_exit(t_game *g, int status);
int			load_images(t_game *g);
void		free_images(t_game *g);
void		render_map(t_game *g);
void		setup_hooks(t_game *g);
int			handle_key(int key, void *param);
void		perror_exit(t_game *g, const char *msg);
void		warn_and_continue(const char *msg);

#endif