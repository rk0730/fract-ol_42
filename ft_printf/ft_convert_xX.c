/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_xX.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:16:27 by 1652952399        #+#    #+#             */
/*   Updated: 2024/06/06 17:04:22 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert_x_h(int fd, unsigned int num, int res, int flag)
{
	int		tmp;
	char	*str;

	if (flag)
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	if (res == -1)
		return (-1);
	if (num >= 16)
	{
		tmp = ft_convert_x_h(fd, num / 16, res, flag);
		if (tmp == -1)
			return (-1);
		else
			res += tmp;
	}
	tmp = ft_convert_c(fd, str[num % 16]);
	if (tmp == -1)
		return (-1);
	else
		return (res + tmp);
}

int	ft_convert_x(int fd, unsigned int num)
{
	return (ft_convert_x_h(fd, num, 0, 1));
}

int	ft_convert_x2(int fd, unsigned int num)
{
	return (ft_convert_x_h(fd, num, 0, 0));
}
