/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:31:06 by biremong          #+#    #+#             */
/*   Updated: 2017/06/22 15:22:03 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//NEED TO DO SOMETHING SO NOT JUST ONE SIDE CAN GET LIT UP
//MAKE SCENE FILE MORE INTUITIVE, LIKE SPHERE HAS CENTER AND RADIUS, CONE HAS RADISU AND HIGHT AND CENTER, CYLINDER HAS CENTER RADIUS AND HEIGHT, OPTION FOR INFINITY?

t_rgb	ft_get_light(t_hit hit, t_scene *scene)
{
	t_rgb	diffuse;
	t_rgb	specular;
	t_rgb	total;
	t_light	light;
	int		i;

	total = ft_get_ambient_light(hit, scene->amb_emission);
	i = -1;
	while (++i < scene->light_cnt)
	{
		light = scene->lights[i];
		if (!ft_in_shadow(&hit, light, scene))
		{
			diffuse = ft_get_diffuse_light(hit, light);
			specular = ft_get_specular_light(hit, light);
			total.r += diffuse.r + specular.r;
			total.g += diffuse.g + specular.g;
			total.b += diffuse.b + specular.b;
		}
	}
	return (total);
}

t_rgb	ft_get_ambient_light(t_hit hit, t_rgb amb_emission)
{
	t_rgb	ambient;

	ambient.r = amb_emission.r * hit.obj.diffusion.r;
	ambient.g = amb_emission.g * hit.obj.diffusion.g;
	ambient.b = amb_emission.b * hit.obj.diffusion.b;
	return (ambient);
}

t_rgb	ft_get_diffuse_light(t_hit hit, t_light light)
{
	t_rgb	diffuse;
	double	shading;

	shading = fmax(ft_dot_product(hit.normal, hit.shdw_ray.d), 0);
	light.emission.r /= hit.light_dist;
	light.emission.g /= hit.light_dist;
	light.emission.b /= hit.light_dist;
	diffuse.r = light.emission.r * shading * hit.obj.diffusion.r;
	diffuse.g = light.emission.g * shading * hit.obj.diffusion.g;
	diffuse.b = light.emission.b * shading * hit.obj.diffusion.b;
	return (diffuse);
}

t_rgb	ft_get_specular_light(t_hit hit, t_light light)
{
	t_rgb	specular;
	t_vec	half_angle;
	double	shading;
	
	half_angle = ft_vec_subtract(hit.shdw_ray.d, hit.ray.d);
	ft_normalize(&half_angle);
	shading = fmax(ft_dot_product(hit.normal, half_angle), 0);
	shading = pow(shading, hit.obj.phong_exp);
	light.emission.r /= hit.light_dist;
	light.emission.g /= hit.light_dist;
	light.emission.b /= hit.light_dist;
	specular.r = light.emission.r * shading * hit.obj.gloss;
	specular.g = light.emission.g * shading * hit.obj.gloss;
	specular.b = light.emission.b * shading * hit.obj.gloss;
	return (specular);
}

int		ft_in_shadow(t_hit *hit, t_light light, t_scene *scene)
{
	t_hit	shdw_hit;

	hit->shdw_ray.o = hit->isect;
	if (ft_strequ(light.type, "POINT"))
		hit->shdw_ray.d = ft_vec_subtract(light.pos, hit->isect);
	else if (ft_strequ(light.type, "PARALLEL"))
		hit->shdw_ray.d = ft_vec_scale(light.dir, -1);
	hit->light_dist = ft_magnitude(hit->shdw_ray.d);
	ft_normalize(&(hit->shdw_ray.d));
	shdw_hit = ft_intersect(hit->shdw_ray, scene);
	if (!isnan(shdw_hit.t) &&
			(ft_strequ(light.type, "PARALLEL") || shdw_hit.t < hit->light_dist))
		return (1);
	else
		return (0);
}
