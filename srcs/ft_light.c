/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:31:06 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:56:33 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb	ft_get_light(t_hit hit, t_scene *scene)
{
	t_rgb	emission;
	t_rgb	diffuse;
	t_rgb	specular;
	t_rgb	total;
	int		i;

	total = (t_rgb){0, 0, 0};
	if (isnan(hit.t))
		return (total);
	total = ft_rgb_mult(hit.obj.diffusion, scene->amb_emission);
	i = -1;
	while (++i < scene->light_cnt)
	{
		emission = ft_adjust_emission(&hit, scene->lights[i], scene);
		diffuse = ft_get_diffuse_light(hit);
		specular = ft_get_specular_light(hit);
		total = ft_rgb_add(total,
				ft_rgb_mult(ft_rgb_add(diffuse, specular), emission));
	}
	return (total);
}

t_rgb	ft_get_diffuse_light(t_hit hit)
{
	t_rgb	diffuse;
	double	shading;

	shading = fmax(ft_dot_product(hit.normal, hit.shdw_ray.d), 0);
	diffuse = ft_rgb_scale(hit.obj.diffusion, shading);
	return (diffuse);
}

t_rgb	ft_get_specular_light(t_hit hit)
{
	t_rgb	specular;
	t_vec	half_angle;
	double	shading;
	double	brightness;

	half_angle = ft_vec_subtract(hit.shdw_ray.d, hit.ray.d);
	ft_normalize(&half_angle);
	shading = fmax(ft_dot_product(hit.normal, half_angle), 0);
	shading = pow(shading, hit.obj.phong_exp);
	brightness = shading * hit.obj.gloss;
	specular = (t_rgb){brightness, brightness, brightness};
	return (specular);
}

t_rgb	ft_adjust_emission(t_hit *hit, t_light light, t_scene *scene)
{
	t_rgb	emission;
	t_hit	shdw_hit;
	double	light_dist;

	emission = light.emission;
	hit->shdw_ray.o = hit->isect;
	hit->shdw_ray.d = (ft_strequ(light.type, "PARALLEL") ?
			ft_vec_scale(light.dir, -1) : ft_vec_subtract(light.pos, hit->isect));
	light_dist = ft_magnitude(hit->shdw_ray.d);
	emission = ft_rgb_scale(emission, (float)1 / light_dist);
	ft_normalize(&hit->shdw_ray.d);
	while (1)
	{
		shdw_hit = ft_intersect(hit->shdw_ray, scene);
		if (isnan(shdw_hit.t) ||
				(!ft_strequ(light.type, "PARALLEL") && shdw_hit.t > light_dist) ||
				(emission.r < 0.001 && emission.g < 0.001 && emission.b < 0.001))
			break ;
		emission = ft_rgb_scale(emission, shdw_hit.obj.k_refr);
		hit->shdw_ray.o = shdw_hit.isect;
		light_dist = ft_magnitude(ft_vec_subtract(light.pos, shdw_hit.isect));
	}
	return (emission);
}
