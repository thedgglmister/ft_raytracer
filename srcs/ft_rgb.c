/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:37:58 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 17:59:41 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_rgb	ft_rgb_add(t_rgb rgb1, t_rgb rgb2)
{
	rgb1.r += rgb2.r;
	rgb1.g += rgb2.g;
	rgb1.b += rgb2.b;
	return (rgb1);
}

t_rgb	ft_rgb_mult(t_rgb rgb1, t_rgb rgb2)
{
	rgb1.r *= rgb2.r;
	rgb1.g *= rgb2.g;
	rgb1.b *= rgb2.b;
	return (rgb1);
}

t_rgb	ft_rgb_scale(t_rgb rgb, double s)
{
	rgb.r *= s;
	rgb.g *= s;
	rgb.b *= s;
	return (rgb);
}
