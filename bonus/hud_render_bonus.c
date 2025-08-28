/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_render_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 02:56:40 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/28 20:02:33 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	hud_init(t_game *g, t_bonus *b)
{
	(void)g;
	b->hud.pos_px.x = 8;
	b->hud.pos_px.y = 16;
	b->hud.step_buf[0] = '\0';
	b->hud.dirty = true;
}

void	hud_update(t_game *g, t_bonus *b)
{
	char	*num;

	if (b->hud.dirty == false)
		return ;
	num = ft_itoa(g->moves);
	if (num == NULL)
		return ;
	ft_strlcpy(b->hud.step_buf, "moves: ", sizeof(b->hud.step_buf));
	ft_strlcat(b->hud.step_buf, num, sizeof(b->hud.step_buf));
	free(num);
	b->hud.dirty = false;
}

static void	render_entities(t_game *g, t_bonus *b)
{
	void	*img;
	int		i;
	int		sx;
	int		sy;

	img = anim_get_frame(&b->enemies.anim);
	i = 0;
	while (img && i < b->enemies.count)
	{
		sx = b->enemies.items[i].x - g->cam_x;
		sy = b->enemies.items[i].y - g->cam_y;
		if (sx >= 0 && sy >= 0 && sx < g->view_cols && sy < g->view_rows)
			mlx_put_image_to_window(g->mlx, g->win, img, sx * g->tile, sy
				* g->tile);
		i = i + 1;
	}
	img = anim_get_frame(&b->player_anim);
	if (!img)
		img = g->player.ptr;
	sx = g->player_pos.x - g->cam_x;
	sy = g->player_pos.y - g->cam_y;
	if (img && sx >= 0 && sy >= 0 && sx < g->view_cols && sy < g->view_rows)
		mlx_put_image_to_window(g->mlx, g->win, img, sx * g->tile, sy
			* g->tile);
}

void	render_bonus_frame(t_game *g, t_bonus *b)
{
	render_entities(g, b);
	hud_update(g, b);
	mlx_string_put(g->mlx, g->win, b->hud.pos_px.x, b->hud.pos_px.y, 0x00FFFFFF,
		b->hud.step_buf);
}
