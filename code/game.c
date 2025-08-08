/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:18 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/08 01:06:33 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	zero_game(t_game *g)
{
	ft_memset(g, 0, sizeof(t_game));
	g->fd = -1;
	g->tile = 32;
}

void	analyse_map(t_game *g)
{
	int	x;
	int	y;

	g->map_h = 0;
	while (g->map[g->map_h])
		g->map_h++;
	g->map_w = (int)ft_strlen(g->map[0]);
	y = -1;
	while (g->map[++y])
	{
		x = -1;
		while (g->map[y][++x])
		{
			if (g->map[y][x] == 'P')
				g->player_pos = (t_pos){x, y};
			else if (g->map[y][x] == 'C')
				g->collectibles++;
		}
	}
}

int	load_and_prepare(t_game *g, char *file)
{
	g->map = load_map(file);
	if (!g->map)
		return (0);
	if (!validate_map(g->map) || !is_path_valid(g->map))
		return (free_map(g->map), 0);
	analyse_map(g);
	return (1);
}

void	clean_exit(t_game *g, int status)
{
	if (g->fd >= 0)
		close(g->fd);
	free_images(g);
	if (g->map)
		free_map(g->map);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	exit(status);
}
