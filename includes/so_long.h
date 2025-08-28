/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:54:13 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/28 03:34:49 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

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
	int		view_cols;
	int		view_rows;
	int		cam_x;
	int		cam_y;

	t_pos	player_pos;
	int		collectibles;
	int		collected;
	int		moves;

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
void		load_and_prepare(t_game *g, char *file);
int			load_one(t_game *g, t_img *dst, char *path);
int			load_images(t_game *g);
void		free_images(t_game *g);
void		center_camera_on_player(t_game *g);
void		put_img(t_game *g, t_img *img, int sx, int sy);
void		draw_player_if_allowed(t_game *g, int sx, int sy);
void		render_map(t_game *g);
void		setup_hooks(t_game *g);
int			handle_key(int key, void *param);
void		sl_free_all(t_game *g);
void		perror_exit(t_game *g, const char *msg);
int			clean_exit(void *param);
#endif