/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:32:40 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/13 17:34:36 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_key_hook(enum e_keycode keycode, t_vars *vars)
{
	printf("key_hook %d\n", keycode);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_display(vars->mlx_info->mlx);
		exit(0);
	}
	if (keycode == KEY_UP){
		double diff = (vars->viewport_info->i_max - vars->viewport_info->i_min)/15;
		vars->viewport_info->i_max += diff;
		vars->viewport_info->i_min += diff;
	}else if (keycode == KEY_DOWN){
		double diff = (vars->viewport_info->i_max - vars->viewport_info->i_min)/15;
		vars->viewport_info->i_max -= diff;
		vars->viewport_info->i_min -= diff;
	}else if (keycode == KEY_LEFT){
		double diff = (vars->viewport_info->r_max - vars->viewport_info->r_min)/15;
		vars->viewport_info->r_max -= diff;
		vars->viewport_info->r_min -= diff;
	}else if (keycode == KEY_RIGHT){
		double diff = (vars->viewport_info->r_max - vars->viewport_info->r_min)/15;
		vars->viewport_info->r_max += diff;
		vars->viewport_info->r_min += diff;
	}
	if (keycode == KEY_SPACE){
		if (vars->frac_type->name == 's')
			vars->frac_type->base_color += 0.15;
		else
			vars->frac_type->base_color += 0.02;
		if (vars->frac_type->base_color > 1.0)
			vars->frac_type->base_color -= 1.0;
	}
	ft_paint(*vars);
	mlx_put_image_to_window(vars->mlx_info->mlx, vars->mlx_info->win, vars->mlx_info->img, 0, 0);
	return (0);
}

int	ft_close(t_mlx *mlx)
{
	ft_printf("close\n");
	mlx_destroy_display(mlx->mlx);
	exit(0);
	return (0);
}
