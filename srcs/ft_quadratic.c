/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quadratic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:36:48 by biremong          #+#    #+#             */
/*   Updated: 2017/05/24 17:45:03 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	*ft_solve_quadratic(double a, double b, double c)
{
	double	calc1;
	double	calc2;
	double	*t;

	t = (double*)ft_malloc(sizeof(double) * 2);
	calc1 = sqrt(b * b - 4 * a * c);
	calc2 = 0.5 / a;
	t[0] = (-b + calc1) * calc2;
	t[1] = (-b - calc1) * calc2;
	return (t);
}
