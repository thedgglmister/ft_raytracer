/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:37:36 by biremong          #+#    #+#             */
/*   Updated: 2017/08/24 17:23:54 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mat	ft_get_transform(t_vec t, double x_rads, double y_rads, double z_rads)
{
	t_mat	transform;
	t_mat	rx_matrix;
	t_mat	ry_matrix;
	t_mat	rz_matrix;

	transform = ft_new_matrix();
	rx_matrix = ft_get_rx_matrix(x_rads);
	ry_matrix = ft_get_ry_matrix(y_rads);
	rz_matrix = ft_get_rz_matrix(z_rads);
	ft_mat_mat_mult(ry_matrix, rx_matrix, &transform);
	ft_mat_mat_mult(transform, rz_matrix, &transform);
	transform[0][3] = t.x;
	transform[1][3] = t.y;
	transform[2][3] = t.z;
	ft_free_matrix(rx_matrix);
	ft_free_matrix(ry_matrix);
	ft_free_matrix(rz_matrix);
	return (transform);
}

t_mat	ft_inverse(t_mat transform)
{
	t_mat	inv_transform;
	t_vec	u;
	t_vec	v;
	t_vec	w;
	t_vec	t;

	inv_transform = ft_new_matrix();
	u = (t_vec){transform[0][0], transform[1][0], transform[2][0], 0};
	v = (t_vec){transform[0][1], transform[1][1], transform[2][1], 0};
	w = (t_vec){transform[0][2], transform[1][2], transform[2][2], 0};
	t = (t_vec){transform[0][3], transform[1][3], transform[2][3], 0};
	inv_transform[0][0] = u.x;
	inv_transform[0][1] = u.y;
	inv_transform[0][2] = u.z;
	inv_transform[0][3] = -ft_dot_product(u, t);
	inv_transform[1][0] = v.x;
	inv_transform[1][1] = v.y;
	inv_transform[1][2] = v.z;
	inv_transform[1][3] = -ft_dot_product(v, t);
	inv_transform[2][0] = w.x;
	inv_transform[2][1] = w.y;
	inv_transform[2][2] = w.z;
	inv_transform[2][3] = -ft_dot_product(w, t);
	return (inv_transform);
}

t_mat	ft_get_rx_matrix(double x_rads)
{
	t_mat	rx_matrix;

	rx_matrix = ft_new_matrix();
	rx_matrix[1][1] = cos(x_rads);
	rx_matrix[1][2] = -sin(x_rads);
	rx_matrix[2][1] = sin(x_rads);
	rx_matrix[2][2] = cos(x_rads);
	return (rx_matrix);
}

t_mat	ft_get_ry_matrix(double y_rads)
{
	t_mat	ry_matrix;

	ry_matrix = ft_new_matrix();
	ry_matrix[0][0] = cos(y_rads);
	ry_matrix[0][2] = sin(y_rads);
	ry_matrix[2][0] = -sin(y_rads);
	ry_matrix[2][2] = cos(y_rads);
	return (ry_matrix);
}

t_mat	ft_get_rz_matrix(double z_rads)
{
	t_mat	rz_matrix;

	rz_matrix = ft_new_matrix();
	rz_matrix[0][0] = cos(z_rads);
	rz_matrix[0][1] = -sin(z_rads);
	rz_matrix[1][0] = sin(z_rads);
	rz_matrix[1][1] = cos(z_rads);
	return (rz_matrix);
}
