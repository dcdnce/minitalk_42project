/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 21:13:25 by pforesti          #+#    #+#             */
/*   Updated: 2021/11/30 19:33:49 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

static void	ft_lstprintfree(t_list *lst)
{
	t_list	*v;
	t_list	*tofree;

	v = lst;
	while (v)
	{
		tofree = v;
		write(1, (char *)v->content, sizeof(char));
		v = (*v).next;
		free(tofree->content);
		free(tofree);
	}
}

static void	ft_str(char c, int pid, int *flag)
{
	static t_list	*lst = NULL;
	char			*p;

	p = malloc(sizeof(char));
	*p = c;
	ft_lstadd_back(&lst, ft_lstnew(p));
	if (!c)
	{
		ft_lstprintfree(lst);
		lst = NULL;
		kill(pid, SIGUSR2);
		*flag = 1;
	}
}

static void	ft_server(int signum, siginfo_t *si, void *uc)
{
	static char		c = 0;
	static int		i = 0;
	int				flag;

	flag = 0;
	if (signum == SIGUSR2)
		c ^= 1 << i;
	else
		c ^= 0 << i;
	i += 1;
	if (i == 8)
	{
		ft_str(c, si->si_pid, &flag);
		i = 0;
		c = 0;
		if (flag)
			return ;
	}
	(void)uc;
	usleep(100);
	kill(si->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID : %d\n", (int)getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_server;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (42)
		pause();
	return (0);
}
