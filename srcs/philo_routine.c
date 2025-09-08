/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 16:10:54 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 16:10:54 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (!wait_start(philo->data))
		return (NULL);
	take_a_fork_and_die(philo);
	return (NULL);
}

void	*philo_routine(void *v_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)v_philo;
	data = philo->data;
	if (!wait_start(data))
		return (NULL);
	printf_mutex(philo->data, "is thinking", philo->id);
	if (philo->id & 1)
		ft_msleep(data->time_to_eat);
	while (is_sim_running(data))
	{
		if (eat(data, philo))
		{
			if (sleeping(data, philo))
				think(data, philo);
		}
		else
			put_forks(philo);
	}
	return (NULL);
}
