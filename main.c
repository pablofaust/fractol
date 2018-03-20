/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:10:02 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/20 17:10:45 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		valid_argument(char *str)
{
	if (ft_strequ(str, "mandelbrot"))
		return (1);
	else if (ft_strequ(str, "julia"))
		return (1);
	else if (ft_strequ(str, "buddhabrot"))
		return (1);
	else if (ft_strequ(str, "anti-buddhabrot"))
		return (1);
	else
		ft_printf("Usage : ./fractol	julia |		mandelbrot |\
	buddhabrot |	anti-buddhabrot\n");
	return (0);
}

int				display_screen_one(t_env *env)
{
	clear_zone(1, env);
	if (!(env->screen[0]->fractal->f(env)))
		return (0);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (!(display_info_menu(env)))
		return (0);
	return (1);
}

void			safe_exit(t_env *env)
{
	if (env->screen)
	{
		free_fractal(env->screen);
		free_screens(env->screen);
	}
	if (env->mlx && env->img && env->win)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
	}
	exit(EXIT_SUCCESS);
}

int				display_fractals(t_env *env)
{
	int	i;

	i = 0;
	if (env->show_menu)
	{
		while (i < 4)
		{
			if (!(env->screen[i]->fractal->f(env)))
				return (0);
			i++;
		}
	}
	else
	{
		if (!(env->screen[0]->fractal->f(env)))
			return (0);
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (!(display_info_menu(env)))
		return (0);
	return (1);
}

int				main(int ac, char **av)
{
	t_env		env;
	t_screen	**screens;

	screens = NULL;
	if (!(ft_check_arguments("./fractol", ac, 1, 1)))
		return (0);
	if (!(valid_argument(av[1])) || !(init_env(&env, av[1])))
	{
		printf("alo ? \n");
		safe_exit(&env);
	}
	if (!(env.screen = init_screens(screens, env.show_menu, env.param)))
		safe_exit(&env);
	else
	{
		if (!(display_fractals(&env)))
			safe_exit(&env);
		if ((!events_listener(&env)))
			safe_exit(&env);
		mlx_loop(env.mlx);
		free_fractal(screens);
		free_screens(screens);
	}
	return (0);
}
