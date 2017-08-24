/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_scene_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:35:34 by biremong          #+#    #+#             */
/*   Updated: 2017/05/24 19:29:34 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_skip_empty_line(int fd)
{
	char *buffer;

	if (!ft_gnl(fd, &buffer))
		ft_error("Invalid End of File");
	if (*buffer)
		ft_error("Scene File Missing An Empty Line");
	free(buffer);
}

char	*ft_parse_str(int fd, char *category)
{
	int		ret;
	char	*buffer;
	char	*str;
	
	ret = ft_gnl(fd, &buffer);
	if (!ret)
		ft_error("Invalid End of File");
	else if (ret < 0)
		ft_error("Error Reading File");
	if (!ft_strnstr(buffer, category, ft_strlen(category)))
		ft_error("Format Error");//specify more detail, like %s the line?
	str = ft_strtrim(ft_strchr(buffer, ':') + 1);
	free(buffer);
	return (str);
}

t_vec	ft_parse_vec(int fd, char *category)
{
	char	*str;
	char	**args;
	t_vec	v;

	str = ft_parse_str(fd, category);
	if (str[0] != '(' || str[ft_strlen(str) - 1] != ')')
		ft_error("Format Error");
	str[ft_strlen(str) - 1] = '\0';
	args = ft_strsplit(str + 1, ',');
	free(str);
	if (ft_arrlen2(args) != 3)
		ft_error("Format Error");
	v = (t_vec){ft_atof(args[0]), ft_atof(args[1]), ft_atof(args[2]), 1};
	ft_arrdel2(args);
	return (v);
}

double	ft_parse_val(int fd, char *category)
{
	char	*str;
	double	value;

	str = ft_parse_str(fd, category);
	value = ft_atof(str);
	free(str);
	return (value);
}

t_rgb	ft_parse_rgb(int fd, char *category)
{
	char	*str;
	char	**args;
	t_rgb	rgb;

	str = ft_parse_str(fd, category);
	if (str[0] != '(' || str[ft_strlen(str) - 1] != ')')
		ft_error("Format Error");
	str[ft_strlen(str) - 1] = '\0';
	args = ft_strsplit(str + 1, ',');
	free(str);
	if (ft_arrlen2(args) != 3)
		ft_error("Format Error");
	rgb = (t_rgb){ft_atof(args[0]), ft_atof(args[1]), ft_atof(args[2])};
	ft_arrdel2(args);
	return (rgb);
}


