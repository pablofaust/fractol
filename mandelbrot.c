/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:48:36 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 18:48:38 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mandelbrot_iter(t_iter *iter,
		int nbr_iter, t_screen *scr, int pixel)
{
	int		i;
	double	input_y;
	double	input_x;
	double	x_tmp;
	double	y_tmp;

	input_x = iter->x;
	input_y = iter->y;
	i = 0;
	while (((iter->x * iter->x) + (iter->y * iter->y)) < 4 && i <= nbr_iter)
	{
		if (i > 0)
			scr->data_addr[pixel] = scr->pal[scr->p][i % 5];
		x_tmp = iter->x;
		y_tmp = iter->y;
		iter->x = (x_tmp * x_tmp) - (y_tmp * y_tmp) + input_x;
		iter->y = 2 * (x_tmp * y_tmp) + input_y;
		i++;
	}
}

static void	*thread_mandelbrot(void *arg)
{
	int			x;
	int			y;
	double		real_y;
	t_iter		iter;
	t_screen	*scr;

	scr = arg;
	y = scr->min_y - 1;
	while (++y < scr->max_y)
	{
		x = scr->min_x - 1;
		real_y = 0 - (scr->ratio_y * (((y - scr->min_scr_y) - scr->height / 2.0)
		/ (0.5 * scr->fractal->zoom * scr->height))) + scr->fractal->start_y;
		while (++x < scr->max_x)
		{
			iter.y = real_y;
			iter.x = scr->ratio_x * (((x - scr->min_scr_x) - scr->width / 2.0) /
			(0.5 * scr->fractal->zoom * scr->width)) + scr->fractal->start_x;
			if (((iter.x * iter.x) + (iter.y * iter.y)) < 4)
				mandelbrot_iter(&iter, scr->fractal->iteration,
					scr, (y * WIDTH_SCREEN) + x);
		}
	}
	pthread_exit(NULL);
}

int			mandelbrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'm');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);
	i = -1;
	while (++i < 4)
	{
		if (pthread_create(&thread[i], NULL, &thread_mandelbrot,
					(void *)screens[i]) == -1)
		{
			perror("pthread_create");
			safe_exit(env);
		}
	}
	i = -1;
	while (++i < 4)
		pthread_join(thread[i], NULL);
	free_screens(screens);
	return (1);
}
