/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:37:43 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/11 22:44:52 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_data(t_pipe_data *data, char **av, char **envp)
{
	int		i;
	char	*full_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			full_path = ft_strnstr(envp[i], "PATH=", 5);
			full_path += 5;
			data->path = ft_split(full_path, ':');
			if (!data->path)
				exit(1);
		}
		i++;
	}
	data->path1 = validate_cmd_path(av[2], data);
	data->path2 = validate_cmd_path(av[3], data);
	if (!data->path1 || !data->path2)
		exit(1);
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

int	main(int ac, char **av, char **envp)
{
	t_pipe_data	data;

	if (ac != 5)
	{
		write(2, "Invalid ac\n", 11);
		exit(1);
	}
	initialize_data(&data, av, envp);
	handle_pipe(&data);
	handle_fork(&data);
	if (data.pid == 0)
	{
		execve_first_cmd(&data, av[1], envp);
	}
	else
	{
		waitpid(data.pid, NULL, WNOHANG);
		execve_second_cmd(&data, av[4], envp);
	}
	free(data.path1);
	free(data.path2);
	free_split_array(data.cmd_split1);
	free_split_array(data.cmd_split2);
	return (0);
}
