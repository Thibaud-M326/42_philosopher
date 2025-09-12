/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-01 19:00:57 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-01 19:00:57 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

void	print_usage(void)
{
	printf("Usage: ");
	printf("./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return ;
}

void	printf_mutex_ate_enough(t_data *data)
{
	long	cur_t;

	cur_t = get_current_time();
	pthread_mutex_lock(&data->print);
	printf("%ld philos have all eaten %d times\n", cur_t, data->nb_must_eat);
	pthread_mutex_unlock(&data->print);
	return ;
}

void	printf_mutex(t_data *data, char *msg, int id_philo)
{
	long	sim_time;

	if (is_sim_running(data))
	{
		pthread_mutex_lock(&data->print);
		if (is_sim_running(data))
		{
			pthread_mutex_lock(&data->start_time_mtx);
			sim_time = get_current_time() - data->start_time;
			pthread_mutex_unlock(&data->start_time_mtx);
			printf("%ld %d %s\n", sim_time, id_philo, msg);
		}
		pthread_mutex_unlock(&data->print);
	}
	return ;
}
