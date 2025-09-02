/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-01 00:45:52 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-01 00:45:52 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

int	ft_msleep_sim_running(t_data *data, int milliseconds)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (!is_sim_running(data))
			return (1);
		ft_msleep(1);
	}
	return (0);
}

long	get_current_time(void)
{
	struct timeval	time;
	long			start_time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (start_time);
}

int	ft_msleep(long milliseconds)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
