/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 03:32:56 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/07 00:52:45 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_img(t_game *g, t_img *img, int sx, int sy)
{
	mlx_put_image_to_window(g->mlx, g->win, img->ptr, sx * g->tile, sy
		* g->tile);
}

#ifndef BONUS

void	draw_player_if_allowed(t_game *g, int sx, int sy)
{
	put_img(g, &g->player, sx, sy);
}

#else

void	draw_player_if_allowed(t_game *g, int sx, int sy)
{
	(void)g;
	(void)sx;
	(void)sy;
}

#endif

int	flood_pass(char **map, int w, int h)
{
	int	y;
	int	x;
	int	changed;

	changed = 0;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if ((map[y][x] != '1' && map[y][x] != 'V') && ((y > 0 && map[y
						- 1][x] == 'V') || (y + 1 < h && map[y + 1][x] == 'V')
					|| (x > 0 && map[y][x - 1] == 'V') || (x + 1 < w && map[y][x
						+ 1] == 'V')))
			{
				map[y][x] = 'V';
				changed = 1;
			}
			x = x + 1;
		}
		y = y + 1;
	}
	return (changed);
}

void	flood_fill(char **map, int sy, int sx)
{
	int	w;
	int	h;
	int	changed;

	h = 0;
	while (map[h])
		h = h + 1;
	if (h <= 0)
		return ;
	w = (int)ft_strlen(map[0]);
	if (w <= 0)
		return ;
	if (map[sy][sx] != '1' && map[sy][sx] != 'V')
		map[sy][sx] = 'V';
	changed = 1;
	while (changed)
		changed = flood_pass(map, w, h);
}
