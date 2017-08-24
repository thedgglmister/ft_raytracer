/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:37:12 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 15:01:48 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	*ft_sphere_hit_dist(t_ray ray, double r)
{
	double	a;
	double	b;
	double	c;

	a = ft_dot_product(ray.d, ray.d);
	b = ft_dot_product(ray.o, ray.d) * 2;
	c = ft_dot_product(ray.o, ray.o) - r * r;
	return (ft_solve_quadratic(a, b, c));
}

t_vec	ft_sphere_normal(t_hit *hit)
{
	t_vec	normal;

	normal = hit->img_isect;
	normal.w = 0;
	ft_normalize(&normal);
	hit->inside = ft_dot_product(hit->img_ray.d, normal) > 0;
	if (hit->inside)
		normal = ft_vec_scale(normal, -1);
	return (normal);
}
