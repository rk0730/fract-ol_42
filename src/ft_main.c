/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:39:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/12 17:18:34 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

// int	mouse_scroll(int button, int x, int y, t_mlx *mlx)
// {
// 	if (mlx->win == NULL)
// 		printf("");
// 	if (button == SCROLL_UP)
// 	{
// 		printf("scroll up   x: %d y: %d\n", x, y);
// 	}
// 	else if (button == SCROLL_DOWN)
// 	{
// 		printf("scroll down x: %d y: %d\n", x, y);
// 	}
// 	return (0);
// }

static void	ft_init(t_vars *vars, char *title)
{
	vars->viewport_info->r_max = 2.0;
	vars->viewport_info->r_min = -2.0;
	vars->viewport_info->i_max = 2.0;
	vars->viewport_info->i_min = -2.0;
	vars->mlx_info->mlx = mlx_init();
	vars->mlx_info->win = mlx_new_window(vars->mlx_info->mlx, WIDTH, HEIGHT, title);
	vars->mlx_info->img = mlx_new_image(vars->mlx_info->mlx, WIDTH, HEIGHT);
	vars->mlx_info->data_addr = mlx_get_data_addr(vars->mlx_info->img,
		&(vars->mlx_info->bpp), &(vars->mlx_info->size_line),
		&(vars->mlx_info->endian));
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_vars	vars;
	t_mlx	mlx;
	t_viewport	viewport;
	t_frac_type	frac_type;
	t_complex_num complex_num;

	vars.mlx_info = &mlx;
	vars.viewport_info = &viewport;
	vars.frac_type = &frac_type;
	frac_type.complex = &complex_num;
	if (ft_arg(argc, argv, &(complex_num.r), &(complex_num.i)) == 0)
	{
		//マンデルブロ集合
		frac_type.name = 'm';
		ft_init(&vars, "Mandelbrot");
		ft_paint(vars);
	}
	else if (ft_arg(argc, argv, &(complex_num.r), &(complex_num.i)) == 1)
	{
		//ジュリア集合
		frac_type.name = 'j';
		ft_init(&vars, "Julia");
		ft_paint(vars);
		// ft_julia(&mlx, t_viewport *viewport, double r, double i);
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_mouse_hook(mlx.win, ft_zoom, &vars);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
