/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:23:21 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/13 18:22:36 by kitaoryoma       ###   ########.fr       */
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
	mouse_i = port->i_max - (double)y / HEIGHT * (port->i_max - port->i_min);
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
	t_mlx_info	*mlx_info;

	mlx_info = vars->mlx_info;
	if (!(event == SCROLL_UP || event == SCROLL_DOWN))
		return (0);
	ft_coordinate(event, x, y, vars->viewport_info);
	ft_paint(*vars);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->win, mlx_info->img, 0, 0);
	return (0);
}
