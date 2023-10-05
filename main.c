/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:37:43 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/05 22:53:49 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_data(t_pipe_data *data, int ac, char **av)
{
	if (ac != 5)
	{
		write(2, "Invalid ac\n", 11);
		exit(1);
	}
	data->path1 = validate_cmd_path(av[2]);
	data->path2 = validate_cmd_path(av[3]);
	if (!data->path1 || !data->path2)
	{
		exit(1);
	}
	data->cmd_split1 = ft_split(av[2], ' ');
	data->cmd_split2 = ft_split(av[3], ' ');
}

void	handle_pipe(t_pipe_data *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	handle_fork(t_pipe_data *data)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork");
		exit (1);
	}
}

void	free_split_array(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

//void	leak_check()
//{
//	system("leaks ./pipex");
//}

int	main(int ac, char **av)
{
	t_pipe_data	data;

	//atexit(leak_check);
	initialize_data(&data, ac, av);
	handle_pipe(&data);
	handle_fork(&data);
	if (data.pid == 0)
	{
		execve_first_cmd(data.pipe_fd, data.path1, data.cmd_split1, av[1]);
	}
	else
	{
		waitpid(data.pid, NULL, WNOHANG);
		execve_second_cmd(data.pipe_fd, data.path2, data.cmd_split2, av[4]);
	}
	free(data.path1);
	free(data.path2);
	free_split_array(data.cmd_split1);
	free_split_array(data.cmd_split2);
	return (0);
}
