#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

// マンデルブロ集合の描画

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

int	mandelbrot(double real, double imag)
{
	int		max_iter;
	double	zr = 0.0, zi;
	int		iter;
	double	tmp;

	max_iter = 1000;
	zr = 0.0, zi = 0.0;
	iter = 0;
	while (zr * zr + zi * zi < 4.0 && iter < max_iter)
	{
		tmp = zr * zr - zi * zi + real;
		zi = 2.0 * zr * zi + imag;
		zr = tmp;
		iter++;
	}
	return (iter);
}

void	draw_mandelbrot(t_mlx *mlx)
{
	double	real;
	double	imag;
	int		iter;
	int		color;
	int		pos;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			real = (x - WIDTH / 2.0) * 1.0 / WIDTH;
			imag = (y - HEIGHT / 2.0) * 1.0 / HEIGHT;
			iter = mandelbrot(real, imag);
			color = iter * 255 / 1000;
			color = (color << 16) | (color << 8) | color;
			pos = (y * mlx->size_line) + (x * (mlx->bpp / 8));
			*(unsigned int *)(mlx->data_addr + pos) = color;
		}
	}
}

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Mandelbrot");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.data_addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line,
			&mlx.endian);
	draw_mandelbrot(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
