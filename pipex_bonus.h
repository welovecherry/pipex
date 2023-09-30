#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h> // execve, access, dup2, close
#include <stdio.h>  // printf
#include <stdlib.h> // malloc, free
#include <string.h> // strlen
#include <fcntl.h>  // open
#include <sys/wait.h>
#include <stdarg.h>

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


#endif
