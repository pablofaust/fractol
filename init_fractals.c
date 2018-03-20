/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:48:08 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 18:48:09 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_julia(t_fractal *fractal)
{
	fractal->f = &julia;
	fractal->iteration = 20;
	fractal->name = 'j';
	fractal->zoom = 0.5;
	fractal->const_x = -0.784;
	fractal->const_y = -0.114;
}

void	init_mandelbrot(t_fractal *fractal)
{
	fractal->f = &mandelbrot;
	fractal->iteration = 36;
	fractal->name = 'm';
	fractal->zoom = 0.5;
	fractal->const_x = 0;
	fractal->const_y = 0;
}

void	init_antibuddhabrot(t_fractal *fractal)
{
	fractal->f = &antibuddhabrot;
	fractal->name = 'a';
	fractal->iteration = 100;
	fractal->zoom = 0.5;
	fractal->const_x = 0;
	fractal->const_y = 0;
}

void	init_buddhabrot(t_fractal *fractal)
{
	fractal->name = 'b';
	fractal->f = &buddhabrot;
	fractal->iteration = 100;
	fractal->zoom = 0.5;
	fractal->const_x = 0;
	fractal->const_y = 0;
}
