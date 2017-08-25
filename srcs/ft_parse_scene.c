/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:36:12 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:50:13 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_parse_cam_info(int fd, t_camera *cam)
{
	ft_skip_empty_line(fd);
	cam->translation = ft_parse_vec(fd, "CAMERA POSITION:");
	cam->target = ft_parse_vec(fd, "CAMERA TARGET:");
	cam->roll = 0;//TO_RAD(ft_parse_val(fd, "CAMERA ROLL:"));
	cam->fov = TO_RAD(ft_parse_val(fd, "CAMERA FOV:"));
}

void	ft_parse_light_info(int fd, t_light *light)
{
	ft_skip_empty_line(fd);
	light->type = ft_parse_str(fd, "LIGHT:");
	if (ft_strequ(light->type, "POINT"))
		light->pos = ft_parse_vec(fd, "\tPOSITION:");
	else if (ft_strequ(light->type, "PARALLEL"))
	{
		light->dir = ft_parse_vec(fd, "\tDIRECTION:");
		light->dir.w = 0;
		ft_normalize(&(light->dir));
	}
	else
		ft_error("Invalid Light Type");
	light->emission = ft_parse_rgb(fd, "\tEMISSION:");//limit?
}

t_rgb	ft_calc_amb_rgb(int fd, t_light *lights, int light_cnt)
{
	int		i;
	double	amb_k;
	t_rgb	total;

	total = (t_rgb){0, 0, 0};
	i = -1;
	while (++i < light_cnt)
		total = ft_rgb_add(total, lights[i].emission);
	amb_k = ft_parse_val(fd, "AMBIENT LIGHT:");
	total = ft_rgb_scale(total, amb_k / light_cnt);
	return (total);
}

void	ft_parse_obj_info(int fd, t_obj *obj)
{
	ft_skip_empty_line(fd);
	obj->type = ft_parse_str(fd, "OBJECT:");
	ft_validate_obj_type(obj->type);
	obj->translation = ft_parse_vec(fd, "\tCENTER:");
	obj->scalar = ft_parse_val(fd, "\tSCALAR:");//limit?
	obj->y_rads = TO_RAD(ft_parse_val(fd, "\tYAW:"));
	obj->x_rads = TO_RAD(ft_parse_val(fd, "\tPITCH:"));
	obj->z_rads = 0;//TO_RAD(ft_parse_val(fd, "\tROLL:"));
	ft_parse_limits(fd, obj->min_lim, obj->max_lim);
	obj->diffusion = ft_parse_rgb(fd, "\tDIFFUSION:"); //limit?
	obj->gloss = ft_parse_val(fd, "\tGLOSS:");//limit?
	obj->phong_exp = ft_parse_val(fd, "\tPHONG EXP:");//limit?
	obj->k_refl = ft_parse_val(fd, "\tREFLECTION:"); //limit?
	obj->k_refr = ft_parse_val(fd, "\tREFRACTION:"); //limit?
	obj->iof = ft_parse_val(fd, "\tIOF:");//limt?
	obj->transform = ft_get_transform(obj->translation,
										obj->x_rads,
										obj->y_rads,
										obj->z_rads);
	obj->inv_transform = ft_inverse(obj->transform);
}

void	ft_parse_limits(int fd, double min_lim[3], double max_lim[3])
{
	char	*str[2];
	char	**args[2];
	int		i;

	str[0] = ft_parse_str(fd, "\tMIN LIMITS:");
	str[1] = ft_parse_str(fd, "\tMAX LIMITS:");
	if (str[0][0] != '(' || str[0][ft_strlen(str[0]) - 1] != ')'
			|| str[1][0] != '(' || str[1][ft_strlen(str[1]) - 1] != ')')
		ft_error("Format Error");
	str[0][ft_strlen(str[0]) - 1] = '\0';
	str[1][ft_strlen(str[1]) - 1] = '\0';
	args[0] = ft_strsplit(str[0] + 1, ',');
	args[1] = ft_strsplit(str[1] + 1, ',');
	if (ft_arrlen2(args[0]) != 3 || ft_arrlen2(args[1]) != 3)
		ft_error("Format Error");
	free(str[0]);
	free(str[1]);
	i = -1;
	while (++i < 3)
	{
		min_lim[i] = (ft_strchr(args[0][i], '~') ? INFINITY : ft_atof(args[0][i]));
		max_lim[i] = (ft_strchr(args[1][i], '~') ? INFINITY : ft_atof(args[1][i]));
	}
	ft_arrdel2(args[0]);
	ft_arrdel2(args[1]);
}

void	ft_validate_obj_type(char *type)
{
	if (ft_strequ(type, "SPHERE"))
		return ;
	else if (ft_strequ(type, "PLANE"))
		return ;
	else if (ft_strequ(type, "CYLINDER"))
		return ;
	else if (ft_strequ(type, "CONE"))
		return ;
	else if (ft_strequ(type, "PARABALOID"))
		return ;
	else
		ft_error("Invalid Object Type");
}
