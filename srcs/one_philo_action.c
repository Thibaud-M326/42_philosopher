/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_a_fork_and_die.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-27 16:04:44 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-27 16:04:44 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_a_fork_and_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	if (philo->left_fork->available == 1)
	{
		philo->left_fork->available = 0;
		printf_mutex(philo->data, "has taken a fork", philo->id);
	}
	if (ft_msleep_sim_running(philo->data, philo->data->time_to_die) == 1)
	{
		philo->left_fork->available = 1;
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
	return (0);
}
