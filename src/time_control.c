/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:48:36 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/20 13:43:57 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	time_dif(long long current, long long past)
{
	return (current - past);
}

/*aqui convertimos el resultado en milisegundos porque
 la struct timeval lo da en segs y en microseg*/
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(long long time)
{
	long long	start;

	start = get_time();
	while (1)
	{
		if (time_dif(get_time(), start) >= time)
			break ;
		usleep(100);
	}
}
