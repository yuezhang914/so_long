/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:41:28 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/08 03:45:30 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	enemy_at(t_bonus *b, int x, int y)
{
	int	i;

	if (!b || b->enemies.count <= 0)
		return (0);
	i = 0;
	while (i < b->enemies.count)
	{
		if (b->enemies.items[i].x == x && b->enemies.items[i].y == y)
			return (1);
		i = i + 1;
	}
	return (0);
}

void	handle_pickup_and_win(t_hookctx *c, int nx, int ny, char tile)
{
	if (tile == 'C')
	{
		c->g->collected++;
		c->g->map[ny][nx] = '0';
	}
	if (tile == 'E' && c->g->collectibles == c->g->collected)
		win_and_quit(c);
}

void	do_move_and_mark(t_hookctx *c, int nx, int ny)
{
	int	px;
	int	py;

	px = c->g->player_pos.x;
	py = c->g->player_pos.y;
	c->g->map[py][px] = '0';
	c->g->map[ny][nx] = 'P';
	c->g->player_pos.x = nx;
	c->g->player_pos.y = ny;
	center_camera_on_player(c->g);
	c->b->hud.dirty = true;
	c->need_redraw = 1;
}
