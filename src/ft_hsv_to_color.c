/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsv_to_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:27:22 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/16 18:27:24 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_help(float rgb_prime[3], float h, float c, float x)
{
	if (h < 1.0 / 6.0)
	{
		rgb_prime[0] = c;
		rgb_prime[1] = x;
		rgb_prime[2] = 0;
	}
	else if (1.0 / 6.0 <= h && h < 2.0 / 6.0)
	{
		rgb_prime[0] = x;
		rgb_prime[1] = c;
		rgb_prime[2] = 0;
	}
	else if (2.0 / 6.0 <= h && h < 3.0 / 6.0)
	{
		rgb_prime[0] = 0;
		rgb_prime[1] = c;
		rgb_prime[2] = x;
	}
	else if (3.0 / 6.0 <= h && h < 4.0 / 6.0)
	{
		rgb_prime[0] = 0;
		rgb_prime[1] = x;
		rgb_prime[2] = c;
	}
}

long	ft_hsv_to_color(float h, float s, float v)
{
	const float	c = v * s;
	const float	x = c * (1 - abs((int)(h * 6) % 2 - 1));
	const float	m = v - c;
	float		rgb_prime[3];

	ft_help(rgb_prime, h, c, x);
	if (4.0 / 6.0 <= h && h < 5.0 / 6.0)
	{
		rgb_prime[0] = x;
		rgb_prime[1] = 0;
		rgb_prime[2] = c;
	}
	else if (5.0 / 6.0 <= h)
	{
		rgb_prime[0] = c;
		rgb_prime[1] = 0;
		rgb_prime[2] = x;
	}
	return ((long)((rgb_prime[0] + m) * 255) << 16 | (long)((rgb_prime[1] + m)
			* 255) << 8 | (long)((rgb_prime[2] + m) * 255));
}
