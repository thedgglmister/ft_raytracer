/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:09:09 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 17:25:38 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_free(t_globals *glob)
{
	ft_free_scene(glob->scene);
	ft_free_matrix(glob->cam->transform);
	free(glob->cam);
	mlx_destroy_image(glob->win->mlx, glob->win->img);
	mlx_destroy_window(glob->win->mlx, glob->win->win);
	free(glob->win->mlx);
	free(glob->win);
}

void	ft_free_matrix(t_mat matrix)
{
	int i;

	i = -1;
	while (++i < 4)
		free(matrix[i]);
	free(matrix);
}

void	ft_free_scene(t_scene *scene)
{
	int i;

	i = -1;
	while (++i < scene->light_cnt)
		free(scene->lights[i].type);
	free(scene->lights);
	i = -1;
	while (++i < scene->obj_cnt)
	{
		free(scene->objs[i].type);
		ft_free_matrix(scene->objs[i].transform);
		ft_free_matrix(scene->objs[i].inv_transform);
	}
	free(scene->objs);
	free(scene);
}
