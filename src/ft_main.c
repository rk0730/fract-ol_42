/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:39:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/20 20:34:43 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft.h"
#include "ft_printf.h"
#include "mlx.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
}			t_mlx;

// enum e_event
// {
// 	ON_KEYDOWN = 2,
// 	ON_KEYUP = 3,
// 	ON_MOUSEDOWN = 4,
// 	ON_MOUSEUP = 5,
// 	ON_MOUSEMOVE = 6,
// 	ON_EXPOSE = 12,
// 	ON_DESTROY = 17
// };

enum e_keycode
{
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_ESC = 53
};

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}


int	main(int argc, char **argv)
{
	if (argc == 0)
		ft_printf("%s\n", argv[0]);

	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "rkitao");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.data_addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line, &mlx.endian);
	for (int x = 300; x < 500; x++)
	{
		for (int y = 200; y < 400; y++)
		{
			char *dst;
			dst = mlx.data_addr + (y * mlx.size_line + x * (mlx.bpp / 8));
			*(unsigned int *)dst = 0xff69b4;
		}
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}