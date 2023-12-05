/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:52:02 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/13 17:25:03 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_check(int return_val, char *msg)
{
	if (return_val == -1)
	{
		perror(msg);
		exit(1);
	}
}

void	execve_first_cmd(t_pipe_data *data, char *infile, char **envp)
{
	int	infile_fd;

	error_check(close(data->pipe_fd[READ]), "close");
	error_check(dup2(data->pipe_fd[WRITE], STDOUT_FILENO), "dup2");
	error_check(close(data->pipe_fd[WRITE]), "close");
	infile_fd = open(infile, O_RDONLY);
	error_check(infile_fd, "open");
	error_check(dup2(infile_fd, STDIN_FILENO), "dup2");
	error_check(close(infile_fd), "close");
	error_check(execve(data->path1, data->cmd_split1, envp), "execve");
}

void	execve_second_cmd(t_pipe_data *data, char *outfile, char **envp)
{
	int	out_fd;

	error_check(close(data->pipe_fd[WRITE]), "close");
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	error_check(out_fd, "open");
	error_check(dup2(out_fd, STDOUT_FILENO), "dup2");
	error_check(close(out_fd), "close");
	error_check(dup2(data->pipe_fd[READ], STDIN_FILENO), "dup2");
	error_check(close(data->pipe_fd[READ]), "close");
	error_check(execve(data->path2, data->cmd_split2, envp), "execve");
}
