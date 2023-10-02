
#include "pipex.h"
//// latest version

//// 유효한 명령을 찾는 함수
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

char	*validate_cmd_path(char *cmd_str)
{
	char	**cmd_split;
	char	*valid_path;

	cmd_split = ft_split(cmd_str, ' ');
	if (!cmd_split || !cmd_split[0])
		return (NULL);
	if (cmd_str[0] == '\0') // Check if input is empty string
	{
		write(2, "zsh: permission denied: \n", 25);
		return (NULL);
	}
	if (ft_strcmp(cmd_str, " ") == 0) // Check if input is space only
	{
		write(2, "zsh: command not found: \n", 25);
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
	int	infile_fd;  // 변경된 변수명

	close(pipe_fd[READ]);		// 읽기용 파이프 닫기
	dup2(pipe_fd[WRITE], STDOUT_FILENO);	// 쓰기용 파이프를 표준 출력에 복사
	close(pipe_fd[WRITE]);		// 원본 쓰기용 파이프 닫기

	infile_fd = open(file, O_RDONLY);  // 입력 파일을 읽기 전용으로 열기
	if (infile_fd == -1)  // 파일 열기 실패 시
	{
		perror("open");
		exit(1);  // 프로그램 종료
	}
	dup2(infile_fd, STDIN_FILENO);  // 입력 파일 디스크립터를 표준 입력에 복사  // 인파일의 내용을 읽는다! 표준 입력이 아니라!
	close(infile_fd);  // 원본 입력 파일 디스크립터 닫기

	if (execve(path, cmd, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	execve_second_cmd(int *pipe_fd, char *path, char **cmd, char *outfile)
{
	int	out_fd;

	close(pipe_fd[WRITE]);	// 쓰기용 파이프를 닫는다.

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)  // 파일 열기에 실패하면
	{
		exit(1);  // 프로그램을 종료한다.
	}
	dup2(out_fd, STDOUT_FILENO);  // 출력 파일 디스크립터를 표준 출력에 복사한다.
	close(out_fd);  // 출력 파일 디스크립터를 닫는다.

	dup2(pipe_fd[READ], STDIN_FILENO);  // 읽기용 파이프를 표준 입력에 복사한다.
	close(pipe_fd[READ]);  // 원본 읽기용 파이프를 닫는다.

	//execve(path, cmd, NULL);  // 새로운 프로세스를 실행한다.
	if (execve(path, cmd, NULL) == -1)
	{
		perror("execve");
		exit(1);  // 실패 시 오류 메시지 출력 후 종료
	}
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
	if (!data->path1 || !data->path2)
	{
		exit(1);
	}
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


int	main(int ac, char **av)
{
	t_pipe_data	data;

	initialize_data(&data, ac, av);
	handle_pipe(&data);
	handle_fork(&data);
	if (data.pid == 0)
	{
		execve_first_cmd(data.pipe_fd, data.path1, data.cmd_split1, av[1]);
		//close(data.pipe_fd[READ]);
		//close(data.pipe_fd[WRITE]);
	}
	else
	{
		wait(NULL);
		execve_second_cmd(data.pipe_fd, data.path2, data.cmd_split2, av[4]);
		// TODO: execve_second_cmd가 실패할 경경우우만  클클로로즈  해해야야지지!
		//close(data.pipe_fd[READ]);
		//close(data.pipe_fd[WRITE]);
	}
	free(data.path1);
	free(data.path2);
	
	return (0);
}
