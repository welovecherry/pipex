/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:38:08 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/09 22:19:34 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//char *validate_cmd_path_bonus(char **cmd_str_array)
//{
//	char *valid_path;

//	if (!cmd_str_array || !cmd_str_array[0])
//	{
//		write(2, "zsh: command not found:\n", 24);
//		return (NULL);
//	}
//	valid_path = is_valid_command(cmd_str_array[0]);
//	if (!valid_path)
//	{
//		write(2, "zsh: command not found: ", 24);
//		write(2, cmd_str_array[0], ft_strlen(cmd_str_array[0]));
//		write(2, "\n", 1);
//		return (NULL);
//	}
//	return (valid_path);
//}

//char *validate_cmd_path_bonus(char **cmd_str_array)
//{
//	char *valid_path;

//	if (!cmd_str_array[0])
//	{
//		if (cmd_str_array[0][0] == '\0')  // Check for empty command string
//		{
//			write(2, "zsh: permission denied: \n", 25);
//			//return (NULL);
//		}
//		else
//			write(2, "zsh: command not found:\n", 24);
//		return (NULL);
//	}
//	valid_path = is_valid_command(cmd_str_array[0]);
//	if (!valid_path)
//	{
//		write(2, "zsh: command not found: ", 24);
//		write(2, cmd_str_array[0], ft_strlen(cmd_str_array[0]));
//		write(2, "\n", 1);
//		return (NULL);
//	}
//	return (valid_path);
//}


//char *validate_cmd_path_bonus(char **cmd_str_array)
//{
//	char *valid_path;

//	if (!cmd_str_array || !cmd_str_array[0])
//	{
//		write(2, "zsh: command not found: \n", 25);
//		return (NULL);
//	}
//	if (cmd_str_array[0][0] == '\0')  // Check for empty command string
//	{
//		write(2, "zsh: permission denied: \n", 25);
//		return (NULL);
//	}
//	valid_path = is_valid_command(cmd_str_array[0]);
//	if (!valid_path)
//	{
//		write(2, "zsh: command not found: ", 24);
//		write(2, cmd_str_array[0], ft_strlen(cmd_str_array[0]));
//		write(2, "\n", 1);
//		return (NULL);
//	}
//	return (valid_path);
//}

//char *validate_cmd_path_bonus(char **cmd_str_array)
//{
//	char *valid_path;

//	if (!cmd_str_array )
//	{
//		write(2, "00", 2);
//		return NULL;
//	}

//	if (!cmd_str_array[0])
//	{
//		write(2, "11", 2);
//		write(2, "zsh: command not found: \n", 25);
//		return (NULL);
//	}
//	if (cmd_str_array[0][0] == '\0')  // Check for empty command string
//	{
//		write(2, "22", 2);

//		write(2, "zsh: permission denied: ''\n", 27);
//		return (NULL);
//	}
//	if (cmd_str_array[0][0] == ' ' && cmd_str_array[0][1] == '\0')  // Check for command string with a single space
//	{
//		write(2, "33", 2);
//		write(2, "zsh: command not found: ''\n", 27);
//		return (NULL);
//	}
//	valid_path = is_valid_command(cmd_str_array[0]);
//	if (!valid_path)
//	{
//		write(2, "44", 2);
//		write(2, "zsh: command not found: ", 24);
//		write(2, cmd_str_array[0], ft_strlen(cmd_str_array[0]));
//		write(2, "\n", 1);
//		return (NULL);
//	}
//	return (valid_path);
//}

//char *validate_cmd_path_bonus(char **cmd_str_array)
//{
//    char *valid_path;

//    if (!cmd_str_array)
//    {
//        write(2, "zsh: command not found: \n", 25);
//        return NULL;
//    }

//    if (cmd_str_array[0] == NULL || cmd_str_array[0][0] == '\0')  // Check for NULL or empty command string
//    {
//        write(2, "zsh: permission denied: ''\n", 27);
//        return (NULL);
//    }

//    if (cmd_str_array[0][0] == ' ' && cmd_str_array[0][1] == '\0')  // Check for command string with a single space
//    {
//        write(2, "zsh: command not found: ''\n", 27);
//        return (NULL);
//    }

//    valid_path = is_valid_command(cmd_str_array[0]);
//    if (!valid_path)
//    {
//        write(2, "zsh: command not found: ", 24);
//        write(2, cmd_str_array[0], ft_strlen(cmd_str_array[0]));
//        write(2, "\n", 1);
//        return (NULL);
//    }
//    return (valid_path);
//}

char *validate_cmd_path_bonus(char **cmd_str_array)
{
	char *valid_path;

	if (!cmd_str_array)
	{
		write(2, "zsh: command not found: \n", 25);
		return NULL;
	}

	// Check for empty command string
	if (cmd_str_array[0] && cmd_str_array[0][0] == '\0')
	{
		write(2, "zsh: permission denied: ''\n", 27);
		return (NULL);
	}

	// Check for command string with a single space
	if (cmd_str_array[0] && cmd_str_array[0][0] == ' ' && cmd_str_array[0][1] == '\0')
	{
		write(2, "zsh: command not found: ''\n", 27);
		return (NULL);
	}

	valid_path = is_valid_command(cmd_str_array[0]);
	if (!valid_path)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, cmd_str_array[0], ft_strlen(cmd_str_array[0]));
		write(2, "\n", 1);
		return (NULL);
	}
	return (valid_path);
}



void initialize_data(t_pipe_data *data, int ac, char *av[])
{
	data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->num_cmds = ac - 3;
	data->pids = malloc(data->num_cmds * sizeof(pid_t));
	data->valid_paths = malloc(data->num_cmds * sizeof(char *));
	data->cmd_str_arrays = malloc(data->num_cmds * sizeof(char **));
}

void initialize_pipes(t_pipe_data *data)
{
	int i = 0;

	data->pipes = malloc((data->num_cmds - 1) * sizeof(int *));
	while (i < data->num_cmds - 1)
	{
		data->pipes[i] = malloc(2 * sizeof(int));
		if (pipe(data->pipes[i]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void close_and_free(t_pipe_data *data)
{
	int i = 0;

	while (i < data->num_cmds - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	free(data->pids);
	free(data->valid_paths);
	free(data->cmd_str_arrays);
	close(data->infile);
	close(data->outfile);
}


void handle_redirections(t_pipe_data *data, int i)
{
	if (i == 0)  // First command: read from input file
	{
		dup2(data->infile, STDIN_FILENO);
	}
	else  // Not the first command: read from the previous command's pipe
	{
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
	}

	if (i == data->num_cmds - 1)  // Last command: write to output file
	{
		dup2(data->outfile, STDOUT_FILENO);
	}
	else  // Not the last command: write to the next command's pipe
	{
		dup2(data->pipes[i][1], STDOUT_FILENO);
	}
}

void close_all_pipes(t_pipe_data *data)
{
	int i;
	
	i = 0;
	while (i < data->num_cmds - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

void execute_command(t_pipe_data *data, char **av, int i)
{
	data->cmd_str_arrays[i] = ft_split(av[i + 2], ' ');
	data->valid_paths[i] = validate_cmd_path_bonus(data->cmd_str_arrays[i]);

	if (data->valid_paths[i])
	{
		if (execve(data->valid_paths[i], data->cmd_str_arrays[i], NULL) == -1)
		{
			perror("execve");
			exit(1);
		}
		free(data->valid_paths[i]);
	}
}

int main(int ac, char **av)
{
	t_pipe_data data;
	int			i;
	
	if (ac < 6)
	{
		write(2, "Invalid ac\n", 11);
		exit(1);
	}
	initialize_data(&data, ac, av);
	initialize_pipes(&data);
	i = 0;
	while (i < data.num_cmds)
	{
		data.pids[i] = fork();
		if (data.pids[i] == 0)  // Child process
		{
			handle_redirections(&data, i);
			close_all_pipes(&data);
			execute_command(&data, av, i);
		}
		i++;
	}
	waitpid(-1, NULL, 0);
	close_and_free(&data);
	return 0;
}