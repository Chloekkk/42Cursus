/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkim <nkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:48:55 by nkim              #+#    #+#             */
/*   Updated: 2022/05/06 16:17:46 by nkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_manager(t_manager *manager, int argc, char **argv)
{
	memset(manager, 0, sizeof(t_manager));
	manager->number_of_philos = arg_parse(argv[1]);
	manager->time_to_die = arg_parse(argv[2]);
	manager->time_to_eat = arg_parse(argv[3]);
	manager->time_to_sleep = arg_parse(argv[4]);
	manager->finish = FALSE;
	if (argc == 6)
		manager->num_of_time_must_eat = arg_parse(argv[5]);
	else
		manager->num_of_time_must_eat = -1;
	manager->start_ms_time = get_ms_time();
}

static int	init_philos(t_manager *manager)
{
	int	i;

	manager->philos
		= (t_philo *)malloc(sizeof(t_philo) * manager->number_of_philos);
	if (!manager->philos)
		return (throw_error("Error: malloc failed"));
	i = 0;
	while (i < manager->number_of_philos)
	{
		memset(&manager->philos[i], 0, sizeof(t_philo));
		manager->philos[i].id = i + 1;
		manager->philos[i].right = manager->philos[i].id;
		manager->philos[i].left = manager->philos[i].id - 1;
		manager->philos[i].start_eat_ms_time = 0;
		manager->philos[i].last_eat_ms_time = 0;
		manager->philos[i].start_sleep_ms_time = 0;
		manager->philos[i].num_of_eat = 0;
		manager->philos[i].manager = manager;
		if (pthread_mutex_init(&manager->philos[i].mutex, NULL))
			return (throw_error("pthread_mutex_init failed"));
		i++;
	}
	manager->philos[manager->number_of_philos - 1].right = 0;
	return (SUCCESS_FLAG);
}

static int	valid_manager(t_manager *manager, int argc)
{
	if (manager->number_of_philos <= 0)
		return (ERROR_FLAG);
	if (manager->time_to_die <= 0)
		return (ERROR_FLAG);
	if (manager->time_to_eat <= 0)
		return (ERROR_FLAG);
	if (manager->time_to_sleep <= 0)
		return (ERROR_FLAG);
	if (argc == 6 && manager->num_of_time_must_eat < 0)
		return (ERROR_FLAG);
	return (SUCCESS_FLAG);
}

static int	init_mutex(t_manager *manager)
{
	int	i;

	manager->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
							* manager->number_of_philos);
	if (!manager->fork)
		return (throw_error("Error: malloc failed"));
	if (pthread_mutex_init(&manager->print, NULL))
		return (throw_error("pthread_mutex_init failed"));
	if (pthread_mutex_init(&manager->finish_mutex, NULL))
		return (throw_error("pthread_mutex_init failed"));
	i = 0;
	while (i < manager->number_of_philos)
	{
		if (pthread_mutex_init(&manager->fork[i], NULL))
			return (throw_error("pthread_mutex_init failed"));
		i++;
	}
	return (SUCCESS_FLAG);
}

int	init(t_manager *manager, int argc, char **argv)
{
	init_manager(manager, argc, argv);
	if (valid_manager(manager, argc))
		return (ERROR_FLAG);
	if (init_philos(manager))
		return (ERROR_FLAG);
	if (init_mutex(manager))
		return (ERROR_FLAG);
	return (SUCCESS_FLAG);
}
