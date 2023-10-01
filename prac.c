//#include "pipex.h"

//char	*is_valid_command(const char *cmd)
//{
//	char	*path1;
//	char	*path2;

//	path1 = ft_strjoin("/bin/", cmd);
//	path2 = ft_strjoin("/usr/bin/", cmd);
//	if (!path1 || !path2)
//		return (NULL);
//	if (access(path1, X_OK) == 0)
//	{
//		free(path2);
//		return (path1);
//	}
//	else if (access(path2, X_OK) == 0)
//	{
//		free(path1);
//		return (path1);
//	}
//	free(path1);
//	free(path1);
//	return (NULL);
//}


//char *get_path(char **cmd_str)
//{
//	char *path;

//	if (!cmd_str || !cmd_str[0])
//	{
//		write(2, "invalid:\n", 24);
//		return (1);
//	}
//	path = is_valid_command(cmd_str[0]);
//	if (!path)
//	{
//		write(2, "zsh: cmd not found: ", 24);
//		write(2, cmd_str[0], ft_strlen(cmd_str[0]));
//		write(2, "\n", 1);
//		return (NULL);
//	}
//	return (path);
//}

//int main(int ac, char *av[])
//{
//	if (ac < 4)
//	{
//		perror("ac");
//		exit(1);
//	}

//	int infile = open(av[1], O_RDONLY); // 첫번째 인자는 ____ ____
//	int outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); // 마지막 인자는 ____ ____

//	int num_cmd = ac - 3; // ____ ____ ____
//	int pipes[num_cmd - 1][2]; // ____ ____
//	pid_t pid[num_cmd]; // ____ ____ ____ ____ ____

//	int i = 0;

//	while (i < num_cmd - 1)
//	{
//		if (pipe(pipes[i]) == -1)
//		{
//			perror("pipe");
//			exit(1);
//		}
//		i++;
//	}

//	i = 0;
//	while (i < num_cmd)
//	{
//		pid[i] = fork();
//		if (pid[i] == 0)
//		{
//			if (i == 0)
//			{
//				dup2(infile, STDIN_FILENO);
//			}
//			else
//			{
//				dup2(pipes[i - 1][0], STDIN_FILENO);
//			}

//			if (i == num_cmd - 1) // last av
//			{
//				dup2(outfile, STDOUT_FILENO);
//			}
//			else
//			{
//				dup2(pipes[i][1], STDOUT_FILENO);
//			}

//			int j = 0;
//			while (j < num_cmd - 1)
//			{
//				close(pipes[j][0]);
//				close(pipes[j][1]);
//				j++;
//			}

//			char **cmd_str = ft_split(av[i + 2], ' ');
//			char *path = get_path(cmd_str);

//			if (path)
//			{
//				evecve(path, cmd_str, NULL);
//				free(cmd_str);
//			}
//			perror("execve");
//			exit(1);
//		}
//		i++;
//	}

//	i = 0;
//	while (i < num_cmd - 1)
//	{
//		close(pipes[i][0]);
//		close(pipes[i][1]);
//		i++;
//	}

//	i = 0;
//	while (i < num_cmd)
//	{
//		wait(NULL);
//		i++;
//	}

//	close(infile);
//	close(outfile);

//	return 0;
//}