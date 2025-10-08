/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:14:59 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/08 03:25:27 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	bonus_key_to_delta(int key, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (key == 'w' || key == XK_Up)
		*dy = -1;
	else if (key == 's' || key == XK_Down)
		*dy = 1;
	else if (key == 'a' || key == XK_Left)
		*dx = -1;
	else if (key == 'd' || key == XK_Right)
		*dx = 1;
	else
		return (0);
	return (1);
}

int	is_blocked_tile(t_game *g, char tile)
{
	if (tile == '1')
		return (1);
	if (tile == 'E' && g->collected < g->collectibles)
		return (1);
	return (0);
}

void	bonus_try_move_player(t_hookctx *c, int dx, int dy)
{
	int		nx;
	int		ny;
	char	tile;

	nx = c->g->player_pos.x + dx;
	ny = c->g->player_pos.y + dy;
	tile = c->g->map[ny][nx];
	if (is_blocked_tile(c->g, tile))
		return ;
	if (enemy_at(c->b, nx, ny))
	{
		lose_and_quit(c);
		return ;
	}
	c->g->moves++;
	ft_printf("Moves: %d\n", c->g->moves);
	handle_pickup_and_win(c, nx, ny, tile);
	do_move_and_mark(c, nx, ny);
}

int	bonus_handle_key(int key, void *param)
{
	t_hookctx	*c;
	int			dx;
	int			dy;

	c = (t_hookctx *)param;
	if (!c || !c->g)
		return (0);
	if (key == XK_Escape)
		lose_and_quit(c);
	if (!bonus_key_to_delta(key, &dx, &dy))
		return (0);
	bonus_try_move_player(c, dx, dy);
	return (0);
}
