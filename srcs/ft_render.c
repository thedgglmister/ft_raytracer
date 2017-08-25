/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:08:48 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:52:57 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_scene(t_globals *glob)
{
	pthread_t	threads[THREAD_CNT];
	t_param		thread_params[THREAD_CNT];
	int			row;
	int			col;
	int			i;

	row = -1;
	while (++row < WIN_H)
	{
		col = -1;
		while (col < WIN_W)
		{
			i = -1;
			while (++i < THREAD_CNT && ++col < WIN_W)
			{
				thread_params[i] = (t_param) {row, col, glob};
				pthread_create(&threads[i], NULL, &ft_render_pixel, &thread_params[i]);
			}
			i = -1;
			while (++i < THREAD_CNT)
				pthread_join(threads[i], NULL);
		}
	}
	mlx_put_image_to_window(glob->win->mlx, glob->win->win, glob->win->img, 0, 0);
}

void	*ft_render_pixel(void *param)
{
	t_param *params;
	t_ray	ray;
	int		i;
	double	rnd[2];
	t_rgb	samples[SS_CNT];

	params = (t_param*)param;
	ray.o = params->glob->cam->origin_img;
	i = -1;
	while (++i < SS_CNT)
	{
		rnd[0] = ((double)rand() / (double)RAND_MAX) / sqrt(SS_CNT);
		rnd[1] = ((double)rand() / (double)RAND_MAX) / sqrt(SS_CNT);
		ray.d = (t_vec)
				{params->col - WIN_W * 0.5 + (i % (int)sqrt(SS_CNT)) * 0.5 + rnd[0],
				WIN_H * 0.5 - params->row - (i / sqrt(SS_CNT)) * 0.5 - rnd[1],
				-params->glob->cam->plane_dist,
				0};
		ray.d = ft_mat_vec_mult(params->glob->cam->transform, ray.d);
		ft_normalize(&ray.d);
		samples[i] = ft_ray_trace(ray, params->glob->scene, 0);
	}
	ft_draw_pixel(params->glob->win->img_str, params->row, params->col, samples);
	return (NULL);
}

void	ft_draw_pixel(char *img_str, int row, int col, t_rgb *samples)
{
	t_rgb color;

	color = ft_combine_samples(samples);
	color = ft_scale_white(color);
	color = ft_gamma_correction(color, 2.2);
	((int*)img_str)[row * WIN_W + col] = ft_rgb_to_int(color);
}
