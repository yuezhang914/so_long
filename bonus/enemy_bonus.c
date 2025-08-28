/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:54:30 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/28 03:18:41 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	is_walkable_char(char ch)
{
	if (ch == '0')
		return (1);
	if (ch == 'C')
		return (1);
	if (ch == 'E')
		return (1);
	if (ch == 'N')
		return (1);
	return (0);
}

static t_enemy	enemy_try_move(t_game *g, t_enemy e)
{
	int		nx;
	int		ny;
	char	ch;

	nx = e.x + e.dir;
	ny = e.y;
	if (nx == g->player_pos.x && ny == g->player_pos.y)
	{
		e.x = nx;
		e.y = ny;
		return (e);
	}
	if (nx < 0 || nx >= g->map_w)
	{
		e.dir = -e.dir;
		return (e);
	}
	ch = g->map[ny][nx];
	if (is_walkable_char(ch) == 1)
		e.x = nx;
	else
		e.dir = -e.dir;
	return (e);
}

static void	enemy_step_one(t_game *g, t_bonus *b, int idx)
{
	t_enemy	e;

	e = b->enemies.items[idx];
	e = enemy_try_move(g, e);
	b->enemies.items[idx] = e;
}

void	enemies_step_once(t_game *g, t_bonus *b)
{
	int	i;

	if (b->enemies.count <= 0)
		return ;
	i = 0;
	while (i < b->enemies.count)
	{
		enemy_step_one(g, b, i);
		i = i + 1;
	}
	anim_flip(&b->enemies.anim);
}
