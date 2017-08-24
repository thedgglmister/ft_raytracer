/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_corrections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:33:07 by biremong          #+#    #+#             */
/*   Updated: 2017/05/15 17:46:02 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rgb	ft_gamma_correction(t_rgb light, double gamma)
{
	light.r = pow(light.r, (1 / gamma));
	light.g = pow(light.g, (1 / gamma));
	light.b = pow(light.b, (1 / gamma));
	return (light);
}

t_rgb	ft_scale_white(t_rgb light)
{
	double max;

	max = fmax(1, fmax(light.r, fmax(light.g, light.b)));
	light.r /= max;
	light.g /= max;
	light.b /= max;
	return (light);
}

int		ft_rgb_to_int(t_rgb light)
{
	int		r;
	int		g;
	int		b;

	r = round(light.r * 255);
	g = round(light.g * 255);
	b = round(light.b * 255);
	return ((r << 16) + (g << 8) + b);
}

t_rgb	ft_combine_samples(t_rgb samples[SS_CNT])
{
	t_rgb	combined;
	int		i;

	combined.r = 0;
	combined.g = 0;
	combined.b = 0;
	i = -1;
	while (++i < SS_CNT)
	{
		combined.r += samples[i].r;
		combined.g += samples[i].g;
		combined.b += samples[i].b;
	}
	combined.r /= SS_CNT;
	combined.g /= SS_CNT;
	combined.b /= SS_CNT;
	return (combined);
}
