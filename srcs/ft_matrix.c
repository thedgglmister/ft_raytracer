/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:44:54 by biremong          #+#    #+#             */
/*   Updated: 2017/05/15 17:44:56 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mat	ft_new_matrix(void)
{
	t_mat	matrix;
	int		i;

	matrix = (double**)ft_malloc(sizeof(double*) * 4);
	i = 0;
	while (i < 4)
	{
		matrix[i] = (double*)ft_malloc(sizeof(double) * 4);
		ft_bzero(matrix[i], sizeof(double) * 4);
		matrix[i][i] = 1;
		i++;
	}
	return (matrix);
}

t_vec	ft_mat_vec_mult(t_mat m, t_vec u)
{
	t_vec v;

	v.x = m[0][0] * u.x + m[0][1] * u.y + m[0][2] * u.z + m[0][3] * u.w;
	v.y = m[1][0] * u.x + m[1][1] * u.y + m[1][2] * u.z + m[1][3] * u.w;
	v.z = m[2][0] * u.x + m[2][1] * u.y + m[2][2] * u.z + m[2][3] * u.w;
	v.w = m[3][0] * u.x + m[3][1] * u.y + m[3][2] * u.z + m[3][3] * u.w;
	return (v);
}

void	ft_mat_mat_mult(t_mat m1, t_mat m2, t_mat *result)
{
	int		row;
	int		col;
	int		i;
	double	sum;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
		{
			i = -1;
			sum = 0;
			while (++i < 4)
				sum += m1[row][i] * m2[i][col];
			(*result)[row][col] = sum;
		}
	}
}
