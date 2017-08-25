/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:34:40 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:48:56 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	main(int ac, char **av)
{
	t_globals	glob;
	int			fd;

	if (ac != 2)
		ft_error("Usage: ./rt file");
	fd = ft_open(av[1]);
	ft_init_window(&glob, fd);
	ft_init_camera(&glob, fd);
	ft_init_scene(&glob, fd);
	ft_close(fd);
	ft_draw_scene(&glob);
	ft_set_hooks(&glob);
	mlx_loop(glob.win->mlx);
	return (0);
}
