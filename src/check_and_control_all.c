/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_control_all.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:11:36 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/22 12:39:40 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_if_everyone_has_eaten(t_philo *philo)
{
	printing(6, philo);
	pthread_mutex_lock(&philo->data->print);
	philo->data->someone_died = 1;
	pthread_mutex_unlock(&philo->data->print);
	return (NULL);
}

int	check_if_someone_is_dead(t_philo *philo, int i)
{
	if (time_dif(get_time(), philo[i].last_eat) > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print);
		philo->data->someone_died = 1;
		printf(BRED "%lld Philo %d has died 💀\n" RESET, (get_time()
				- philo->data->start_time), (i + 1));
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	return (0);
}

void	*check_philo(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->someone_died == 0)
	{
		i = -1;
		pthread_mutex_lock(&philo->data->start);
		while (++i < philo->data->philos_num)
		{
			if (check_if_someone_is_dead(philo, i) == 1)
				break ;
		}
		while (--i >= 0 && (philo[i].n_times_has_eat == philo->data->must_eat)
			&& philo->data->someone_died == 0)
		{
			if (i == 0)
				return (check_if_everyone_has_eaten(philo));
		}
		if (philo->data->someone_died)
			break ;
		pthread_mutex_unlock(&philo->data->start);
		usleep(100);
	}
	return (NULL);
}

int	create_control(t_data *data, t_philo *philo)
{
	pthread_t	control;

	if (pthread_create(&control, NULL, &check_philo, philo) != 0)
	{
		printf("Can't control if someone died\n");
		return (free_and_destroy(data, philo, -1));
	}
	pthread_join(control, NULL);
	return (0);
}
