/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:27:41 by biremong          #+#    #+#             */
/*   Updated: 2017/05/23 14:59:20 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//finite solids
//direct light vs indirect light?

void	ft_init_window(t_globals *glob, int fd)
{
	char	*scene_name;

	glob->win = (t_window*)ft_malloc(sizeof(t_window));
	glob->win->mlx = mlx_init();
	scene_name = ft_parse_str(fd, "SCENE NAME:");
	glob->win->win = mlx_new_window(glob->win->mlx, WIN_W, WIN_H, scene_name);
	free(scene_name);
	glob->win->img = mlx_new_image(glob->win->mlx, WIN_W, WIN_H);
	glob->win->img_str = mlx_get_data_addr(glob->win->img,
									&glob->win->bits_per_pix,
									&glob->win->bytes_per_row,
									&glob->win->endian);
}

void	ft_init_camera(t_globals *glob, int fd)
{
	t_camera	*cam;
	t_vec		cam_dir;
	double		x_rads;
	double		y_rads;
	double		z_rads;

	glob->cam = (t_camera*)ft_malloc(sizeof(t_camera));
	cam = glob->cam;
	ft_parse_cam_info(fd, cam);
	cam->ray.o = (t_vec){0, 0, 0, 1};
	cam->ray.d = (t_vec){0, 0, -1, 0};
	cam->plane_dist = WIN_W / (2 * tan(cam->fov / 2));
	cam_dir = ft_vec_subtract(cam->target, cam->translation);
	x_rads = asin(cam_dir.y / ft_magnitude(cam_dir));
	y_rads = atan2(-cam_dir.x, -cam_dir.z);
	z_rads = cam->roll;
	cam->transform = ft_get_transform(cam->translation, x_rads, y_rads, z_rads);
}

void	ft_init_scene(t_globals *glob, int fd)
{
	t_scene	*scene;
	int		i;
	int		light_cnt;


	glob->scene = (t_scene*)ft_malloc(sizeof(t_scene));
	scene = glob->scene;
	ft_skip_empty_line(fd);
	light_cnt = ft_parse_val(fd, "LIGHT COUNT:");
	scene->light_cnt = light_cnt;
	scene->lights = (t_light*)ft_malloc(sizeof(t_light) * light_cnt);
	i = -1;
	while (++i < scene->light_cnt)
		ft_parse_light_info(fd, scene->lights + i);
	ft_skip_empty_line(fd);
	scene->amb_emission = ft_calc_amb_rgb(fd, scene->lights, scene->light_cnt);
	ft_skip_empty_line(fd);
	scene->obj_cnt = ft_parse_val(fd, "OBJECT COUNT:");
	scene->objs = (t_obj*)ft_malloc(sizeof(t_obj) * scene->obj_cnt);
	i = -1;
	while (++i < scene->obj_cnt)
		ft_parse_obj_info(fd, scene->objs + i);
}
