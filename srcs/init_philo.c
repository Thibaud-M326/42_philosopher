/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 13:01:36 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 13:01:36 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "philo.h"

t_data	*init_data_av(t_data *data, char **av)
{
	int	err;

	memset(data, 0, sizeof(t_data));
	data->nb_philo = ft_atol(av[1], &err);
	data->time_to_die = ft_atol(av[2], &err);
	data->time_to_eat = ft_atol(av[3], &err);
	data->time_to_sleep = ft_atol(av[4], &err);
	if (av[5])
		data->nb_must_eat = ft_atol(av[5], &err);
	else
		data->nb_must_eat = -1;
	data->odd_offset = 2 * data->time_to_eat - data->time_to_sleep;
	data->start_time = 0;
	data->run_sim = 1;
	data->start_sim = -1;
	return (data);
}

t_data	*init_data_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (NULL);
	memset(data->forks, 0, (sizeof(t_fork) * data->nb_philo));
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
		{
			while (i-- >= 0)
				pthread_mutex_destroy(&data->forks[i].fork);
			free(data->forks);
			data->forks = NULL;
			return (NULL);
		}
		data->forks[i].available = 1;
		i++;
	}
	return (data);
}

t_data	*init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		clean_data(data);
		return (NULL);
	}
	if (pthread_mutex_init(&data->run_sim_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		clean_data(data);
		return (NULL);
	}
	if (pthread_mutex_init(&data->start_sim_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->run_sim_mtx);
		clean_data(data);
		return (NULL);
	}
	return (data);
}

t_data	*init_data_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (NULL);
	memset(data->philos, 0, sizeof(t_philo) * data->nb_philo);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		if (pthread_mutex_init(&data->philos[i].last_meal_time_mtx, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].last_meal_time_mtx);
			return (NULL);
		}
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (data);
}

t_data	*init_philo(t_data *data, char **av)
{
	init_data_av(data, av);
	if (init_data_forks(data) == NULL)
		return (NULL);
	if (init_data_mutex(data) == NULL)
		return (NULL);
	if (init_data_philos(data) == NULL)
	{
		clean_data(data);
		return (NULL);
	}
	return (data);
}
