/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_times.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 16:46:28 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 16:46:28 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_start_times(t_data *data)
{
	int		i;
	long	start_time;

	start_time = get_current_time();
	pthread_mutex_lock(&data->start_time_mtx);
	data->start_time = start_time;
	pthread_mutex_unlock(&data->start_time_mtx);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_time_mtx);
		pthread_mutex_lock(&data->start_time_mtx);
		data->philos[i].last_meal_time = start_time;
		pthread_mutex_unlock(&data->start_time_mtx);
		pthread_mutex_unlock(&data->philos[i].last_meal_time_mtx);
		i++;
	}
	return (0);
}
