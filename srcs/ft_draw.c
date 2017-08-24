/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:08:48 by biremong          #+#    #+#             */
/*   Updated: 2017/08/21 16:49:04 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//keep track of total distacne traveled by light as it refelcts to diminish it...?


#include "rtv1.h"

void	ft_draw_scene(t_globals *glob)
{
	t_ray	ray;
	int		row;
	int		col;
	int		color;

	ray.o = ft_mat_vec_mult(glob->cam->transform, glob->cam->ray.o);
	row = -1;
	while (++row < WIN_H)
	{
		col = -1;
		while (++col < WIN_W)
		{
			color = ft_get_color(ray, row, col, glob);
			ft_draw_pixel(glob->win->img_str, row, col, color);
		}
	}
	mlx_put_image_to_window(glob->win->mlx,
							glob->win->win,
							glob->win->img,
							0, 0);
}

int		ft_get_color(t_ray ray, int row, int col, t_globals *glob)
{
	int		i;
	double	randx;
	double	randy;
	t_rgb	samples[SS_CNT];
	t_rgb	color;

	i = -1;
	while (++i < SS_CNT)
	{
		randx = ((double)rand() / (double)RAND_MAX) / sqrt(SS_CNT);
		randy = ((double)rand() / (double)RAND_MAX) / sqrt(SS_CNT);
		ray.d = (t_vec)
				{col - WIN_W * 0.5 + (i % (int)sqrt(SS_CNT)) * 0.5 + randx,
				WIN_H * 0.5 - row - (i / sqrt(SS_CNT)) * 0.5 - randy,
				-glob->cam->plane_dist,
				0};
		ray.d = ft_mat_vec_mult(glob->cam->transform, ray.d);
		ft_normalize(&ray.d);
		samples[i] = ft_ray_trace(ray, glob->scene, 0, AIR_N1);
	}
	color = ft_combine_samples(samples);
	color = ft_scale_white(color);
	color = ft_gamma_correction(color, 2.2);
	return (ft_rgb_to_int(color));
}

t_rgb	ft_ray_trace(t_ray ray, t_scene *scene, int recurse_count, double n1) //only get hit info on things if i need them, if i dont need reflection, for example...
{
	t_hit	hit;
	t_rgb	hit_light;
	t_rgb	reflect_light;
	t_rgb	refract_light;
	t_rgb	combined;

	hit_light = (t_rgb){0, 0, 0};
	reflect_light = (t_rgb){0, 0, 0};// nec?
	refract_light = (t_rgb){0, 0, 0};// nec?

	hit = ft_intersect(ray, scene); 
	hit.n1 = n1;
//printf("%d\n", recurse_count);
//	printf("%f %f %f\n", hit.reflect_ray.o.x, hit.reflect_ray.o.y,  hit.reflect_ray.o.z);
//	printf("%f %f %f\n\n", hit.reflect_ray.d.x, hit.reflect_ray.d.y,  hit.reflect_ray.d.z);

/*
if (recurse_count == 1 )//&& !isnan(hit.t))
{
	printf("%d\n", recurse_count);	
	printf("%f %f %f\n", ray.o.x, ray.o.y, ray.o.z);
	printf("%f %f %f\n\n", ray.d.x, ray.d.y, ray.d.z);
	//printf("%f %f %f\n\n", hit.reflect_ray.d.x, hit.reflect_ray.d.y, hit.reflect_ray.d.z); //need to check intersect function because poitns are hitting that shouldnt be, there angles of rreflection seem right
}
*/
	if (isnan(hit.t))
	{
		printf("a\n");
		return (hit_light); //black
	}

	hit_light = ft_get_light(hit, scene); //have this return black if nan... get rid of lines above

	if (recurse_count == MAX_RECURSE || (hit.obj.k_refl == 0 && hit.obj.k_refr == 0))
	{
	//	if (ray.d.x < 0.01 && ray.d.x > -0.01 && ray.d.y < 0.01 && ray.d.y > -0.01)
	//		printf("%d   %f %f %f\n", recurse_count, hit_light.r, hit_light.g, hit_light.b); 


		return (hit_light);

	}

	if (hit.obj.k_refl != 0)
	{ //fresnal it


		reflect_light = ft_ray_trace(hit.reflect_ray, scene, recurse_count + 1, n1); //n2? shouldnt it stay same?
	//	printf("%f %f %f\n\n", reflect_light.r, reflect_light.g, reflect_light.b);
	}

	if (hit.obj.k_refr != 0)
	{// fresnal it

		ft_get_refract_ray(&hit);
		refract_light = ft_ray_trace(hit.refract_ray, scene, recurse_count + 1, hit.obj.n2);
	}


	combined = ft_combine_light(&hit, reflect_light, refract_light, hit_light);
	return (combined);
}

void	ft_draw_pixel(char *img_str, int row, int col, int color)
{
	((int*)img_str)[row * WIN_W + col] = color;
}
