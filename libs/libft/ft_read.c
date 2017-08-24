/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 19:32:04 by biremong          #+#    #+#             */
/*   Updated: 2017/01/26 19:36:14 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_read(int fd, char *buf, int len)
{
	int	ret;

	if ((ret = read(fd, buf, len)) == -1)
		ft_error("Error: Read Failed");
	return (ret);
}
