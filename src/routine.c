/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:38:28 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/21 14:40:08 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->fork_left]);
	printing(1, philo);
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	printing(2, philo);
	printing(3, philo);
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->start);
	philo->last_eat = get_time();
	philo->n_times_has_eat++;
	pthread_mutex_unlock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_right]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_philo % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->data->start);
	while (philo->data->someone_died == 0)
	{
		pthread_mutex_unlock(&philo->data->start);
		is_eating(philo);
		printing(4, philo);
		ft_sleep(philo->data->time_sleep);
		printing(5, philo);
		pthread_mutex_lock(&philo->data->start);
		if (philo->data->must_eat)
			if (philo->data->must_eat == philo->n_times_has_eat)
				break ;
	}
	pthread_mutex_unlock(&philo->data->start);
	return (NULL);
}
