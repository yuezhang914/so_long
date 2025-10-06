/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:10 by yzhang2           #+#    #+#             */
/*   Updated: 2025/09/22 15:32:16 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	bonus_zero(t_bonus *b)
{
	b->enemies.items = NULL;
	b->enemies.count = 0;
	b->enemies.w = 0;
	b->enemies.h = 0;
	b->enemies.anim.images = NULL;
	b->enemies.anim.total = 0;
	b->enemies.anim.pos = 0;
	b->hud.step_buf[0] = '\0';
	b->hud.dirty = true;
	b->hud.pos_px.x = BONUS_HUD_MARGIN;
	b->hud.pos_px.y = BONUS_HUD_MARGIN;
	b->lost = 0;
	b->initialized = false;
}

static int	prepare_game_resources(t_game *g, t_bonus *b, const char *path)
{
	zero_game(g);
	bonus_zero(b);
	load_and_prepare(g, (char *)path);
	if (g->mlx == NULL)
		g->mlx = mlx_init();
	if (g->mlx == NULL)
		perror_exit(g, "mlx_init failed");
	if (g->tile <= 0 || g->wall.ptr == NULL)
	{
		if (!load_images(g))
			perror_exit(g, "load_images failed");
	}
	return (1);
}

static int	compute_viewport_and_window(t_game *g)
{
	int	sw;
	int	sh;

	mlx_get_screen_size(g->mlx, &sw, &sh);
	if (sw <= 0 || sh <= 0)
	{
		sw = 1280;
		sh = 720;
	}
	if (!calc_view_size(g, sw, sh))
		return (0);
	if (!create_window_if_needed(g))
		return (0);
	return (1);
}

static int	bonus_init_all(t_game *g, t_bonus *b, const char *path)
{
	if (!prepare_game_resources(g, b, path))
		return (0);
	if (!compute_viewport_and_window(g))
		return (0);
	if (!bonus_images_load(g, b))
		perror_exit(g, "bonus: images load failed");
	if (!enemies_init(g, b))
		perror_exit(g, "bonus: enemies init failed");
	hud_init(g, b);
	center_camera_on_player(g);
	b->initialized = true;
	render_map(g);
	render_bonus_frame(g, b);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	g;
	t_bonus	b;
	void	*hook_ctx;

	if (argc != 2)
	{
		write(2, "Usage: ./so_long_bonus <map.ber>\n", 33);
		return (1);
	}
	if (!bonus_init_all(&g, &b, argv[1]))
		return (1);
	setup_hooks(&g);
	hook_ctx = hooks_bonus_install(&g, &b);
	mlx_loop(g.mlx);
	hooks_bonus_free(hook_ctx);
	enemies_free(&b);
	free_images(&g);
	free_map(g.map);
	return (0);
}
