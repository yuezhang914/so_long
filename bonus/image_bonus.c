/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 04:51:45 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/12 04:59:42 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	sizes_ok(t_game *g, t_bonus *b)
{
	if (b->player2.w != g->tile)
		return (0);
	if (b->player2.h != g->tile)
		return (0);
	if (b->enemy1.w != g->tile || b->enemy1.h != g->tile)
		return (0);
	if (b->enemy2.w != g->tile || b->enemy2.h != g->tile)
		return (0);
	return (1);
}

int	bonus_images_load(t_game *g, t_bonus *b)
{
	int	ok;

	if (!g || !g->mlx)
		return (0);
	ok = load_one(g, &b->player2, "assets/player2.xpm");
	if (ok)
		ok = load_one(g, &b->enemy1, "assets/enemy1.xpm");
	if (ok)
		ok = load_one(g, &b->enemy2, "assets/enemy2.xpm");
	if (ok)
		ok = sizes_ok(g, b);
	if (!ok)
	{
		bonus_images_free(g, b);
		return (0);
	}
	b->player_imgs[0] = g->player.ptr;
	b->player_imgs[1] = b->player2.ptr;
	b->enemy_imgs[0] = b->enemy1.ptr;
	b->enemy_imgs[1] = b->enemy2.ptr;
	anim_init(&b->player_anim, (void **)b->player_imgs, 2);
	anim_init(&b->enemies.anim, (void **)b->enemy_imgs, 2);
	return (1);
}

void	bonus_images_free(t_game *g, t_bonus *b)
{
	if (b->player2.ptr != NULL)
	{
		mlx_destroy_image(g->mlx, b->player2.ptr);
		b->player2.ptr = NULL;
	}
	if (b->enemy1.ptr != NULL)
	{
		mlx_destroy_image(g->mlx, b->enemy1.ptr);
		b->enemy1.ptr = NULL;
	}
	if (b->enemy2.ptr != NULL)
	{
		mlx_destroy_image(g->mlx, b->enemy2.ptr);
		b->enemy2.ptr = NULL;
	}
}
