/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:12:15 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/12 16:48:07 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_mandelbrot(t_complex_num c)
{
	int		max_iter;
	double	zr, zi;
	int		iter;
	double	tmp;

	max_iter = 1000;
	zr = 0.0;
	zi = 0.0;
	iter = 0;
	while (zr * zr + zi * zi < 4.0 && iter < max_iter)
	{
		tmp = zr * zr - zi * zi + c.r;
		zi = 2.0 * zr * zi + c.i;
		zr = tmp;
		iter++;
	}
	return (iter);
}

int	ft_julia(t_complex_num z, t_complex_num c)
{
	int	max_iter;
	double    zr, zi;
	int    iter;
	double    tmp;

	max_iter = 1000;
	zr = z.r;
	zi = z.i;
	iter = 0;
	while (zr * zr + zi * zi < 4.0 && iter < max_iter)
	{
		tmp = zr * zr - zi * zi + c.r;
		zi = 2.0 * zr * zi + c.i;
		zr = tmp;
		iter++;
	}
	return (iter);
}
