/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:26:04 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 16:39:13 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		clear_image(t_env *env)
{
	int		i;

	i = 0;
	while (i < HEIGHT_SCREEN * WIDTH_SCREEN)
	{
		if (env->data_addr[i] != 0)
			env->data_addr[i] = 0;
		i++;
	}
}

void		clear_zone(int zone, t_env *env)
{
	t_screen	*scr;
	int			x;
	int			y;

	scr = env->screen[zone - 1];
	y = scr->min_y;
	while (y < scr->max_y)
	{
		x = scr->min_x;
		while (x < scr->max_x)
		{
			if (env->data_addr[y * WIDTH_SCREEN + x] != 0)
				env->data_addr[y * WIDTH_SCREEN + x] = 0;
			x++;
		}
		y++;
	}
}

int			clear_and_redraw(t_env *env)
{
	clear_image(env);
	if (!(display_fractals(env)))
		return (0);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (1);
}
