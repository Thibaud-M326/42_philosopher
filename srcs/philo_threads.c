/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 15:52:00 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 15:52:00 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start_sim_mtx);
	while (i < data->nb_philo)
	{
		if (pthread_create(
				&data->philos[i].philo, NULL,
				&philo_routine, &data->philos[i]) != 0)
		{
			data->start_sim = 0;
			pthread_mutex_unlock(&data->start_sim_mtx);
			while (i >= 0)
			{
				pthread_join(data->philos[i].philo, NULL);
				i--;
			}
			return (1);
		}
		i++;
	}
	data->start_sim = 1;
	return (0);
}

int	create_one_philo_thread(t_data *data)
{
	pthread_mutex_lock(&data->start_sim_mtx);
	if (pthread_create(
			&data->philos->philo, NULL,
			&one_philo_routine, data->philos) != 0)
	{
		data->start_sim = 0;
		pthread_mutex_unlock(&data->start_sim_mtx);
		pthread_join(data->philos->philo, NULL);
		return (1);
	}
	data->start_sim = 1;
	return (0);
}

int	philo_threads(t_data *data)
{
	if (data->nb_philo == 1)
	{
		if (create_one_philo_thread(data) == 1)
			return (1);
	}
	else if (create_philo_threads(data) == 1)
		return (1);
	return (0);
}

int	join_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].philo, NULL);
		i++;
	}
	return (0);
}
