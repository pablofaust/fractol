/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:55:11 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 14:19:00 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_env(t_env *env, char *av)
{
	env->param = av;
	env->show_menu = 0;
	env->show_info = 0;
	env->julia_loop = 0;
	env->zoom_enable = 0;
	if (!(set_palettes(env)))
		return (0);
	env->p = 0;
	env->mlx = mlx_init();
	if (!(env->win = mlx_new_window(env->mlx,
					WIDTH_SCREEN, HEIGHT_SCREEN, "Fractol")))
		return (0);
	if (!(env->img = mlx_new_image(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN)))
		return (0);
	if (!(env->data_addr = (unsigned int*)mlx_get_data_addr(env->img,
			&env->bits_per_pixel, &env->bytes_per_line, &env->endian)))
		return (0);
	return (1);
}
