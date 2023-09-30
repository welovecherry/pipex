
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
//	valid_path = is_valid_command(cmd_split[0]);
//	if (!valid_path)
//	{
//		write(2, "zsh: command not found: ", 24);
//		write(2, cmd_split[0], ft_strlen(cmd_split[0]));
//		write(2, "\n", 1);
//		return (NULL);
//	}
//	return (valid_path);
//}

//int main(int argc, char *argv[])
//{
//	if (argc < 2)
//	{
//		fprintf(stderr, "No commands provided.\n");
//		exit(1);
//	}
	
//	int num_cmds = argc - 1; // 명령어의 개수
//	int pipes[num_cmds - 1][2]; // 파이프 배열
//	pid_t pids[num_cmds]; // 프로세스 ID를 저장할 배열
//	int i = 0;

//	// 파이프 생성
//	while (i < num_cmds - 1)
//	{
//		if (pipe(pipes[i]) == -1)
//		{
//			perror("pipe");
//			exit(1);
//		}
//		i++;
//	}

//	// 자식 프로세스 생성 및 명령어 실행
//	i = 0;
//	while (i < num_cmds)
//	{
//		pids[i] = fork();
//		if (pids[i] == 0)
//		{
//			// 첫 번째 명령어가 아닌 경우 입력을 리다이렉션
//			if (i != 0)
//			{
//				dup2(pipes[i - 1][0], STDIN_FILENO);
//			}
			
//			// 마지막 명령어가 아닌 경우 출력을 리다이렉션
//			if (i != num_cmds - 1)
//			{
//				dup2(pipes[i][1], STDOUT_FILENO);
//			}
			
//			// 사용하지 않는 파이프 닫기
//			int j = 0;
//			while (j < num_cmds - 1)
//			{
//				close(pipes[j][0]);
//				close(pipes[j][1]);
//				j++;
//			}
			
//			// 명령어 유효성 검사 및 실행
//			char *valid_path = validate_cmd_path(argv[i + 1]);
//			if (valid_path)
//			{
//				char *cmd_args[] = { valid_path, NULL };
//				execve(valid_path, cmd_args, NULL);
//				free(valid_path);
//			}
//			perror("execve");
//			exit(1);
//		}
//		i++;
//	}
	
//	// 부모 프로세스: 모든 파이프 닫기
//	i = 0;
//	while (i < num_cmds - 1)
//	{
//		close(pipes[i][0]);
//		close(pipes[i][1]);
//		i++;
//	}

//	// 모든 자식 프로세스가 종료될 때까지 대기
//	i = 0;
//	while (i < num_cmds)
//	{
//		wait(NULL);
//		i++;
//	}

//	return 0;
//}
