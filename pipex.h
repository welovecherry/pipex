#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h> // execve, access, dup2, close
#include <stdio.h>  // printf
#include <stdlib.h> // malloc, free
#include <fcntl.h>  // open
#include <sys/wait.h> // wait

#define READ 0
#define WRITE 1

typedef struct	s_pipe_data
{
	int			pipe_fd[2];
	pid_t		pid;
	char		*path1;
	char		*path2;
	char		**cmd_split1;
	char		**cmd_split2;
}	t_pipe_data;


char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

//void create_and_wait_for_children(int *pipefd, char **av);
//void execute_shell_cmd(int *pipefd, char *command);
//void execute_first_child(int *pipefd, char *command);
//void execute_second_child(int *pipefd, char *command, char *output_file);
//void parent_wait(int *pipefd, pid_t child1, pid_t child2);
//void redirect_input_from_file(const char *file);
//void redirect_output_to_file(const char *file);
//int	ft_printf(const char *format, ...);

#endif
