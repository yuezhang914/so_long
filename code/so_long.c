/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:08 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/09 00:04:08 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   so_long.c – program entry point (mandatory)                              */
/* ************************************************************************** */

#include "so_long.h"

/* ───────── 打印用法 ───────── */
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
	/* 1️⃣ 读图 + 校验 */
	if (!load_and_prepare(&g, av[1]))
		perror_exit(&g, "Load / validate map failed");
	/* 2️⃣ 启动图形 */
	g.mlx = mlx_init();
	if (!g.mlx)
		perror_exit(&g, "mlx_init failed");
	g.win = mlx_new_window(g.mlx, g.map_w * TILE, g.map_h * TILE, "so_long");
	if (!g.win)
		perror_exit(&g, "mlx_new_window failed");
	/* 3️⃣ 载图 */
	if (!load_images(&g))
		perror_exit(&g, "load_images failed");
	/* 4️⃣ 首帧 + 事件钩子 */
	render_map(&g);
	setup_hooks(&g);
	/* 5️⃣ 事件循环（ESC 或 X 会在 hooks 里 clean_exit） */
	mlx_loop(g.mlx);
	return (0);
}
