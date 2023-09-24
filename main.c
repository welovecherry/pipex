#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "pipex.h"


// 유효한 명령을 찾는 함수
char	*is_valid_command(const char *cmd)
{
	char	*path1;
	char	*path2;

	path1 = ft_strjoin("/bin/", cmd);
	path2 = ft_strjoin("/usr/bin/", cmd);

	// 메모리 할당 체크
	if (!path1 || !path2)
		return (NULL);

	// 둘 중 하나가 실행 가능한지 체크
	if (access(path1, X_OK) == 0)
	{
		free(path2);
		return (path1);
	}
	else if (access(path2, X_OK) == 0)
	{
		free(path1);
		return (path2);
	}

	// 둘 다 안되면 메모리 해제
	free(path1);
	free(path2);
	return (NULL);
}


char	*validate_cmd_path(char *cmd_str)
{
	char	**cmd_split;
	char	*valid_path;

	cmd_split = ft_split(cmd_str, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		write(2, "zsh: command not found:\n", 24);
		return (NULL);
	}
	valid_path = is_valid_command(cmd_split[0]);
	if (!valid_path)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, cmd_split[0], ft_strlen(cmd_split[0]));
		write(2, "\n", 1);
		return (NULL);
	}
	return valid_path;
}

void	execve_first_cmd(int *fd, char *path, char **cmd, char *file)
{
	int	file_fd;

	close(fd[READ]);	// 읽기용 파이프 닫기
	dup2(fd[WRITE], STDOUT_FILENO);	// 쓰기용 파이프 복사
	close(fd[WRITE]);	// 원본 쓰기용 파이프 닫기

	file_fd = open(file, O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	execve(path, cmd, NULL);
}

void	execve_second_cmd(int *fd, char *path, char **cmd, char *outfile)
{
	int	out_fd;

	close(fd[WRITE]);	// 쓰기용 파이프 닫기

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		exit(1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);

	dup2(fd[READ], STDIN_FILENO);	// 읽기용 파이프 복사
	close(fd[READ]);	// 원본 읽기용 파이프 닫기

	execve(path, cmd, NULL);
}


void	initialize_data(t_pipe_data *data, int ac, char **av)
{
	if (ac != 5)
	{
		write(2, "Invalid ac\n", 11);
		exit(1);
	}
	data->path1 = validate_cmd_path(av[2]);
	data->path2 = validate_cmd_path(av[3]);
	if (data->path1 == 0 || data->path2 == 0)
	{
		exit(1);
	}
	data->cmd_split1 = ft_split(av[2], ' ');
	data->cmd_split2 = ft_split(av[3], ' ');
}

void	handle_pipe(t_pipe_data *data)
{
	if (pipe(data->fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

//void handle_fork(t_pipe_data *data, char **av)
//{
//	data->pid = fork();
//	if (data->pid == 0)
//	{
//		execve_first_cmd(data->fd, data->path1, data->cmd_split1, av[1]);
//	}
//	else
//	{
//		wait(NULL);
//		execve_second_cmd(data->fd, data->path2, data->cmd_split2, av[4]);
//		close(data->fd[READ]);  // Close the reading end
//		close(data->fd[WRITE]); // Close the writing end
//	}
//}

int	main(int ac, char **av)
{
	t_pipe_data data;

	initialize_data(&data, ac, av);
	handle_pipe(&data);
	//handle_fork(&data, av);
	data.pid = fork();
	if (data.pid == 0)
	{
		execve_first_cmd(data.fd, data.path1, data.cmd_split1, av[1]);
	}
	else
	{
		wait(NULL);
		execve_second_cmd(data.fd, data.path2, data.cmd_split2, av[4]);
		close(data.fd[READ]);  // Close the reading end
		close(data.fd[WRITE]); // Close the writing end
	}
	free(data.path1);
	free(data.path2);

	return (0);
}
