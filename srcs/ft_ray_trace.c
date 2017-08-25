/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:08:48 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:55:05 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb	ft_ray_trace(t_ray ray, t_scene *scene, int recurse_n)
{
	t_hit	hit;
	t_rgb	plain_light;
	t_rgb	reflect_light;
	t_rgb	refract_light;
	t_rgb	combined;

	hit = ft_intersect(ray, scene);
	plain_light = ft_get_light(hit, scene);
	if (isnan(hit.t) ||
			recurse_n >= MAX_RECURSE ||
			(hit.obj.k_refl == 0 && hit.obj.k_refr == 0))
		return (plain_light);
	if (isnan(ray.d.x))
	{
		refract_light = (t_rgb){NAN, NAN, NAN};
		return (refract_light);
	}
	reflect_light = ft_ray_trace(hit.reflect_ray, scene, recurse_n + 1);
	refract_light = ft_ray_trace(hit.refract_ray, scene, recurse_n + 1);
	combined = ft_combine_light(&hit, reflect_light, refract_light, plain_light);
	return (combined);
}

t_rgb	ft_combine_light(t_hit *hit, t_rgb refl, t_rgb refr, t_rgb plain)
{
	t_rgb	combined;
	double	r0;
	double	refl_pcnt;
	double	theta;
	double	out_iof;

	if (isnan(refr.r))
		refl_pcnt = 1;
	else
	{
		out_iof = (hit->inside ? AIR_IOF : hit->obj.iof);
		r0 = (hit->incoming_iof - out_iof) / (hit->incoming_iof + out_iof);
		r0 = r0 * r0;
		theta = ft_vector_angle(hit->ray.d, ft_vec_scale(hit->normal, -1));
		refl_pcnt = r0 + (1 - r0) * pow(1 - cos(theta), 5);
	}
	combined.r = (plain.r + hit->obj.k_refl * refl.r) * refl_pcnt +
				hit->obj.k_refr * (1 - refl_pcnt) * refr.r;
	combined.g = (plain.g + hit->obj.k_refl * refl.g) * refl_pcnt +
				hit->obj.k_refr * (1 - refl_pcnt) * refr.g;
	combined.b = (plain.b + hit->obj.k_refl * refl.b) * refl_pcnt +
				hit->obj.k_refr * (1 - refl_pcnt) * refr.b;
	return (combined);
}
