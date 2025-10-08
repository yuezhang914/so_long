/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:54:36 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/08 03:25:27 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	expose_cb(void *param)
{
	t_hookctx	*c;

	c = (t_hookctx *)param;
	if (!c || !c->g || !c->b)
		return (0);
	render_map(c->g);
	render_bonus_frame(c->g, c->b);
	return (0);
}

static void	perform_redraw(t_hookctx *c)
{
	render_map(c->g);
	render_bonus_frame(c->g, c->b);
	c->need_redraw = 0;
}

static int	loop_cb(void *param)
{
	t_hookctx	*c;

	c = (t_hookctx *)param;
	if (!c || !c->g || !c->b)
		return (0);
	if (c->g->moves != c->last_moves)
	{
		c->last_moves = c->g->moves;
		center_camera_on_player(c->g);
		c->b->hud.dirty = true;
		anim_flip(&c->b->player_anim);
		c->need_redraw = 1;
	}
	if (++c->frame_acc >= BONUS_ENEMY_STEP_TICKS)
	{
		c->frame_acc = 0;
		enemies_step_once(c->g, c->b);
		if (collide_check_lose(c->g, c->b))
			lose_and_quit(c);
		c->b->hud.dirty = true;
		c->need_redraw = 1;
	}
	if (c->need_redraw || c->b->hud.dirty)
		perform_redraw(c);
	return (0);
}

void	*hooks_bonus_install(t_game *g, t_bonus *b)
{
	t_hookctx	*c;

	c = (t_hookctx *)malloc(sizeof(t_hookctx));
	if (!c)
		return (NULL);
	c->frame_acc = 0;
	c->g = g;
	c->b = b;
	c->last_moves = g->moves;
	c->need_redraw = 1;
	mlx_loop_hook(g->mlx, loop_cb, c);
	mlx_expose_hook(g->win, expose_cb, c);
	mlx_hook(g->win, 2, 1L << 0, bonus_handle_key, c);
	return ((void *)c);
}

void	hooks_bonus_free(void *opaque)
{
	t_hookctx	*c;

	c = (t_hookctx *)opaque;
	if (c)
		free(c);
}
