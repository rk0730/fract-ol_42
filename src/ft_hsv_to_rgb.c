
#include "ft_fractol.h"

void ft_hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b)
{
	float c = v * s;
	float x = c * (1 - abs((int)(h * 6) % 2 - 1));
	float m = v - c;
	float r_prime, g_prime, b_prime;

	if (h < 1.0 / 6.0)
	{
		r_prime = c;
		g_prime = x;
		b_prime = 0;
	}
	else if (h < 2.0 / 6.0)
	{
		r_prime = x;
		g_prime = c;
		b_prime = 0;
	}
	else if (h < 3.0 / 6.0)
	{
		r_prime = 0;
		g_prime = c;
		b_prime = x;
	}
	else if (h < 4.0 / 6.0)
	{
		r_prime = 0;
		g_prime = x;
		b_prime = c;
	}
	else if (h < 5.0 / 6.0)
	{
		r_prime = x;
		g_prime = 0;
		b_prime = c;
	}
	else
	{
		r_prime = c;
		g_prime = 0;
		b_prime = x;
	}

	*r = (r_prime + m) * 255;
	*g = (g_prime + m) * 255;
	*b = (b_prime + m) * 255;
}
