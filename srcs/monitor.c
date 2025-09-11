/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 16:20:37 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 16:20:37 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	is_a_philo_dead(t_data *data)
{
	int		i;
	long	time_last_meal;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_time_mtx);
		time_last_meal = get_current_time() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].last_meal_time_mtx);
		if (time_last_meal >= data->time_to_die)
		{
			printf_mutex(data, "died", data->philos[i].id);
			pthread_mutex_lock(&data->run_sim_mtx);
			data->run_sim = 0;
			pthread_mutex_unlock(&data->run_sim_mtx);
			return ;
		}
		i++;
	}
}

int	is_philos_ate_enough(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].meals_eaten_mtx);
		if (data->philos[i].meals_eaten < data->nb_must_eat)
		{
			pthread_mutex_unlock(&data->philos[i].meals_eaten_mtx);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].meals_eaten_mtx);
		i++;
	}
	pthread_mutex_lock(&data->run_sim_mtx);
	data->run_sim = 0;
	pthread_mutex_unlock(&data->run_sim_mtx);
	return (0);
}

int	monitor(t_data *data)
{
	set_start_times(data);
	pthread_mutex_lock(&data->start_sim_mtx);
	if (data->start_sim == 0)
	{
		#include <stdio.h>
		printf("start sim = 0 in monitor");
		pthread_mutex_unlock(&data->start_sim_mtx);
		return (1);
	}
	data->start_sim = 1;
	pthread_mutex_unlock(&data->start_sim_mtx);
	while (is_sim_running(data))
	{
		is_a_philo_dead(data);
		if (is_sim_running(data) && data->nb_must_eat != -1)
			is_philos_ate_enough(data);
		usleep(100);
	}
	return (0);
}
