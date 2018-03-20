/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_of_3_double.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:57:46 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/20 18:16:45 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_max_of_3_double(double x, double y, double z)
{
	if (x >= y && x >= y)
		return (x);
	else if (y > x && y >= z)
		return (y);
	else
		return (z);
}
