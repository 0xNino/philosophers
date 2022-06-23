/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/23 02:49:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*satiated_rout(void *void_philo)
{
	t_philo	*philo;
	t_info	*info;
	int		i;

	philo = (t_philo *) void_philo;
	info = philo->info;
	while (check_death(info))
	{
		philo_sleep(info, 10);
		i = 0;
		pthread_mutex_lock(&info->satiated);
		if (info->satiated_nb == info->nb_philo)
		{
			pthread_mutex_lock(&info->alive);
			info->death = 1;
			pthread_mutex_unlock(&info->alive);
			break ;
		}
		return (philo_unlock(&info->satiated));
	}
	pthread_mutex_unlock(&info->satiated);
	return ((void *) FAILURE);
}

static void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) void_philo;
	info = philo->info;
	if (info->nb_philo == 1)
		return (SUCCESS);
	if (philo->id % 2)
		philo_sleep(info, 500);
	while (check_death(info))
	{
		philo_meal(info, philo);
		if (check_satiated(info, philo) == SUCCESS)
			return (SUCCESS);
		pthread_mutex_lock(&info->meals_eaten);
		if (info->enough)
			return (philo_unlock(&info->meals_eaten));
		pthread_mutex_unlock(&info->meals_eaten);
		print_sleep(info, philo);
		philo_sleep(info, info->time_sleep);
		print_think(info, philo);
	}
	return (SUCCESS);
}

static int	alone(t_info *info)
{
	t_philo	philo;

	philo = info->philos[0];
	if (pthread_create(&philo.thread_id, NULL, routine, &philo))
		return (philo_error("Error: phtread_create failed\n", FAILURE));
	philo.starvation_time = info->time_die;
	print_fork(info, &philo, philo.left_fork_id);
	philo_sleep(info, info->time_die);
	print_death(info, &philo);
	pthread_join(philo.thread_id, NULL);
	free(info->philos);
	end_mutexes(info);
	return (SUCCESS);
}

static int	philo(t_info *info)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = info->philos;
	info->start_time = philo_time();
	printf("%s%s%s%s\n", WHITE, DASH, DASH2, RESET);
	if (info->nb_philo == 1)
		return (alone(info));
	while (++i < info->nb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]))
			return (philo_error("Error: phtread_create failed\n", FAILURE));
		if (pthread_create(&info->satiated_id, NULL, satiated_rout, &philos[i]))
			return (philo_error("Error: phtread_create failed\n", FAILURE));
		pthread_mutex_lock(&info->time_check);
		philos[i].last_meal_time = philo_time();
		pthread_mutex_unlock(&info->time_check);
	}
	end_monitor(info, info->philos);
	end_threads(info);
	end_mutexes(info);
	if (info->satiated_nb >= info->nb_philo)
		printf("%s\t\t\tEveryone finished eating 🎉\t\t\t%s\n", BLUEBG, RESET);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_args(argc, argv))
		return (FAILURE);
	if (init_info(argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (FAILURE);
	if (init_mutex(&info))
		return (FAILURE);
	if (philo(&info))
		return (FAILURE);
	return (SUCCESS);
}
