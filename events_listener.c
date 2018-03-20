/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/20 16:40:57 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		events_listener(t_env *env)
{
	if (!(mlx_key_hook(env->win, key_hook, env)))
		return (0);
	if (!(mlx_mouse_hook(env->win, mouse_hook, env)))
		return (0);
	if (!(mlx_hook(env->win, MOTION_NOTIFY, PTR_MOTION_MASK, julia_loop, env)))
		return (0);
	return (1);
}
