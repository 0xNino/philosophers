/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/03 13:38:05 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	error(char *errmsg, int errnum)
{
	printf("%s", errmsg);
	return (errnum);
}

static int	isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			i++;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error("Error: wrong argument count\n", FAILURE));
	i = 1;
	while (i < argc)
	{
		if (isnumber(argv[i]) == FAILURE)
			return (error("Error: invalid arguments\n", FAILURE));
		i++;
	}
	return (SUCCESS);
}

static int	init_info(char **argv, t_info *info)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->nb_meals_req = ft_atoi(argv[5]);
	else
		info->nb_meals_req = 0;
	info->philos = malloc (sizeof(t_philo) * info->nb_philo);
	if (!info->philos)
		return (error("Error: philos malloc failed\n", FAILURE));
	info->death = 0;
	info->enough = 0;
	if (info->nb_philo < 1 || info->nb_philo > 250)
		return (error("Error: invalid philosopher count\n", FAILURE));
	if (info->time_die < 0 || info->time_eat < 0 || info->time_sleep < 0)
		return (error("Error: invalid time values\n", FAILURE));
	if (info->nb_meals_req < 0)
		return (error("Error: invalid required meal count\n", FAILURE));
	return (SUCCESS);
}

static int	init_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].nb_meals = 0;
		info->philos[i].left_fork_id = i;
		info->philos[i].right_fork_id = (i + 1) % info->nb_philo;
		info->philos[i].last_meal_time = 0;
		info->philos[i].info = info;
	}
	return (SUCCESS);
}

static int	init_mutex(t_info *info)
{
	int				i;
	pthread_mutex_t	*mutexes;

	i = -1;
	mutexes = malloc (sizeof(pthread_mutex_t) * info->nb_philo);
	if (!mutexes)
		return (error("Error: mutexes malloc failed\n", FAILURE));
	while (++i < info->nb_philo)
		if (pthread_mutex_init(&mutexes[i], NULL))
			return (error("Error: mutex init failed\n", FAILURE));
	info->forks = mutexes;
	if (pthread_mutex_init(&info->write, NULL))
		return (error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->alive, NULL))
		return (error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->meals_eaten, NULL))
		return (error("Error: mutex init failed\n", FAILURE));
	if (pthread_mutex_init(&info->time_check, NULL))
		return (error("Error: mutex init failed\n", FAILURE));
	return (SUCCESS);
}

static void	*one_philo(t_info *info)
{
	(void)info; //!
	return (NULL);
}

static int	check_death(t_info *info)
{
	int	exit;

	exit = FALSE;
	pthread_mutex_lock(&info->alive);
	if (info->death)
		exit = TRUE;
	pthread_mutex_unlock(&info->alive);
	return (exit);
}
static void	print(t_info *info, int philo_id, char *msg)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
		printf("%li %d %s\n", ft_time() - info->start_time, philo_id, msg);
	pthread_mutex_lock(&info->write);
}

static void	philo_sleep(t_info *info, long time)
{
	long	i;

	i = ft_time();
	while(check_death(info))
	{
		if (ft_time() - i >= time)
			break ;
		usleep(50);
	}
}

static void	philo_meal(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->forks[philo->left_fork_id]);
	print(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&info->forks[philo->right_fork_id]);
	print(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&info->time_check);
	philo->last_meal_time = ft_time();
	pthread_mutex_unlock(&info->time_check);
	print(info, philo->id, "is eating");
	philo_sleep(info, info->time_eat)
	pthread_mutex_unlock(&info->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&info->forks[philo->right_fork_id]);
}

static void	*start_routine(void *void_philo)
{
	t_philo *philo;
	t_info	*info;

	philo = (t_philo *) void_philo;
	info = philo->info;
	if (info->nb_philo == 1)
		return (one_philo(info));
	if (philo->id % 2)
		usleep(info->time_die + 50);
	while (check_death(info))
	{
		philo_meal(info, philo);
	}
	return (SUCCESS);
}

static int	init_thread(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = ft_time();
	while (++i < info->nb_philo)
	{
		if(pthread_create(&info->philos[i].thread_id, NULL, start_routine, &info->philos[i]))
			return (error("Error: phtread_create failed\n", FAILURE));
		pthread_mutex_lock(&info->time_check);
		info->philos[i].last_meal_time = ft_time();
		pthread_mutex_unlock(&info->time_check);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	philo;
	
	(void) philo; //!
	if (check_args(argc, argv))
		return (FAILURE);
	if (init_info(argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (FAILURE);
	if (init_mutex(&info))
		return (FAILURE);
	if (init_thread(&info))
		return (FAILURE);
	return (SUCCESS);
}
