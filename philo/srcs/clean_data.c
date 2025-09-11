/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-01 01:31:58 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-01 01:31:58 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

void	clean_forks(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i].fork);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	return ;
}

void	clean_philos(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	return ;
}

void	clean_data_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->run_sim_mtx);
	pthread_mutex_destroy(&data->start_sim_mtx);
	return ;
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	clean_forks(data);
	clean_philos(data);
	clean_data_mutex(data);
	return ;
}
