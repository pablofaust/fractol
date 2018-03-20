/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:52:04 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/20 17:02:54 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		zoom_in_or_out(t_screen *scr, int button)
{
	if (button == 2)
		scr->fractal->zoom = scr->fractal->zoom / 1.1;
	else if (button == 1)
		scr->fractal->zoom = scr->fractal->zoom * 1.1;
}

void		zoom_start_pos(t_iter *start, t_iter *after, t_screen *scr)
{
	if (after->x >= 0)
		scr->fractal->start_x = scr->fractal->start_x +
		fdim(fmax(after->x, start->x), fmin(after->x, start->x));
	else
		scr->fractal->start_x = scr->fractal->start_x -
		fdim(fmax(after->x, start->x), fmin(after->x, start->x));
	if (after->y >= 0)
		scr->fractal->start_y = scr->fractal->start_y +
		fdim(fmax(after->y, start->y), fmin(after->y, start->y));
	else
		scr->fractal->start_y = scr->fractal->start_y -
		fdim(fmax(after->y, start->y), fmin(after->y, start->y));
}

int			zoom(int button, int x, int y, t_env *env)
{
	t_screen	*scr;
	t_iter		start;
	t_iter		after;

	if (env->julia_loop == 0)
	{
		scr = env->screen[0];
		start.y = 0 - (scr->ratio_y * ((y - scr->height / 2.0) /
		(0.5 * scr->fractal->zoom * scr->height)));
		start.x = scr->ratio_x * (x - scr->width / 2.0) /
		(0.5 * scr->fractal->zoom * scr->width);
		zoom_in_or_out(scr, button);
		after.x = ((scr->ratio_x * (x - scr->width / 2.0) /
		(0.5 * scr->fractal->zoom * scr->width)));
		after.y = 0 - (scr->ratio_y * ((y - scr->height / 2.0) /
		(0.5 * scr->fractal->zoom * scr->height)));
		zoom_start_pos(&start, &after, scr);
		if (!(display_screen_one(env)))
			return (0);
	}
	return (1);
}
