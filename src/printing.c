/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:26:25 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/21 14:27:35 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(int n, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (n == 1)
	{
		printf("%lld philo:%d has taken left fork 🍴 Left fork->%d\n",
			(get_time() - philo->data->start_time), philo->num_philo,
			philo->fork_left);
	}
	else if (n == 2)
	{
		printf("%lld philo:%d has taken right fork 🍴 Right fork->%d \n",
			(get_time() - philo->data->start_time), philo->num_philo,
			philo->fork_right);
	}
	else if (n == 3)
	{
		printf(YEL "%lld philo:%d is eating 🥗\n" RESET, (get_time()
				- philo->data->start_time), philo->num_philo);
	}
	continue_printing(n, philo);
}

void	continue_printing(int n, t_philo *philo)
{
	if (philo->data->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (n == 4)
	{
		printf(BLU "%lld philo:%d is sleeping 💤\n" RESET, (get_time()
				- philo->data->start_time), philo->num_philo);
	}
	else if (n == 5)
	{
		printf(CYN "%lld philo:%d is thinking 💭\n" RESET, (get_time()
				- philo->data->start_time), philo->num_philo);
	}
	else if (n == 6)
		printf(MAG "Everyone has eaten enough! 🥣 \n" RESET);
	pthread_mutex_unlock(&philo->data->print);
}
