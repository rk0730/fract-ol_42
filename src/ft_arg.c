/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:22:30 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/23 18:04:16 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static double	ft_atof_h1(char **str_p, int *sign, double *result)
{
	char	*point;

	while (**str_p == ' ' || (9 <= **str_p && **str_p <= 13))
	{
		(*str_p)++;
	}
	if (**str_p == '-')
	{
		*sign = -1;
		(*str_p)++;
	}
	point = *str_p;
	while (ft_isdigit(**str_p))
	{
		*result = *result * 10.0 + (**str_p - '0');
		(*str_p)++;
	}
	if (*str_p == point)
		return (NAN);
	return (0);
}

static double	ft_atof_h2(char **str_p, double *fraction, double *divisor)
{
	int		fraction_flag;
	char	*point;

	fraction_flag = 0;
	if (**str_p == '.')
	{
		(*str_p)++;
		fraction_flag = 1;
	}
	if (fraction_flag)
	{
		point = (*str_p);
		while (ft_isdigit(**str_p))
		{
			*fraction = *fraction * 10.0 + (**str_p - '0');
			*divisor *= 10.0;
			(*str_p)++;
		}
		if (*str_p == point)
			return (NAN);
	}
	return (0);
}

static double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	double	divisor;
	int		sign;

	result = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	sign = 1;
	if (isnan(ft_atof_h1(&str, &sign, &result)))
		return (NAN);
	if (isnan(ft_atof_h2(&str, &fraction, &divisor)))
		return (NAN);
	result += fraction / divisor;
	return (result * sign);
}

static void	ft_arg_h(int argc, char **argv, t_complex_num *complex_num)
{
	if (argc < 4)
	{
		ft_printf("Usage: ./fractol [m/j (double)x (double)y/s]\n");
		exit(1);
	}
	complex_num->r = ft_atof(argv[2]);
	complex_num->i = ft_atof(argv[3]);
	if (isnan(complex_num->r) || isnan(complex_num->i))
	{
		ft_printf("Invalid argument\n");
		exit(1);
	}
}

int	ft_arg(int argc, char **argv, t_complex_num *complex_num)
{
	if (argc < 2)
	{
		ft_printf("Usage: ./fractol [m/j (double)x (double)y/s]\n");
		exit(1);
	}
	if (argv[1][0] == 'm')
		return (0);
	if (argv[1][0] == 's')
		return (2);
	if (argv[1][0] == 'j')
	{
		ft_arg_h(argc, argv, complex_num);
		return (1);
	}
	ft_printf("Usage: ./fractol [m/j (double)x (double)y/s]\n");
	exit(1);
}
