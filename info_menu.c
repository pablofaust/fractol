/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:47:41 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 18:47:43 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		toggle_first_screen_size(t_env *env)
{
	env->screen[0]->max_x = get_x_max(1, env->show_menu);
	env->screen[0]->width = ft_dim(env->screen[0]->max_x,
			env->screen[0]->min_x);
	get_screen_ratio((double)env->screen[0]->width,
			(double)env->screen[0]->height, env->screen[0]);
}

int			set_menu(t_env *env)
{
	if (env->show_menu)
		env->show_menu = 0;
	else
		env->show_menu = 1;
	toggle_first_screen_size(env);
	if (!(clear_and_redraw(env)))
		return (0);
	return (1);
}

int			toggle_info_menu(t_env *env)
{
	if (env->show_info)
	{
		env->show_info = 0;
		if (!display_screen_one(env))
			return (0);
	}
	else
	{
		env->show_info = 1;
		if (!display_screen_one(env))
			return (0);
	}
	return (1);
}

int			display_info_menu(t_env *env)
{
	char	*iterations;

	if (env->show_info)
	{
		mlx_string_put(env->mlx, env->win, 10, 15, 0xFFFFFF, "Zoom (Z) : ");
		if (env->zoom_enable)
			mlx_string_put(env->mlx, env->win, 120, 15, 0x0ad66f, "Y");
		else
			mlx_string_put(env->mlx, env->win, 120, 15, 0xd60a29, "N");
		mlx_string_put(env->mlx, env->win, 140, 15, 0xFFFFFF, "Loop (L) :");
		if (env->julia_loop)
			mlx_string_put(env->mlx, env->win, 250, 15, 0x0ad66f, "Y");
		else
			mlx_string_put(env->mlx, env->win, 250, 15, 0xd60a29, "N");
		mlx_string_put(env->mlx, env->win, 270, 15, 0xFFFFFF, "Iterations :");
		if (!(iterations = ft_itoa(env->screen[0]->fractal->iteration)))
			return (0);
		mlx_string_put(env->mlx, env->win, 400, 15, 0xFFFFFF, iterations);
		ft_strdel(&iterations);
	}
	return (1);
}
