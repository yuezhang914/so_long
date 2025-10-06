/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 03:06:31 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/03 05:27:06 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	lose_and_quit(t_hookctx *c)
{
	write(2, "You lose\n", 9);
	enemies_free(c->b);
	bonus_images_free(c->g, c->b);
	sl_free_all(c->g);
	exit(0);
}

static void	init_game_for_validation(t_game *tmp, char **map)
{
	tmp->mlx = NULL;
	tmp->win = NULL;
	tmp->map = map;
	tmp->map_w = 0;
	tmp->map_h = 0;
	tmp->tile = 0;
	tmp->view_cols = 0;
	tmp->view_rows = 0;
	tmp->cam_x = 0;
	tmp->cam_y = 0;
	tmp->player_pos.x = 0;
	tmp->player_pos.y = 0;
	tmp->collectibles = 0;
	tmp->collected = 0;
	tmp->moves = 0;
	tmp->wall.ptr = NULL;
	tmp->floor.ptr = NULL;
	tmp->player.ptr = NULL;
	tmp->collect.ptr = NULL;
	tmp->exit.ptr = NULL;
	tmp->fd = -1;
}

int	validate_map(char **map)
{
	t_game	tmp;

	init_game_for_validation(&tmp, map);
	if (validator_check_bonus(&tmp))
		return (1);
	else
		return (0);
}

int	calc_view_size(t_game *g, int sw, int sh)
{
	int	want_cols;
	int	want_rows;
	int	cols;
	int	rows;

	(void)sw;
	(void)sh;
	want_cols = 40;
	want_rows = 15;
	if (g->map_w < want_cols)
		cols = g->map_w;
	else
		cols = want_cols;
	if (g->map_h < want_rows)
		rows = g->map_h;
	else
		rows = want_rows;
	g->view_cols = cols;
	g->view_rows = rows;
	g->cam_x = 0;
	g->cam_y = 0;
	return (1);
}

int	create_window_if_needed(t_game *g)
{
	int	ww;
	int	hh;

	ww = g->view_cols * g->tile;
	hh = g->view_rows * g->tile;
	if (g->win == NULL)
	{
		g->win = mlx_new_window(g->mlx, ww, hh, "so_long_bonus");
		if (g->win == NULL)
			perror_exit(g, "mlx_new_window failed");
	}
	return (1);
}
