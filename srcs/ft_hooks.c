/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:23:15 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 20:59:35 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_set_hooks(t_globals *glob)
{
	mlx_hook(glob->win->win, 17, 0, ft_on_exit, glob);
	mlx_hook(glob->win->win, 2, 0, ft_on_keypress, glob);
}

int		ft_on_keypress(int keycode, void *param)
{
	if (keycode == 53)
	{
		ft_free((t_globals*)param);
		exit(0);
	}
	return (0);
}

int		ft_on_exit(void *param)
{
	ft_free((t_globals*)param);
	exit(0);
	return (0);
}
