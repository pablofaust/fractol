/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:30:59 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 19:00:54 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	set_julia_loop(t_env *env)
{
	if (env->julia_loop)
		env->julia_loop = 0;
	else
		env->julia_loop = 1;
	if (env->zoom_enable)
		env->zoom_enable = 0;
	if (env->show_info)
		if (!(display_screen_one(env)))
			return (0);
	return (1);
}

static int	enable_zoom(t_env *env)
{
	if (env->zoom_enable)
		env->zoom_enable = 0;
	else
		env->zoom_enable = 1;
	if (env->julia_loop)
		env->julia_loop = 0;
	if (env->show_info)
		if (!(display_screen_one(env)))
			return (0);
	return (1);
}

static int	change_palette(t_env *env, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		if (env->p == 0)
			env->p = 4;
		else
			env->p--;
	}
	if (keycode == KEY_RIGHT)
	{
		if (env->p == 4)
			env->p = 0;
		else
			env->p++;
	}
	if (!(clear_and_redraw(env)))
		return (0);
	return (1);
}

static int	change_iterations(int keycode, t_env *env)
{
	if (keycode == KEY_MINUS)
	{
		if (env->screen[0]->fractal->iteration - 10 <= 5)
			env->screen[0]->fractal->iteration = 5;
		else
			env->screen[0]->fractal->iteration =
				env->screen[0]->fractal->iteration - 10;
	}
	if (keycode == KEY_EQUAL)
	{
		if (FRACT_INT_MAX - env->screen[0]->fractal->iteration > 10)
			env->screen[0]->fractal->iteration =
				env->screen[0]->fractal->iteration + 10;
	}
	if (!(display_screen_one(env)))
		return (0);
	return (1);
}

int			key_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESCAPE)
		safe_exit(env);
	if (keycode == KEY_I)
		if (!(toggle_info_menu(env)))
			return (0);
	if (keycode == KEY_Z)
		if (!(enable_zoom(env)))
			return (0);
	if (keycode == KEY_L)
		if (!(set_julia_loop(env)))
			return (0);
	if (keycode == KEY_M)
		if (!(set_menu(env)))
			return (0);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		if (!(change_palette(env, keycode)))
			return (0);
	if (keycode == KEY_MINUS || keycode == KEY_EQUAL)
		if (!(change_iterations(keycode, env)))
			return (0);
	return (0);
}
