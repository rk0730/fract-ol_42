/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:12:15 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/16 18:17:52 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_mandelbrot(t_complex_num c)
{
	int				max_iter;
	t_complex_num	z;
	int				iter;
	double			tmp;

	max_iter = 1000;
	z.r = 0.0;
	z.i = 0.0;
	iter = 0;
	while (z.r * z.r + z.i * z.i < 4.0 && iter < max_iter)
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = tmp;
		iter++;
	}
	return (iter);
}

int	ft_julia(t_complex_num z, t_complex_num c)
{
	int				max_iter;
	t_complex_num	zn;
	int				iter;
	double			tmp;

	max_iter = 1000;
	zn.r = z.r;
	zn.i = z.i;
	iter = 0;
	while (zn.r * zn.r + zn.i * zn.i < 4.0 && iter < max_iter)
	{
		tmp = zn.r * zn.r - zn.i * zn.i + c.r;
		zn.i = 2.0 * zn.r * zn.i + c.i;
		zn.r = tmp;
		iter++;
	}
	return (iter);
}
