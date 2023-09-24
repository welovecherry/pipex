#include "pipex_bonus.h"



char	*is_valid_command(const char *cmd)
{
	char	*path1;
	char	*path2;

	path1 = ft_strjoin("/bin/", cmd);
	path2 = ft_strjoin("usr/bin/", cmd);
	if (!path1 || !path2)
		return (NULL);
	if (access(path1, X_OK) == 0)
	{
		free(path2);
		return(path1);
	}
	else if (access(path2, X_OK) == 0)
	{
		free(path1);
		return (path2);
	}
	free(path1);
	free(path2);
	return (NULL);
}


char	*validate_cmd_path(char *cmd_str)
{
	char **cmd_split;
	char *valid_path;

	cmd_split = ft_split(cmd_str, ' ');
	if (cmd_split == 0 || cmd_split[0] == 0)
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
	return (valid_path);
}

void	execve_first_cmd(int *pipe_fd, char *path, char **cmd, char *file)
{
	int	infile_fd;

	close(pipe_fd[READ]);
	dup2(pipe_fd[WRITE],STDOUT_FILENO);
	close(pipe_fd[WRITE]);

	infile_fd = open(file, O_RDONLY);
	if (infile_fd < 0)  // 파일 열기 실패 처리
	{
		perror("open");
		exit(1);  // 실패시 프로그램 종료
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	execve(path, cmd, NULL);
}

void	execve_second_cmd(int *pipe_fd, char *path, char **cmd, char *outfile)
{
	int out_fd;

	close(pipe_fd[WRITE]);
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		exit(1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);

	dup2(pipe_fd[READ], STDIN_FILENO);
	close(pipe_fd[READ]);

	execve(path, cmd, NULL);
}

void	handle_pipe(t_pipe_data *data)
{
	if (pipe(data->fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
}

void	handle_fork(t_pipe_data *data)
{
	data->pid = fork();
	if (data->path1 < 0)
	{
		perror("fork");
		exit (1);
	}
}

void	initialize_data(t_pipe_data *data, int ac, char **av)
{
	if (ac != 5)
	{
		write(1, "Invalid ac\n", 11);
		exit(1);
	}
	data->path1 = validate_cmd_path(av[2]);
	data->path2 = validate_cmd_path(av[3]);
	if (!data->path1 || !data->path2)
	{
		exit (1);
	}
	data->cmd_split1 = ft_split(av[2], ' ');
	data->cmd_split2 = ft_split(av[3], ' ');
}


int main(int ac, char **av)
{
	t_pipe_data	data;

	initialize_data(&data, ac, av);
	handle_pipe(&data);
	handle_fork(&data);
	if (data.pid == 0)
	{
		excve_first_cmd(data.fd, data.path1, data.cmd_split1, av[1]);
	}
	else
	{
		wait(NULL);
		excve_second_cmd(data.fd, data.path2, data.cmd_split2, av[4]);
		close(data.fd[READ]);		
		close(data.fd[WRITE]);
	}
	free(data.path1);
	free(data.path2);
	return (0);
}