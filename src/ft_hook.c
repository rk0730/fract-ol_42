/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:32:40 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/23 16:39:46 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static void	ft_key_hook_h1(enum e_keycode keycode, t_vars *vars)
{
	const double	diff = (vars->viewport->i_max - vars->viewport->i_min) / 15;

	if (keycode == KEY_UP)
	{
		vars->viewport->i_max += diff;
		vars->viewport->i_min += diff;
	}
	else if (keycode == KEY_DOWN)
	{
		vars->viewport->i_max -= diff;
		vars->viewport->i_min -= diff;
	}
}

static void	ft_key_hook_h2(enum e_keycode keycode, t_vars *vars)
{
	const double	diff = (vars->viewport->r_max - vars->viewport->r_min) / 15;

	if (keycode == KEY_LEFT)
	{
		vars->viewport->r_max -= diff;
		vars->viewport->r_min -= diff;
	}
	else if (keycode == KEY_RIGHT)
	{
		vars->viewport->r_max += diff;
		vars->viewport->r_min += diff;
	}
}

int	ft_key_hook(enum e_keycode keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		ft_close(vars->mlx_info);
		exit(0);
	}
	if (keycode == KEY_SPACE)
	{
		if (vars->frac_type->name == 's')
			vars->frac_type->base_color += 0.15;
		else
			vars->frac_type->base_color += 0.02;
		if (vars->frac_type->base_color > 1.0)
			vars->frac_type->base_color -= 1.0;
	}
	ft_key_hook_h1(keycode, vars);
	ft_key_hook_h2(keycode, vars);
	ft_paint(*vars);
	mlx_put_image_to_window(vars->mlx_info->mlx, vars->mlx_info->win,
		vars->mlx_info->img, 0, 0);
	// mlx_destroy_image(vars->mlx_info->mlx, vars->mlx_info->img);
	return (0);
}

int	ft_close(t_mlx_info *mlx_info)
{
	// free(mlx_info->data_addr);
	mlx_destroy_image(mlx_info->mlx, mlx_info->img);
	mlx_destroy_window(mlx_info->mlx, mlx_info->win);
	mlx_destroy_display(mlx_info->mlx);
	free(mlx_info->mlx);
	exit(0);
	return (0);
}
