/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 19:32:04 by biremong          #+#    #+#             */
/*   Updated: 2017/01/26 19:33:50 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_open(char *file_name)
{
	int	fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_error("Error: Open Failed");
	return (fd);
}
