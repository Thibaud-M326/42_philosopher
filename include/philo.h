/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmaitre <thmaitre@student.42lyon.fr>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 11:51:44 by thmaitre          #+#    #+#             */
/*   Updated: 2025-08-25 11:51:44 by thmaitre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					available;
}	t_fork;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			philo;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		last_meal_time_mtx;
	long				last_meal_time;
	pthread_mutex_t		meals_eaten_mtx;
	int					meals_eaten;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	long				start_time;
	int					nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					nb_must_eat;
	int					odd_offset;
	pthread_mutex_t		run_sim_mtx;
	int					run_sim;
	pthread_mutex_t		print;
	pthread_mutex_t		start_sim_mtx;
	int					start_sim;
	t_philo				*philos;
	t_fork				*forks;
}	t_data;

//	srcs/check_args.c
int		check_args(int ac, char **av);

//	srcs/clean_data.c
void	clean_data(t_data *data);

//	srcs/take_forks.c
int		take_forks(t_philo *philo);
void	put_forks(t_philo *philo);

//	srcs/ft_atol.c
long	ft_atol(const char *nptr, int *err);

//	srcs/init_philo.c
t_data	*init_philo(t_data *data, char **av);

//	srcs/is_sim_running.c
int		is_sim_running(t_data *data);

//	srcs/monitor.c
int		monitor(t_data *data);

//	srcs/one_philo_action.c
int		take_a_fork_and_die(t_philo *philo);

//	srcs/philo_actions.c
int		eat(t_data *data, t_philo *philo);
int		sleeping(t_data *data, t_philo *philo);
int		think(t_data *data, t_philo *philo);

//	srcs/philo_routine.c
void	*philo_routine(void *v_philo);
void	*one_philo_routine(void *v_philo);

//	srcs/philo_threads.c
int		philo_threads(t_data *data);
int		join_philo_threads(t_data *data);

//	srcs/printf_mutex.c
void	printf_mutex_ate_enough(t_data *data);
void	printf_mutex(t_data *data, char *msg, int id_philo);

//	srcs/set_start_times.c
int		set_start_times(t_data *data);

//	srcs/time.c
int		ft_msleep_sim_running(t_data *data, int milliseconds);
long	get_current_time(void);
int		ft_msleep(long milliseconds);

//	srcs/wait_start.c
int		wait_start(t_data *data);
