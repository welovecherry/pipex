/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:40:25 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/09 19:50:18 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

//typedef struct	s_pipe_data
//{
//	int			pipe_fd[2];
//	pid_t		pid;
//	char		*path1;
//	char		*path2;
//	char		**cmd_split1;
//	char		**cmd_split2;
//}	t_pipe_data;

//typedef struct	s_pipe_data
//{
//	int		infile;          // File descriptor for input file
//	int		outfile;         // File descriptor for output file
//	int		num_cmds;        // Number of commands
//	int		**pipes;         // Array of pipe file descriptors
//	pid_t	*pids;           // Array of process IDs
//	char	*path1;
//	char	*path2;
//	char	**cmd_split1;
//	char	**cmd_split2;
//}	t_pipe_data;

typedef struct s_pipe_data
{
	int		infile;          // File descriptor for input file
	int		outfile;         // File descriptor for output file
	int		num_cmds;        // Number of commands
	int		**pipes;         // Array of pipe file descriptors
	pid_t	*pids;           // Array of process IDs
	char	**valid_paths;   // Array of validated command paths
	char	***cmd_str_arrays; // Array of command string arrays
}	t_pipe_data;

char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*is_valid_command(const char *cmd);
char	*validate_cmd_path(char *cmd_str);
void	free_split_array(char **arr);

#endif
