/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:55:04 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/09 00:01:24 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/keysym.h>

#define KEY_ESC XK_Escape
#define KEY_LEFT XK_Left
#define KEY_UP XK_Up
#define KEY_RIGHT XK_Right
#define KEY_DOWN XK_Down
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'

/* ───── ① 键码 → 位移 ───── */
static int	key_to_delta(int key, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (key == KEY_W || key == KEY_UP)
		*dy = -1;
	else if (key == KEY_S || key == KEY_DOWN)
		*dy = 1;
	else if (key == KEY_A || key == KEY_LEFT)
		*dx = -1;
	else if (key == KEY_D || key == KEY_RIGHT)
		*dx = 1;
	else
		return (0);
	return (1);
}

/* ───── ② 尝试移动 ───── */
static void	try_move_player(t_game *g, int dx, int dy)
{
	int		nx;
	int		ny;
	char	tile;

	nx = g->player_pos.x + dx;
	ny = g->player_pos.y + dy;
	tile = g->map[ny][nx];
	if (tile == '1') /* 墙：不可走 */
		return ;
	g->moves++;
	if (tile == 'C')
	{
		g->collected++;
		g->map[ny][nx] = '0'; /* 先吃掉，后面再写成 'P' */
	}
	if (tile == 'E' && g->collectibles == g->collected)
		clean_exit(g, EXIT_SUCCESS); /* 胜利退出 */
	/* 更新地图 & 位置 */
	g->map[g->player_pos.y][g->player_pos.x] = '0';
	g->map[ny][nx] = 'P';
	g->player_pos = (t_pos){nx, ny};
	render_map(g);
}

/* ───── ③ 键盘回调 ───── */
int	handle_key(int key, void *param)
{
	t_game	*g;
	int		dx;
	int		dy;

	g = (t_game *)param;
	if (key == KEY_ESC)
		clean_exit(g, EXIT_SUCCESS);
	if (!key_to_delta(key, &dx, &dy))
		return (0);
	try_move_player(g, dx, dy);
	return (0);
}

/* ───── ④ 注册 hook ───── */
void	setup_hooks(t_game *g)
{
	mlx_hook(g->win, 2, 1L << 0, handle_key, g); /* KeyPress */
	mlx_hook(g->win, 17, 0, clean_exit, g);      /* window X */
}