/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 17:54:25 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 17:54:25 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_data *data, t_philo *philo)
{
	if (!is_sim_running(data))
		return (0);
	if (take_forks(philo) == 1)
		return (0);
	printf_mutex(philo->data, "is eating", philo->id);
	pthread_mutex_lock(&philo->last_meal_time_mtx);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_time_mtx);
	ft_msleep_sim_running(data, data->time_to_eat);
	pthread_mutex_lock(&philo->meals_eaten_mtx);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mtx);
	put_forks(philo);
	return (1);
}

int	sleeping(t_data *data, t_philo *philo)
{
	if (!is_sim_running(data))
		return (0);
	printf_mutex(philo->data, "is sleeping", philo->id);
	ft_msleep_sim_running(data, philo->data->time_to_sleep);
	return (1);
}

int	think(t_data *dt, t_philo *philo)
{
	if (!is_sim_running(dt))
		return (0);
	printf_mutex(philo->data, "is thinking", philo->id);
	if (dt->nb_philo & 1)
		ft_msleep_sim_running(dt, dt->odd_offset);
	return (1);
}
