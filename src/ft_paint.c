/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:28:21 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/23 13:44:35 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static void	ft_put_color(t_vars vars, int iter, int x, int y)
{
	long	color;
	int		pos;
	double	h;

	if (iter == 100)
		color = (20 << 16) | (20 << 8) | 20;
	else
	{
		h = iter / 100.0 + vars.frac_type->base_color;
		color = ft_hsv_to_color(h, 1, 1);
	}
	pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
	*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
}

static int	ft_iter(t_vars vars, int x, int y)
{
	t_complex_num	z;
	t_viewport		*viewport;

	viewport = vars.viewport;
	z.r = viewport->r_min + (x * (viewport->r_max - viewport->r_min) / WIDTH);
	z.i = viewport->i_max - (y * (viewport->i_max - viewport->i_min) / HEIGHT);
	if (vars.frac_type->name == 'm')
		return (ft_mandelbrot(z));
	else if (vars.frac_type->name == 'j')
		return (ft_julia(z, *(vars.frac_type->complex)));
	else
	{
		ft_printf("Invalid fraction type\n");
		return (-1);
	}
}

void	ft_paint(t_vars vars)
{
	int	x;
	int	y;
	int	iter;

	if (vars.frac_type->name == 's')
	{
		ft_sierpinski(vars);
		return ;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			iter = ft_iter(vars, x, y);
			if (iter == -1)
				return ;
			ft_put_color(vars, iter, x, y);
			x++;
		}
		y++;
	}
}
