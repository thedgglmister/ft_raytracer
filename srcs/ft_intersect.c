/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:30:43 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 15:06:33 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//textures need to be un-gamma-corrected?

t_hit	ft_intersect(t_ray ray, t_scene *scene)//free t
{
	t_hit		hit;
	t_ray		img_ray;
	t_obj		obj;
	double		*t;
	int			i;

	hit.t = NAN;
	i = -1;
	while (++i < scene->obj_cnt) //is it getting closest hit????HOW?????
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
	}
	if (!isnan(hit.t))
		ft_get_hit_data(&hit);
	return (hit);
}
