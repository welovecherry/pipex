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


char	*parse_and_validate_cmd(char *cmd_str)
{
	char	**cmd_split;
	char	*valid_path;

	cmd_split = ft_split(cmd_str, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		write(2, "\n", 1);
		return (NULL);
	}

	valid_path = is_valid_command(cmd_split[0]);
	if (!valid_path)
	{
		//write(2, "zsh: command not found: ", 16);
		// ft_printf????
		printf("zsh: command not found: %s\n", cmd_split[0]);
		return (NULL);
	}

	return valid_path;
}

// 첫 번째 명령어 실행 함수
void execute_first_cmd(int *fd, char *valid_path1, char **cmd_split1, char *file)
{
	close(fd[0]); // 읽기용 파이프 닫기
	dup2(fd[1], 1); // 쓰기용 파이프 복사
	close(fd[1]); // 원본 쓰기용 파이프 닫기

	// 파일 열고 읽기
	int file_fd = open(file, O_RDONLY);
	dup2(file_fd, 0);
	close(file_fd);

	execve(valid_path1, cmd_split1, NULL);
}

// 두 번째 명령어 실행 함수
void execute_second_cmd(int *fd, char *valid_path2, char **cmd_split2, char *outfile)
{
	int out_fd;
	close(fd[1]);

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(out_fd, 1); 
	close(out_fd); 

	dup2(fd[0], 0);
	close(fd[0]); 
	execve(valid_path2, cmd_split2, NULL);
}



void	initialize_data(t_pipe_data *data, int ac, char **av)
{
	if (ac != 5)
	{
		write(2, "Invalid ac\n", 11);
		exit(1);
	}
	data->valid_path1 = parse_and_validate_cmd(av[2]);
	data->valid_path2 = parse_and_validate_cmd(av[3]);
	if (!data->valid_path1 || !data->valid_path2)
		exit(1);
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

void handle_fork(t_pipe_data *data, char **av)
{
	data->pid = fork();
	if (data->pid == 0)
	{
		execute_first_cmd(data->fd, data->valid_path1, data->cmd_split1, av[1]);
	}
	else
	{
		wait(NULL);
		execute_second_cmd(data->fd, data->valid_path2, data->cmd_split2, av[4]);
		close(data->fd[READ]);  // Close the reading end
		close(data->fd[WRITE]); // Close the writing end
	}
}

int	main(int ac, char **av)
{
	t_pipe_data data;

	initialize_data(&data, ac, av);
	handle_pipe(&data);
	//handle_fork(&data, av);
	data.pid = fork();
	if (data.pid == 0)
	{
		execute_first_cmd(data.fd, data.valid_path1, data.cmd_split1, av[1]);
	}
	else
	{
		wait(NULL);
		execute_second_cmd(data.fd, data.valid_path2, data.cmd_split2, av[4]);
		close(data.fd[READ]);  // Close the reading end
		close(data.fd[WRITE]); // Close the writing end
	}
	free(data.valid_path1);
	free(data.valid_path2);

	return (0);
}
