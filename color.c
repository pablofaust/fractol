/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:47:56 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 18:47:57 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int hex;

	if (r > 255)
		r = 255;
	if (b > 255)
		b = 255;
	if (g > 255)
		g = 255;
	hex = (r << 16) + (g << 8) + b;
	return (hex);
}

unsigned int	rgb_to_hsl(double r, double g, double b, double light)
{
	double	c;
	double	l;
	double	hue;
	double	saturation;

	r = r / 255;
	g = g / 255;
	b = b / 255;
	c = ft_max_of_3_double(r, g, b) - ft_min_of_3_double(r, g, b);
	l = (ft_max_of_3_double(r, g, b) + ft_min_of_3_double(r, g, b)) / 2.0;
	if (r == ft_max_of_3_double(r, g, b) && c != 0)
		hue = fmod(((g - b)) / c, 6.0) * 60.0;
	else if (g == ft_max_of_3_double(r, g, b) && c != 0)
		hue = ((b - r) / c + 2.0) * 60.0;
	else if (b == ft_max_of_3_double(r, g, b) && c != 0)
		hue = ((r - g) / c + 4.0) * 60.0;
	else
		hue = 0;
	saturation = c / (1.0 - fabs(2 * l - 1.0));
	return (hsv_calculator(hue, saturation, light));
}

unsigned int	hex_to_rgb_to_hsl(unsigned int hex, double light)
{
	double		r;
	double		g;
	double		b;

	r = hex >> 16;
	g = (hex >> 8) & 0xff;
	b = hex & 0xff;
	return (rgb_to_hsl(r, g, b, light));
}

unsigned int	hsv_calculator(double hue, double saturation, double bright)
{
	double	c;
	double	m;
	double	x;
	int		cm;
	int		xm;

	c = bright * saturation;
	m = bright - c;
	x = c * (1.0 - fabs(fmod(hue / 60.0, 2) - 1.0));
	cm = (int)round((c + m) * 255);
	xm = (int)round((x + m) * 255);
	if (hue >= 0 && hue <= 60)
		return (rgb_to_hex(cm, xm, (int)round(m * 255)));
	if (hue > 60 && hue <= 120)
		return (rgb_to_hex(xm, xm, (int)round(m * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb_to_hex((int)round(m * 255), cm, xm));
	if (hue > 180 && hue <= 240)
		return (rgb_to_hex((int)round(m * 255), xm, cm));
	if (hue > 240 && hue <= 300)
		return (rgb_to_hex(xm, (int)round(m * 255), cm));
	else
		return (rgb_to_hex(cm, (int)round((m) * 255), xm));
	return (0);
}
