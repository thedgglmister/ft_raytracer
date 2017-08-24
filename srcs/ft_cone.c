/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:09:50 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 14:59:29 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	*ft_cone_hit_dist(t_ray ray, double s)
{
	double	a;
	double	b;
	double	c;

	a = ray.d.x * ray.d.x + ray.d.y * ray.d.y - ray.d.z * ray.d.z * s * s;
	b = (ray.d.x * ray.o.x + ray.d.y * ray.o.y - ray.d.z * ray.o.z * s * s) * 2;
	c = ray.o.x * ray.o.x + ray.o.y * ray.o.y - ray.o.z * ray.o.z * s * s;
	return (ft_solve_quadratic(a, b, c));
}

t_vec	ft_cone_normal(t_hit *hit, double s)
{
	t_vec	normal;

	normal = hit->img_isect;
	normal.z = 0;
	ft_normalize(&normal);
	normal.z = (normal.z < 0 ? s : -s);
	ft_normalize(&normal);
	normal.w = 0;
	hit->inside = ft_dot_product(hit->img_ray.d, normal) > 0;
	if (hit->inside)
		normal = ft_vec_scale(normal, -1);
	return (normal);
}
