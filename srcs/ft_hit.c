/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:23:00 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 15:04:04 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

int	ft_within_limits(t_obj obj, t_ray ray, double t)
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

	
void	ft_get_reflect_ray(t_hit *hit)
{
	double dot;

	dot = ft_dot_product(hit->ray.d, hit->normal);
	hit->reflect_ray.o = hit->isect;
	hit->reflect_ray.d = ft_vec_subtract(hit->ray.d, ft_vec_scale(hit->normal, (2 * dot)));
}

void	ft_get_refract_ray(t_hit *hit)
{
	double ratio;
	t_vec temp1;
	t_vec temp2;
	double temp3;

	ratio = hit->n1 / (hit->inside ? AIR_N1 : hit->obj.n2);
	temp1 = ft_cross_product(ft_vec_scale(hit->normal, -1), hit->ray.d);
	temp1 = ft_cross_product(hit->normal, temp1);
	temp1 = ft_vec_scale(temp1, ratio);
	temp2 = ft_cross_product(hit->normal, hit->ray.d);
	temp3 = sqrt(1 - ft_dot_product(temp2, temp2) * ratio * ratio);
	temp2 = ft_vec_scale(hit->normal, temp3);
	hit->refract_ray.o = hit->isect;
	hit->refract_ray.d = ft_vec_subtract(temp1, temp2);
	ft_normalize(&hit->refract_ray.d);
}


void	ft_get_hit_data(t_hit *hit)
{
	hit->isect = ft_vec_add(hit->ray.o, ft_vec_scale(hit->ray.d, hit->t));
	hit->img_isect = ft_vec_add(hit->img_ray.o, ft_vec_scale(hit->img_ray.d, hit->t));
	hit->img_normal = ft_get_normal(hit);
	hit->normal = ft_mat_vec_mult(hit->obj.transform, hit->img_normal);
	ft_get_reflect_ray(hit);
//	ft_hit_to_world(hit);
}





/*
void	ft_hit_to_world(t_hit *hit)
{
	hit->ray.o = ft_mat_vec_mult(hit->obj.transform, hit->ray.o);
	hit->ray.d = ft_mat_vec_mult(hit->obj.transform, hit->ray.d);
	hit->isect = ft_mat_vec_mult(hit->obj.transform, hit->isect);
	hit->normal = ft_mat_vec_mult(hit->obj.transform, hit->normal);
	hit->reflect_ray.d = ft_mat_vec_mult(hit->obj.transform, hit->reflect_ray.d);
}
*/
