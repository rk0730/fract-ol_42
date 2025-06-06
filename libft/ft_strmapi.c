/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:16:05 by rkitao            #+#    #+#             */
/*   Updated: 2024/04/20 20:24:02 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	result = ft_strdup(s);
	if (!result)
		return (NULL);
	len = (unsigned int)ft_strlen(s);
	while (i < len)
	{
		result[i] = f(i, result[i]);
		i++;
	}
	return (result);
}
