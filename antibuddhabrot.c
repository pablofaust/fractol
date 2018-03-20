/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/20 15:36:52 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_fractal_pixel(t_screen *scr, int pixel_x, int pixel_y, int i)
{
	int	pos;

	pos = (pixel_y * WIDTH_SCREEN) + pixel_x;
	if (pixel_x > scr->min_scr_x && pixel_x < scr->max_scr_x &&
		pixel_y > scr->min_scr_y && pixel_y < scr->max_scr_y && i > 50)
	{
		if (0xffffff - scr->data_addr[pos] > scr->hex_const)
			scr->data_addr[pos] = scr->data_addr[pos] + scr->hex_const;
		else
			scr->data_addr[pos] = 0xffffff;
	}
}

int			iter_anti(t_iter *iter, int nbr_iter, t_screen *scr)
{
	double		x_tmp;
	int			i;
	double		pixel_x;
	double		pixel_y;

	iter->o_x = iter->x;
	iter->o_y = iter->y;
	pixel_x = 0;
	pixel_y = 0;
	i = -1;
	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && ++i <= nbr_iter)
	{
		draw_fractal_pixel(scr, (int)round(pixel_x), (int)round(pixel_y), i);
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y;
		pixel_x = (((iter->y - scr->fractal->start_x) * (0.5 * scr->width *
		scr->fractal->zoom)) / scr->ratio_x) + (scr->width * 0.5) +
		scr->min_scr_x;
		pixel_y = (scr->height * 0.5) - (iter->x - scr->fractal->start_y) *
			((0.5 * scr->fractal->zoom * scr->height) / scr->ratio_y) +
			scr->min_scr_y;
	}
	return (0);
}

void		*thread_anti(void *arg)
{
	int			x;
	int			y;
	double		real_y;
	t_iter		iter;
	t_screen	*scr;

	scr = arg;
	scr->hex_const = hex_to_rgb_to_hsl(scr->pal[scr->p][1]);
	y = scr->min_y - 1;
	while (++y < scr->max_y)
	{
		x = scr->min_x - 1;
		real_y = 0 - (scr->ratio_y * (((y - scr->min_scr_y) -
		scr->height / 2.0) / (0.5 * scr->fractal->zoom * scr->height))) +
		scr->fractal->start_y;
		while (++x < scr->max_x)
		{
			iter.y = real_y;
			iter.x = scr->ratio_x * (((x - scr->min_scr_x) - scr->width / 2.0) /
			(0.5 * scr->fractal->zoom * scr->width)) + scr->fractal->start_x;
			if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
				iter_anti(&iter, scr->fractal->iteration, scr);
		}
	}
	pthread_exit(NULL);
}
