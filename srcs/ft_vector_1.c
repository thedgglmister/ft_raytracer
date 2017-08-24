/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:37:58 by biremong          #+#    #+#             */
/*   Updated: 2017/05/15 17:39:31 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_dot_product(t_vec u, t_vec v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

double	ft_magnitude(t_vec v)
{
	return (sqrt(ft_dot_product(v, v)));
}

void	ft_normalize(t_vec *u)//not 0
{
	double	mag;

	mag = ft_magnitude(*u);
	*u = ft_vec_scale(*u, (1 / mag));
}

double	ft_vector_angle(t_vec u, t_vec v)
{
	double	dot;
	double	mag_v;
	double	mag_u;
	double	ratio;

	dot = ft_dot_product(u, v);
	mag_u = ft_magnitude(u);
	mag_v = ft_magnitude(v);
	ratio = dot / (mag_u * mag_v);
	if (ratio > 1)
		ratio = 1;
	else if (ratio < -1)
		ratio = -1;
	return (acos(ratio));
}
