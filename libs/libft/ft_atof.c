/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:58:57 by biremong          #+#    #+#             */
/*   Updated: 2017/05/24 19:31:47 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	char	*trimmed;
	double	result;
	int		sign;
	int		i;
	double	place_value;

	trimmed = ft_strtrim(str);
	sign = (trimmed[0] == '-' ? -1 : 1);
	free(trimmed);
	result = ft_atoi(str);
	if (!(str = ft_strchr(str, '.')))
		return (result);
	str++;
	i = 0;
	place_value = 0.1;
	while (ft_isdigit(str[i]))
	{
		result += (str[i] - '0') * place_value * sign;
		place_value /= 10;
		i++;
	}
	return (result);
}
