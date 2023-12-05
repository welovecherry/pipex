/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:40:43 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/13 17:34:37 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1

typedef struct s_pipe_data
{
	int			pipe_fd[2];
	pid_t		pid;
	char		*path1;
	char		*path2;
	char		**cmd_split1;
	char		**cmd_split2;
	char		**path;
}	t_pipe_data;

char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
void	free_split_array(char **arr);
char	*validate_cmd_path(char *cmd_str, t_pipe_data *data);
void	free_split_array(char **arr);
void	execve_first_cmd(t_pipe_data *data, char *file, char **envp);
void	execve_second_cmd(t_pipe_data *data, char *outfile, char **envp);
void	free_split_array(char **arr);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
