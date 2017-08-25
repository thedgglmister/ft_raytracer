/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:23:00 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:57:55 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	*ft_hit_dist(t_ray ray, t_obj obj)
{
	if (ft_strequ(obj.type, "PLANE"))
		return (ft_plane_hit_dist(ray));
	else if (ft_strequ(obj.type, "SPHERE"))
		return (ft_sphere_hit_dist(ray, obj.scalar));
	else if (ft_strequ(obj.type, "CYLINDER"))
		return (ft_cylinder_hit_dist(ray, obj.scalar));
	else if (ft_strequ(obj.type, "PARABALOID"))
		return (ft_parabaloid_hit_dist(ray, obj.scalar));
	else
		return (ft_cone_hit_dist(ray, obj.scalar));
}

double	ft_closest_hit(t_obj obj, t_ray ray, double *t, double prev_t)
{
	if (t[0] < 0.00001 || isinf(t[0]) || (!isnan(prev_t) && t[0] > prev_t))
		t[0] = NAN;
	if (t[1] < 0.00001 || isinf(t[1]) || (!isnan(prev_t) && t[1] > prev_t))
		t[1] = NAN;
	if (isnan(t[0]) && isnan(t[1]))
		return (NAN);
	else if (isnan(t[0]))
		return ((ft_within_limits(obj, ray, t[1]) ? t[1] : NAN));
	else if (isnan(t[1]))
		return ((ft_within_limits(obj, ray, t[0]) ? t[0] : NAN));
	else if (t[0] < t[1])
	{
		if (ft_within_limits(obj, ray, t[0]))
			return (t[0]);
		else
			return ((ft_within_limits(obj, ray, t[1]) ? t[1] : NAN));
	}
	else
	{
		if (ft_within_limits(obj, ray, t[1]))
			return (t[1]);
		else
			return ((ft_within_limits(obj, ray, t[0]) ? t[0] : NAN));
	}
}

int		ft_within_limits(t_obj obj, t_ray ray, double t)
{
	t_vec isect;

	isect = ft_vec_add(ray.o, ft_vec_scale(ray.d, t));
	if (!isinf(obj.min_lim[0]) && isect.x < obj.min_lim[0])
		return (0);
	if (!isinf(obj.min_lim[1]) && isect.y < obj.min_lim[1])
		return (0);
	if (!isinf(obj.min_lim[2]) && isect.z < obj.min_lim[2])
		return (0);
	if (!isinf(obj.max_lim[0]) && isect.x > obj.max_lim[0])
		return (0);
	if (!isinf(obj.max_lim[1]) && isect.y > obj.max_lim[1])
		return (0);
	if (!isinf(obj.max_lim[2]) && isect.z > obj.max_lim[2])
		return (0);
	return (1);
}
