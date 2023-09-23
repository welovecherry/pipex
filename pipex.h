#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h> // execve, access, dup2, close
#include <stdio.h>  // printf
#include <stdlib.h> // malloc, free
#include <string.h> // strlen
#include <fcntl.h>  // open
#include <sys/wait.h>



char	**ft_split(char *s, char c);
void create_and_wait_for_children(int *pipefd, char **av);
void execute_shell_cmd(int *pipefd, char *command);
void execute_first_child(int *pipefd, char *command);
void execute_second_child(int *pipefd, char *command, char *output_file);
void parent_wait(int *pipefd, pid_t child1, pid_t child2);
void redirect_input_from_file(const char *file);
void redirect_output_to_file(const char *file);

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
