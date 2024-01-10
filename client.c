/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarikay <osarikay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:42:47 by osarikay          #+#    #+#             */
/*   Updated: 2024/01/10 15:58:32 by osarikay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	pid_check(int pid)
{
	if (pid == -1)
	{
		write(1, "\033[3;31mPlease enter a valid PID!\n", 33);
		exit(0);
	}
	if (kill(pid, 0) == -1)
	{
		write(1, "\033[3;31mThis PID is wrong!\n", 26);
		exit(0);
	}
	return (0);
}

void	ft_sendbit(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	char *message;
	int i;
	
	i = 0;
	if (argc != 3)
	{
		write(1,
			"\033[3;31mCheck Arguments!\n\
Please enter a ./client <PID> <String>\n",
			63);
		return (1);
	}
	pid = atoi(argv[1]);
	pid_check(pid);
	message = "\033[3;36mClient'ten Gelen Mesaj -->\033[0m ";
	while (message[i])
		ft_sendbit(pid, message[i++]);
	while (*argv[2])
		ft_sendbit(pid, *(argv[2]++));
	ft_sendbit(pid, '\n');
	return (0);
}
