/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:36:36 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 17:23:28 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	*ft_plane_hit_dist(t_ray ray)
{
	double *t;

	t = (double*)ft_malloc(sizeof(double) * 2);
	t[0] = -ray.o.z / ray.d.z;
	t[1] = NAN;
	return (t);
}

t_vec	ft_plane_normal(t_hit *hit)
{
	t_vec normal;

	normal = (t_vec){0, 0, 1, 0};
	if (hit->img_ray.d.z > 0)
	{
		normal.z = -1;
		hit->inside = 1;
	}
	return (normal);
}
