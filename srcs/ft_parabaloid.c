/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parabaloid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:35:22 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 15:00:48 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	*ft_parabaloid_hit_dist(t_ray ray, double s)
{
	double	a;
	double	b;
	double	c;

	a = ray.d.x * ray.d.x + ray.d.y * ray.d.y;
	b = 2 * (ray.o.x * ray.d.x + ray.o.y * ray.d.y) - s * ray.d.z;
	c = ray.o.x * ray.o.x + ray.o.y * ray.o.y - s * ray.o.z;
	return (ft_solve_quadratic(a, b, c));
}

t_vec	ft_parabaloid_normal(t_hit *hit, double s)
{
	t_vec	normal;

	normal.x = 2 * hit->img_isect.x;
	normal.y = 2 * hit->img_isect.y;
	normal.z = -s;
	normal.w = 0;
	ft_normalize(&normal);
	hit->inside = ft_dot_product(hit->img_ray.d, normal) > 0;
	if (hit->inside)
		normal = ft_vec_scale(normal, -1);
	return (normal);
}
