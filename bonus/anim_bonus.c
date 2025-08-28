/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:40:10 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/28 01:06:36 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	anim_init(t_anim *a, void **images, int total)
{
	a->images = images;
	a->total = total;
	if (a->total < 0)
		a->total = 0;
	a->pos = 0;
}

void	anim_flip(t_anim *a)
{
	int	next;

	if (a->total <= 1)
		return ;
	next = a->pos + 1;
	if (next >= a->total)
		next = 0;
	a->pos = next;
}

void	*anim_get_frame(const t_anim *a)
{
	if (!a || !a->images || a->total <= 0)
		return (NULL);
	if (a->pos < 0 || a->pos >= a->total)
		return (a->images[0]);
	return (a->images[a->pos]);
}
