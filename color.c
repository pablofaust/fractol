/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:52:30 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/19 22:26:31 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int rgb_to_hex(int r, int g, int b)
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

unsigned int rgb_to_hsl(double r, double g, double b)
{
	double	c;
	double	l;
	double	hue;
	double	saturation;

	r = r / 255;
	g = g / 255;
	b = b / 255;
	c = ft_max_of_3_double(r , g , b ) - ft_min_of_3_double(r , g , b );
	l = (ft_max_of_3_double(r , g , b ) + ft_min_of_3_double(r , g , b )) / 2.0;
	if (r  == ft_max_of_3_double(r , g , b ) && c != 0)
		hue = fmod(((g - b) ) / c, 6.0) * 60.0;
	else if (g  == ft_max_of_3_double(r , g , b ) && c != 0)
		hue = ((b - r) / c + 2.0) * 60.0;
	else if (b  == ft_max_of_3_double(r , g , b ) && c != 0)
		hue = ((r - g) / c + 4.0) * 60.0;
	else
		hue = 0;
	saturation = c / (1.0 - fabs(2 * l - 1.0));
	return (hsv_calculator(hue, saturation, 0.15));
}

unsigned int hex_to_rgb_to_hsl(unsigned int hex)
{
	double		r;
	double		g;
	double		b;

	r = hex >> 16;
	g = (hex >> 8) & 0xff;
	b = hex & 0xff;
	return (rgb_to_hsl(r, g, b));
}

unsigned int hsl_calculator(double hue, double saturation, double light)
{
	double	chroma;
	double	min;
	double  x;

	chroma = (1.0 - fabs(2.0 * light) - 1.0) * saturation; 
	min = 1.0 * (light - (0.5 * chroma));
	x = chroma * (1.0 - (fabs(fmod(hue / 60.0, 2.0) - 1.0))); // PAS BON
	if (hue >= 0 && hue <= 60)
		return (rgb_to_hex((int)round((chroma + min) * 255),(int)round((x + min) * 255),(int)round(min * 255)));	
	if (hue > 60 && hue <= 120)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round((chroma + min) * 255),(int)round(min * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb_to_hex((int)round((min) * 255),(int)round((chroma + min) * 255),(int)round((x + min) * 255)));
	if (hue > 180 && hue <= 240)
		return (rgb_to_hex((int)round(min * 255),(int)round((x + min) * 255),(int)round((chroma + min) * 255)));
	if (hue > 240 && hue <= 300)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round(min * 255),(int)round((chroma + min) * 255)));
	else if (hue > 300 && hue <= 360)
		return (rgb_to_hex((int)round((chroma + min)* 255),(int)round((min) * 255),(int)round((x + min) * 255)));
	else
		return (rgb_to_hex(min * 255, min * 255, min * 255));
	return (0);
}

unsigned int hsv_calculator(double hue, double saturation, double bright)
{
	double	chroma;
	double	min;
	double  x;

	chroma = bright * saturation;
	min = bright - chroma;
	x = chroma * (1.0 - fabs(fmod(hue / 60.0, 2) - 1.0));
	if (hue >= 0 && hue <= 60)
		return (rgb_to_hex((int)round((chroma + min) * 255),(int)round((x + min) * 255),(int)round(min * 255)));
	if (hue > 60 && hue <= 120)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round((chroma + min) * 255),(int)round(min * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb_to_hex((int)round((min) * 255),(int)round((chroma + min) * 255),(int)round((x + min) * 255)));
	if (hue > 180 && hue <= 240)
		return (rgb_to_hex((int)round(min * 255),(int)round((x + min) * 255),(int)round((chroma + min) * 255)));
	if (hue > 240 && hue <= 300)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round(min * 255),(int)round((chroma + min) * 255)));
	else
		return (rgb_to_hex((int)round((chroma + min)* 255),(int)round((min) * 255),(int)round((x + min) * 255)));
	return (0);
}


