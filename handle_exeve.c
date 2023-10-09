/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exeve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:52:02 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/09 18:41:02 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execve_first_cmd(int *pipe_fd, char *path, char **cmd, char *file)
{
	int	infile_fd;

	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close(pipe_fd[WRITE]);
	infile_fd = open(file, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	execve_second_cmd(int *pipe_fd, char *path, char **cmd, char *outfile)
{
	int	out_fd;

	close(pipe_fd[WRITE]);
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
	{
		exit(1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close(pipe_fd[READ]);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
}
