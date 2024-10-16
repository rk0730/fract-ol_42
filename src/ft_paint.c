/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:28:21 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/16 18:31:14 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static void	ft_put_color(t_vars vars, int iter, int x, int y)
{
	long	color;
	int		pos;
	double	h;

	// 収束した場合は黒
	if (iter == 1000)
		color = (20 << 16) | (20 << 8) | 20;
	else
	{
		// HSV to RGB
		h = iter / 1000.0 + vars.frac_type->base_color;
		// base_color(0.66)がないと赤くなり見にくい
		color = ft_hsv_to_color(h, 1, 1);
	}
	pos = (y * vars.mlx_info->size_line) + (x * (vars.mlx_info->bpp / 8));
	*(unsigned int *)(vars.mlx_info->data_addr + pos) = color;
}

static int	ft__iter(t_vars vars, int x, int y)
{
	t_complex_num	z;
	t_viewport		*viewport;

	viewport = vars.viewport;
	// (0,0)が左上なので、yの値を逆にする
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
			iter = ft__iter(vars, x, y);
			if (iter == -1)
				return ;
			ft_put_color(vars, iter, x, y);
			x++;
		}
		y++;
	}
}
