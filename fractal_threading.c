/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_threading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:40:22 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 15:40:29 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			antibuddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'a');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, &thread_anti,
					(void *)screens[i]) == -1)
		{
			perror("pthread_create");
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = -1;
	while (++i < 4)
		pthread_join(thread[i], NULL);
	free_screens(screens);
	return (1);
}

int			buddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'b');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);
	i = -1;
	while (++i < 4)
	{
		if (pthread_create(&thread[i], NULL, &thread_buddha,
					(void *)screens[i]) == -1)
		{
			perror("pthread_create");
			return (EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < 4)
		pthread_join(thread[i], NULL);
	free_screens(screens);
	return (1);
}
