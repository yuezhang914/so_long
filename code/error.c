/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:20 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/09 00:01:55 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ───────── ① 释放所有资源 ───────── */
static void	free_all(t_game *g)
{
	if (g->fd >= 0)
		close(g->fd);
	free_images(g); /* images.c 中实现，空指针安全 */
	free_map(g->map);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

/* ───────── ② 打印错误并退出 ───────── */
void	perror_exit(t_game *g, const char *msg)
{
	ft_printf("Error\n%s\n", msg);
	free_all(g);
	exit(EXIT_FAILURE);
}

/* ───────── ③ 打印警告继续运行 (可选) ───────── */
void	warn_and_continue(const char *msg)
{
	ft_printf("Warning\n%s\n", msg);
}
