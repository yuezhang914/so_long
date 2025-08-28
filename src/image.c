/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:05:58 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/18 02:10:17 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_one(t_game *g, t_img *dst, char *path)
{
	dst->ptr = mlx_xpm_file_to_image(g->mlx, path, &dst->w, &dst->h);
	if (!dst->ptr)
		return (0);
	return (1);
}

static void	destroy_one(t_game *g, t_img *src)
{
	if (src->ptr)
	{
		mlx_destroy_image(g->mlx, src->ptr);
		src->ptr = NULL;
	}
}

void	free_images(t_game *g)
{
	destroy_one(g, &g->wall);
	destroy_one(g, &g->floor);
	destroy_one(g, &g->player);
	destroy_one(g, &g->collect);
	destroy_one(g, &g->exit);
}

int	load_images(t_game *g)
{
	if (!load_one(g, &g->wall, "assets/wall.xpm"))
		return (0);
	if (!load_one(g, &g->floor, "assets/floor.xpm"))
		return (free_images(g), 0);
	if (!load_one(g, &g->player, "assets/player1.xpm"))
		return (free_images(g), 0);
	if (!load_one(g, &g->collect, "assets/collect.xpm"))
		return (free_images(g), 0);
	if (!load_one(g, &g->exit, "assets/exit.xpm"))
		return (free_images(g), 0);
	if (g->wall.w != g->floor.w || g->wall.h != g->floor.h
		|| g->player.w != g->wall.w || g->player.h != g->wall.h
		|| g->collect.w != g->wall.w || g->collect.h != g->wall.h
		|| g->exit.w != g->wall.w || g->exit.h != g->wall.h)
		return (free_images(g), 0);
	g->tile = g->wall.w;
	return (1);
}
