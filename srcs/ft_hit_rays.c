/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:23:00 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:59:04 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	ft_get_normal(t_hit *hit)
{
	if (ft_strequ(hit->obj.type, "PLANE"))
		return (ft_plane_normal(hit));
	else if (ft_strequ(hit->obj.type, "SPHERE"))
		return (ft_sphere_normal(hit));
	else if (ft_strequ(hit->obj.type, "CYLINDER"))
		return (ft_cylinder_normal(hit));
	else if (ft_strequ(hit->obj.type, "PARABALOID"))
		return (ft_parabaloid_normal(hit, hit->obj.scalar));
	else
		return (ft_cone_normal(hit, hit->obj.scalar));
}

t_ray	ft_get_reflect_ray(t_hit *hit)
{
	t_ray	reflect_ray;
	double	dot;

	dot = ft_dot_product(hit->ray.d, hit->normal);
	reflect_ray.o = hit->isect;
	reflect_ray.d = ft_vec_subtract(hit->ray.d, ft_vec_scale(hit->normal, (2 * dot)));
	ft_normalize(&reflect_ray.d);
	return (reflect_ray);
}

t_ray	ft_get_refract_ray(t_hit *hit)
{
	t_ray	refract_ray;
	double	ratio;
	t_vec	temp1;
	t_vec	temp2;
	double	temp3;

	ratio = hit->incoming_iof / (hit->inside ? AIR_IOF : hit->obj.iof);
	temp1 = ft_cross_product(ft_vec_scale(hit->normal, -1), hit->ray.d);
	temp1 = ft_cross_product(hit->normal, temp1);
	temp1 = ft_vec_scale(temp1, ratio);
	temp2 = ft_cross_product(hit->normal, hit->ray.d);
	temp3 = sqrt(1 - ft_dot_product(temp2, temp2) * ratio * ratio);
	temp2 = ft_vec_scale(hit->normal, temp3);
	refract_ray.o = hit->isect;
	refract_ray.d = ft_vec_subtract(temp1, temp2);
	ft_normalize(&refract_ray.d);
	return (refract_ray);
}
