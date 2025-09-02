/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 16:53:37 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 16:53:37 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_start(t_data *data)
{
	pthread_mutex_lock(&data->start_sim_mtx);
	if (data->start_sim == 1)
	{
		pthread_mutex_unlock(&data->start_sim_mtx);
		return (1);
	}
	pthread_mutex_unlock(&data->start_sim_mtx);
	return (0);
}
