/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-30 23:52:35 by thmaitre          #+#    #+#             */
/*   Updated: 2025-07-30 23:52:35 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if (c == '+' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_only_one_plus(char *str_av)
{
	int	i;

	i = 1;
	while (str_av[i])
	{
		if (i != 0 && str_av[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	is_only_zero(char *str_av)
{
	int	i;

	i = 0;
	while (str_av[i])
	{
		if (str_av[i] >= '1' && str_av[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_pos_num(char *str_av)
{
	int	i;

	i = 0;
	if (!is_only_one_plus(str_av))
		return (0);
	if (is_only_zero(str_av))
		return (0);
	while (str_av[i])
	{
		if (!is_digit(str_av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	if (ac < 5 || ac > 6)
	{
		print_usage();
		return (0);
	}
	while (++i < ac)
	{
		if (!is_pos_num(av[i]))
		{
			print_usage();
			return (0);
		}
		ft_atol(av[i], &err);
		if (err != 0)
		{
			print_usage();
			return (0);
		}
	}
	return (1);
}
