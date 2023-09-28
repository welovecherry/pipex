
//// DONE: ls
//// DONE: infile ls
//// DONE: infile ls | wc outfile
//// TODO: ac av
//// TODO: infile grep return | ls | wc outfile

//#include "pipex.h" // pipex.h 헤더 파일을 포함합니다.

//typedef struct	s_pipe_data
//{
//	int			pipe_fd[2];
//	pid_t		pid;
//	char		*path1;
//	char		*path2;
//	char		**cmd_split1;
//	char		**cmd_split2;
//}	t_pipe_data;


//char	*is_valid_cmd(char *cmd)
//{
//	char	*path1;
//	char	*path2;

//	path1 = ft_strjoin("/bin/", cmd);
//	path2 = ft_strjoin("/usr/bin/", cmd);
//	if (!path2 || !path2)
//		return (NULL);
//	if (access(path1, X_OK) == 0)
//	{
//		free (path2);
//		return (path1);
//	}
//	else if (access(path2, X_OK) == 0)
//	{
//		free(path1);
//		return (path2);
//	}
//	free(path1);
//	free(path2);
//	return (NULL);
//}

//char	*validate_cmd_path(char *cmd_str)
//{
//	char	**cmd_split;
//	char	*valid_path;

//	cmd_split = ft_split(cmd_str, ' ');
//	if (!cmd_split || !cmd_split[0])
//	{
//		write(2, "zsh: command not found:\n", 24);
//		return (NULL);
//	}
//	valid_path = is_valid_cmd(cmd_split[0]);
//	if (!valid_path)
//	{
//		write(2, "zsh: command not found: ", 24);
//		write(2, cmd_split[0], ft_strlen(cmd_split[0]));
//		write(2, "\n", 1);
//		return (NULL);
//	}
//	return (valid_path);
//}

//void	initalize_data(t_pipe_data *data, int ac, char **av)
//{
//	if (ac != 5)
//	{
//		write(2, "Invalid ac\n", 11);
//		exit(1);
//	}
//	data->path1 = validate_cmd_path(av[2]);
//	data->path2 = validate_cmd_path(av[2]);
//	if (!data->path1 || !data->path2)
//	{
//		exit (1);
//	}
//	data->cmd_split1 = ft_split(av[2], ' ');
//	data->cmd_split2 = ft_split(av[3], ' ');
//}


//// 메인 함수 시작
//int main(int ac, char **av)
//{
//	int		infile_fd;	// 입력 파일 디스크립터
//	int		outfile_fd;	// 출력 파일 디스크립터
//	t_pipe_data	data;

//	// 파이프 생성
//	if (pipe(data.pipe_fd) == -1)
//	{
//		perror("pipe");
//		exit(1);
//	}
//	data.pid = fork();
//	if (data.pid == -1)
//	{
//		perror("fork");
//		exit (1);
//	}
//	// 프로세스 분기
//	if (data.pid == 0)  // 자식 프로세스
//	{
//		execve_first_cmd(data.pipe_fd, data.path1);
//		//// 입력 파일을 연다.
//		//infile_fd = open("./ft_split.c", O_RDONLY);
//		//if (infile_fd == -1)
//		//{
//		//	perror("open");
//		//	exit(1);
//		//}
		
//		//dup2(infile_fd, STDIN_FILENO);
//		//close(infile_fd);

//		//// 출력을 파이프로 리다이렉션한다.
//		//dup2(pipe_fd[1], STDOUT_FILENO);
//		//close(pipe_fd[0]);
//		//close(pipe_fd[1]);

//		//// ls 명령어를 실행한다.
//		//char *args[] = {"grep","return", NULL};
//		//execve("/usr/bin/grep", args, NULL);
//	}
//	else  // 부모 프로세스
//	{
//		// 자식 프로세스가 종료되기를 기다린다.
//		wait(NULL);

//		// 출력 파일을 연다.
//		outfile_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//		if (outfile_fd == -1)
//		{
//			perror("open");
//			exit(1);
//		}

//		dup2(outfile_fd, STDOUT_FILENO);
//		close(outfile_fd);

//		// 입력을 파이프에서 받는다.
//		dup2(pipe_fd[0], STDIN_FILENO);
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);

//		// wc 명령어를 실행한다.
//		char *args2[] = {"ls", NULL};
//		execve("/bin/ls", args2, NULL);
//	}

//	return (0);
//}
