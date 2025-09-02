/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 11:55:56 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 11:55:56 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv))
		return (0);
	if (init_philo(&data, argv) == NULL)
		return (0);
	if (philo_threads(&data) == 1)
	{
		clean_data(&data);
		return (0);
	}
	if (monitor(&data) == 1)
	{
		join_philo_threads(&data);
		clean_data(&data);
		return (0);
	}
	join_philo_threads(&data);
	clean_data(&data);
	return (0);
}
