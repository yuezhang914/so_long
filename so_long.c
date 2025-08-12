/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:08 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/12 19:09:58 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	print_usage(void)
{
	ft_printf("Error\nUsage: ./so_long <map.ber>\n");
	return (1);
}

int	main(int ac, char **av)
{
	t_game	g;

	if (ac != 2)
		return (print_usage());
	zero_game(&g);
	load_and_prepare(&g, av[1]);
	g.mlx = mlx_init();
	if (!g.mlx)
		perror_exit(&g, "mlx_init failed");
	if (!load_images(&g))
		perror_exit(&g, "load_images failed");
	g.view_cols = 40;
	g.view_rows = 15;
	g.cam_x = 0;
	g.cam_y = 0;
	g.win = mlx_new_window(g.mlx, g.view_cols * g.tile, g.view_rows * g.tile,
			"so_long");
	if (!g.win)
		perror_exit(&g, "mlx_new_window failed");
	center_camera_on_player(&g);
	render_map(&g);
	setup_hooks(&g);
	mlx_loop(g.mlx);
	return (0);
}
