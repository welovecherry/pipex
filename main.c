#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "pipex.h"
// Your ft_split function prototype

char	*is_valid_command(const char *cmd)
{
	char	*path1;
	char	*path2;

	path1 = ft_strjoin("/bin/", cmd);
	path2 = ft_strjoin("/usr/bin/", cmd);
	if (!path1 || !path2)
		return (NULL);
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
	free(path1);
	free(path2);
	return (NULL);
}

void execute_first_command(int *fd, char *valid_path1, char **cmd_split1, char *file)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	int file_fd = open(file, O_RDONLY);
	dup2(file_fd, 0);
	close(file_fd);
	execve(valid_path1, cmd_split1, NULL);
}


void execute_second_command_with_output(int *fd, char *valid_path2, char **cmd_split2, char *outfile)
{
	int out_fd;

	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(out_fd, 1);
	close(out_fd);

	execve(valid_path2, cmd_split2, NULL);
}



char	*parse_and_validate_cmd(char *cmd_str)
{
	char	**cmd_split;
	char	*valid_path;

	cmd_split = ft_split(cmd_str, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		write(2, "Invalid command\n", 16);
		return (NULL);
	}

	valid_path = is_valid_command(cmd_split[0]);
	if (!valid_path)
	{
		write(2, "Invalid command\n", 16);
		return (NULL);
	}

	return valid_path;
}

void wait_for_children(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
int main(int ac, char **av)
{
	int fd[2];
	pid_t pid;
	char *valid_path1;
	char *valid_path2;
	char **cmd_split1;
	char **cmd_split2;

	if (ac < 5)
	{
		write(2, "Usage: ./a.out <file> <command1> <command2> <outfile>\n", 55);
		return (1);
	}

	valid_path1 = parse_and_validate_cmd(av[2]);
	valid_path2 = parse_and_validate_cmd(av[3]);
	if (!valid_path1 || !valid_path2)
		return (1);

	cmd_split1 = ft_split(av[2], ' ');
	cmd_split2 = ft_split(av[3], ' ');

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		execute_first_command(fd, valid_path1, cmd_split1, av[1]);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execute_second_command_with_output(fd, valid_path2, cmd_split2, av[4]);
		}
		else
		{
			wait_for_children(fd);
		}
	}

	free(valid_path1);
	free(valid_path2);
	// Free the cmd_split arrays
	// ...

	return (0);
}