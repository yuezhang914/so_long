/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:55:02 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/08 02:48:30 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_img(t_game *g, t_img *img, int gx, int gy)
{
	mlx_put_image_to_window(g->mlx, g->win, img->ptr, gx * g->tile, gy
		* g->tile);
}

static void	draw_tile(t_game *g, char c, int gx, int gy)
{
	put_img(g, &g->floor, gx, gy);
	if (c == '1')
		put_img(g, &g->wall, gx, gy);
	else if (c == 'C')
		put_img(g, &g->collect, gx, gy);
	else if (c == 'E')
		put_img(g, &g->exit, gx, gy);
	else if (c == 'P')
		put_img(g, &g->player, gx, gy);
}

void	render_map(t_game *g)
{
	int	x;
	int	y;

	mlx_clear_window(g->mlx, g->win);
	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			draw_tile(g, g->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
