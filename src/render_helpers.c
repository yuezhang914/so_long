/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 03:32:56 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/28 03:33:14 by yzhang2          ###   ########.fr       */
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
