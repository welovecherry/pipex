/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:49:20 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/08 19:54:57 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split_array(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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
	if (!cmd_split)
		return (NULL);
	if (!cmd_split[0])
	{
		if (cmd_str[0] == '\0') // Check if input is empty string
			write(2, "zsh: permission denied: \n", 25);
		else // Otherwise, input must be space only
			write(2, "zsh: command not found: \n", 25);
		free_split_array(cmd_split);  // Don't forget to free cmd_split
		return (NULL);
	}
	valid_path = is_valid_command(cmd_split[0]);
	if (!valid_path)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, cmd_split[0], ft_strlen(cmd_split[0]));
		write(2, "\n", 1);
		free_split_array(cmd_split);  // Don't forget to free cmd_split
		return (NULL);
	}
	free_split_array(cmd_split);  // Don't forget to free cmd_split
	return (valid_path);
}
