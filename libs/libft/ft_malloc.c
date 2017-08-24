/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:58:42 by biremong          #+#    #+#             */
/*   Updated: 2017/05/15 15:58:44 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t bytes)
{
	void	*addr;

	addr = malloc(bytes);
	if (!addr)
		ft_crash("Error: Malloc Failed");
	return (addr);
}
