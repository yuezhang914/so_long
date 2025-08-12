/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:55:02 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/12 19:08:56 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_img(t_game *g, t_img *img, int sx, int sy)
{
	mlx_put_image_to_window(g->mlx, g->win, img->ptr, sx * g->tile, sy
		* g->tile);
}

static void	draw_tile(t_game *g, char c, int sx, int sy)
{
	put_img(g, &g->floor, sx, sy);
	if (c == '1')
		put_img(g, &g->wall, sx, sy);
	else if (c == 'C')
		put_img(g, &g->collect, sx, sy);
	else if (c == 'E')
		put_img(g, &g->exit, sx, sy);
	else if (c == 'P')
		put_img(g, &g->player, sx, sy);
}

void	center_camera_on_player(t_game *g)
{
	int	tx;
	int	ty;

	tx = g->player_pos.x - g->view_cols / 2;
	ty = g->player_pos.y - g->view_rows / 2;
	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (g->map_w > g->view_cols && tx > g->map_w - g->view_cols)
		tx = g->map_w - g->view_cols;
	if (g->map_h > g->view_rows && ty > g->map_h - g->view_rows)
		ty = g->map_h - g->view_rows;
	if (g->map_w <= g->view_cols)
		tx = 0;
	if (g->map_h <= g->view_rows)
		ty = 0;
	g->cam_x = tx;
	g->cam_y = ty;
}

void	render_map(t_game *g)
{
	int	sy;
	int	gy;
	int	sx;
	int	gx;

	mlx_clear_window(g->mlx, g->win);
	sy = 0;
	while (sy < g->view_rows)
	{
		gy = g->cam_y + sy;
		if (gy >= 0 && gy < g->map_h)
		{
			sx = 0;
			while (sx < g->view_cols)
			{
				gx = g->cam_x + sx;
				if (gx >= 0 && gx < g->map_w)
					draw_tile(g, g->map[gy][gx], sx, sy);
				sx++;
			}
		}
		sy++;
	}
}
