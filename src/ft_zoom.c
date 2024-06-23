/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:23:21 by rkitao            #+#    #+#             */
/*   Updated: 2024/06/23 15:02:46 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_coordinate(int event, int x, int y, t_viewport *port)
{
	double	new_r_range;
	double	new_i_range;
	double	mouse_r;
	double	mouse_i;
	double	ratio;

	mouse_r = (double)x / WIDTH * (port->r_max - port->r_min) + port->r_min;
	mouse_i = (double)y / HEIGHT * (port->i_max - port->i_min) + port->i_min;
	if (event == SCROLL_UP)
	{
		new_r_range = (port->r_max - port->r_min) / 1.25;
		new_i_range = (port->i_max - port->i_min) / 1.25;
	}
	else
	{
		new_r_range = (port->r_max - port->r_min) * 1.25;
		new_i_range = (port->i_max - port->i_min) * 1.25;
	}
	ratio = (mouse_r - port->r_min) / (port->r_max - port->r_min);
	port->r_max = mouse_r + new_r_range * (1 - ratio);
	port->r_min = mouse_r - new_r_range * ratio;
	ratio = (mouse_i - port->i_min) / (port->i_max - port->i_min);
	port->i_max = mouse_i + new_i_range * (1 - ratio);
	port->i_min = mouse_i - new_i_range * ratio;
}


int	ft_zoom(int event, int x, int y, t_vars *vars)
{
	t_mlx		*mlx;
	// t_viewport	*viewport;

	mlx = vars->mlx_info;
	if (!(event == SCROLL_UP || event == SCROLL_DOWN))
		return (0);
	ft_coordinate(event, x, y, vars->viewport_info);
	ft_mandelbrot(mlx, vars->viewport_info);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
