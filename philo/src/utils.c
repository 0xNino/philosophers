/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:43:59 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/24 18:43:59 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	isnumber(char *str)
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

int	ft_atoi(const char *str)
{
	long	nbr;
	int		minus;

	nbr = 0;
	minus = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			minus = 1;
	while ('0' <= *str && *str <= '9')
	{
		if ((nbr > (__LONG_MAX__ - *str + '0') / 10) && minus)
			return (0);
		if ((nbr > (__LONG_MAX__ - *str + '0') / 10) && !minus)
			return (-1);
		nbr = 10 * nbr + (*str - '0');
		str++;
	}
	if (minus)
		return ((int)-nbr);
	return ((int)nbr);
}

int	min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	print_meals(t_info *info, t_philo *philo, int count, long time)
{
	int		sat_nb;
	int		meals_req;
	int		id;
	long	wait;

	sat_nb = info->satiated_nb;
	meals_req = info->nb_meals_req;
	id = philo->id + 1;
	wait = philo_time() - philo->last_meal_time;
	if (meals_req <= 0 && time < 10000)
		printf(EAT1, WHITE, time, id, wait, count, RESET);
	else if (meals_req <= 0)
		printf(EAT2, WHITE, time, id, wait, count, RESET);
	else if (sat_nb >= info->nb_philo && count == meals_req && time < 10000)
		printf(EAT3, GREEN2, time, id, wait, count, RESET);
	else if (sat_nb >= info->nb_philo && count == meals_req)
		printf(EAT4, GREEN2, time, id, wait, count, RESET);
	else if ((count == meals_req || sat_nb >= info->nb_philo) && time < 10000)
		printf(EAT3, GREEN, time, id, wait, count, RESET);
	else if (count == meals_req || sat_nb >= info->nb_philo)
		printf(EAT4, GREEN, time, id, wait, count, RESET);
	else if (time < 10000)
		printf(EAT5, WHITE, time, id, wait, count, RESET);
	else
		printf(EAT6, WHITE, time, id, wait, count, RESET);
}
