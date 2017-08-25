/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:30:43 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:57:06 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hit	ft_intersect(t_ray ray, t_scene *scene)
{
	t_hit		hit;
	t_ray		img_ray;
	t_obj		obj;
	double		*t;
	int			i;

	hit.t = NAN;
	i = -1;
	while (++i < scene->obj_cnt)
	{
		obj = scene->objs[i];
		img_ray.o = ft_mat_vec_mult(obj.inv_transform, ray.o);
		img_ray.d = ft_mat_vec_mult(obj.inv_transform, ray.d);
		t = ft_hit_dist(img_ray, obj);
		t[0] = ft_closest_hit(obj, img_ray, t, hit.t);
		if (!isnan(t[0]))
		{
			hit.ray = ray;
			hit.img_ray = img_ray;
			hit.t = t[0];
			hit.obj = obj;
		}
		free(t);
	}
	ft_get_hit_data(&hit);
	return (hit);
}

void	ft_get_hit_data(t_hit *hit)
{
	t_vec	temp;

	if (isnan(hit->t))
		return ;
	hit->isect = ft_vec_add(hit->ray.o, ft_vec_scale(hit->ray.d, hit->t));
	temp = ft_vec_scale(hit->img_ray.d, hit->t);
	hit->img_isect = ft_vec_add(hit->img_ray.o, temp);
	hit->img_normal = ft_get_normal(hit);
	hit->normal = ft_mat_vec_mult(hit->obj.transform, hit->img_normal);
	hit->incoming_iof = (hit->inside ? hit->obj.iof : AIR_IOF);
	hit->reflect_ray = ft_get_reflect_ray(hit);
	hit->refract_ray = ft_get_refract_ray(hit);
}
