/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:09:35 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 15:00:19 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	*ft_cylinder_hit_dist(t_ray ray, double r)
{
	double	a;
	double	b;
	double	c;

	a = ray.d.x * ray.d.x + ray.d.y * ray.d.y;
	b = (ray.d.x * ray.o.x + ray.d.y * ray.o.y) * 2;
	c = (ray.o.x * ray.o.x + ray.o.y * ray.o.y) - r * r;
	return (ft_solve_quadratic(a, b, c));
}

t_vec	ft_cylinder_normal(t_hit *hit)
{
	t_vec	normal;

	normal = hit->img_isect;
	normal.z = 0;
	normal.w = 0;
	ft_normalize(&normal);
	hit->inside = ft_dot_product(hit->img_ray.d, normal) > 0;
	if (hit->inside)
		normal = ft_vec_scale(normal, -1);
	return (normal);
}
