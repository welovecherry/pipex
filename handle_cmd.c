/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:49:20 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/13 17:54:11 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*is_valid_command(const char *cmd, t_pipe_data *data)
{
	char	*valid_path;
	char	*temp_path;
	int		i;

	i = 0;
	while ((data->path)[i])
	{
		temp_path = ft_strjoin((data->path)[i++], "/");
		if (!temp_path)
			exit(1);
		valid_path = ft_strjoin(temp_path, cmd);
		if (!valid_path)
		{
			free(temp_path);
			exit(1);
		}
		if (access(valid_path, X_OK) == 0)
		{
			free(temp_path);
			return (valid_path);
		}
		free(temp_path);
		free(valid_path);
	}
	return (NULL);
}

char	*not_valid_path(char **cmd_split)
{
	write(2, "zsh: command not found: ", 24);
	write(2, cmd_split[0], ft_strlen(cmd_split[0]));
	write(2, "\n", 1);
	free_split_array(cmd_split);
	return (NULL);
}

char	*validate_cmd_path(char *cmd_str, t_pipe_data *data)
{
	char	**cmd_split;
	char	*valid_path;

	cmd_split = ft_split(cmd_str, ' ');
	if (!cmd_split)
		return (NULL);
	if (!cmd_split[0])
	{
		if (cmd_str[0] == '\0')
			write(2, "zsh: permission denied: \n", 25);
		else
			write(2, "zsh: command not found: \n", 25);
		free_split_array(cmd_split);
		return (NULL);
	}
	valid_path = is_valid_command(cmd_split[0], data);
	if (!valid_path)
		return (not_valid_path(cmd_split));
	free_split_array(cmd_split);
	return (valid_path);
}
