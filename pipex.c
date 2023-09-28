//#include "pipex.h"

//// DONE: echo aa | echo bb
//// TODO: infile ls



////int main()
////{
////	//pid_t	pid;
////	int		infile_fd;

////	//pid = fork();
////	//if (pid == 0)
////	//{
////		char *argv[] = { "wc", NULL};

////		infile_fd = open("./ft_split.c", O_RDONLY);
////		dup2(infile_fd, STDIN_FILENO);
////		close(infile_fd);


////		execve("/usr/bin/wc", argv, NULL);
////	//}
////	//else
////	//{
////	//	wait(NULL);
////	//	char *argv2[] = {"echo", "bb", NULL};
////	//	execve("/bin/echo", argv2, NULL);
////	//}
////	return (0);
////}

////TODO: infile grep return | wc

//int main()
//{
//	pid_t	pid;
//	int		pipe_fd[2];
//	int		infile_fd;
//	int		outfile_fd;

//	if (pipe(pipe_fd) == -1) // STUDY: forgot making pipe
//	{
//		perror("pipe");
//		exit (1);
//	}

//	pid = fork();
//	if (pid == 0)
//	{
//		char *args[] = { "grep", "return", NULL};

//		infile_fd = open("./ft_split.c", O_RDONLY);
//		dup2(infile_fd, STDIN_FILENO);
//		close(infile_fd);
		
//		dup2(pipe_fd[WRITE], STDOUT_FILENO); // STUDY(OUT)
//		close(pipe_fd[READ]);
//		close(pipe_fd[WRITE]);

//		execve("/usr/bin/grep", args, NULL);
//	}
//	else
//	{
//		wait(NULL);
		
//		outfile_fd = open("outfile.txt", O_WRONLY| O_CREAT | O_TRUNC, 0644);
//		if 
//		dup2(outfile_fd, STDOUT_FILENO);
//		close(outfile_fd);

//		dup2(pipe_fd[READ], STDIN_FILENO);
//		close(pipe_fd[READ]);
//		close(pipe_fd[WRITE]);

//		char *args2[] = {"wc", NULL};
//		execve("/usr/bin/wc", args2, NULL);
//	}
//	return (0);
//}