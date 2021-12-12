/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:23:29 by pforesti          #+#    #+#             */
/*   Updated: 2021/12/06 10:21:23 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk_bonus.h"

int	g_sent;

static void	ft_client(int pid, const char *str)
{
	int				i;
	char			c;

	while (1)
	{
		i = -1;
		c = *str;
		while (++i < 8)
		{
			if (!(c & 1 << i))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
			usleep(100);
		}
		if (!*str)
			return ;
		str++;
	}
}

void	ft_handler(int signum)
{
	static int	received = 0;

	if (signum == SIGUSR2)
	{
		ft_printf("%d printed\n", received / 8);
		received = 0;
		exit(EXIT_SUCCESS);
	}
	else
	{
		received++;
		if (received / 8 == (g_sent / 2) && !(received % 8) && g_sent >= 500)
			ft_printf("half of the characters received\n", received / 8);
	}
}

int	main(int ac, char *av[])
{
	struct sigaction	sa;

	sa.sa_handler = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (ac == 3)
	{
		if (!av[2])
			exit(EXIT_FAILURE);
		if (!kill(ft_atoi(av[1]), 0))
		{
			g_sent = ft_strlen(av[2]);
			ft_printf("%d characters to send\n", g_sent);
			ft_client(ft_atoi(av[1]), av[2]);
		}
		else
			ft_printf("error : PID not valid\n");
	}
	else
		ft_printf("error : args not valid\n");
	return (0);
}
