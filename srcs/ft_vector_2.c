/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:38:16 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 17:24:28 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	ft_cross_product(t_vec u, t_vec v)
{
	t_vec cross_prod;

	cross_prod.x = u.y * v.z - u.z * v.y;
	cross_prod.y = u.z * v.x - u.x * v.z;
	cross_prod.z = u.x * v.y - u.y * v.x;
	return (cross_prod);
}

t_vec	ft_ortho_vector(t_vec u)
{
	t_vec ortho;

	if (u.x == 0)
	{
		ortho.x = 1;
		ortho.y = 0;
	}
	else
	{
		ortho.y = 1;
		ortho.x = -u.y / u.x;
	}
	ortho.z = 0;
	return (ortho);
}

t_vec	ft_vec_add(t_vec v, t_vec u)
{
	v.x += u.x;
	v.y += u.y;
	v.z += u.z;
	v.w += u.w;
	return (v);
}

t_vec	ft_vec_subtract(t_vec v, t_vec u)
{
	v.x -= u.x;
	v.y -= u.y;
	v.z -= u.z;
	v.w -= v.w;
	return (v);
}

t_vec	ft_vec_scale(t_vec v, double scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return (v);
}
