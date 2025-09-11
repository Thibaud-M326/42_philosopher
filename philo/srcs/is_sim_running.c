/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sim_running.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 18:52:39 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 18:52:39 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sim_running(t_data *data)
{
	pthread_mutex_lock(&data->run_sim_mtx);
	if (data->run_sim == 0)
	{
		pthread_mutex_unlock(&data->run_sim_mtx);
		return (0);
	}
	pthread_mutex_unlock(&data->run_sim_mtx);
	return (1);
}
