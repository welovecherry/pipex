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


int main(int ac, char **av)
{
	int fd;
	pid_t pid;
	char *valid_path;
	char **cmd_split;

	if (ac < 3)
	{
		write(2, "Usage: ./a.out <file> <command> [options]\n", 42);
		return (1);
	}

	cmd_split = ft_split(av[2], ' ');
	if (!cmd_split || !cmd_split[0])
	{
		write(2, "Invalid command\n", 16);
		return (1);
	}

	valid_path = is_valid_command(cmd_split[0]);
	if (!valid_path)
	{
		write(2, "Invalid command\n", 16);
		return (1);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(1);
		}

		if (dup2(fd, 0) < 0)
		{
			perror("dup2");
			exit(1);
		}

		close(fd);

		char *envp[] = {NULL};

		if (execve(valid_path, cmd_split, envp) < 0)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}

	free(valid_path);
	// Free the cmd_split array
	// ...

	return (0);
}
