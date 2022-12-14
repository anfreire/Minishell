/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 06:49:28 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/05 21:40:16 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	g_exit;

int	run_line(t_data *data, int i, int *flag)
{
	int	size;

	size = data->cmd.cmd_nbr + data->built.builtin_n;
	if (size == 0)
		no_command_not_found(data);
	while (data->par_line[++i])
	{
		if (builtin_detector(data, data->par_line[i]) >= 0)
			break ;
		else if (cmd_detector(data, data->par_line[i]) == 1 \
			&& data->paths.p_str != NULL)
			break ;
		else if (cmd_detector(data, data->par_line[i]) == 2 \
			&& data->paths.p_str != NULL)
			break ;
		else if (redir_detector(data, data->par_line[i]) == 1)
			flag++;
	}
	return (i);
}

int	walk_till_executable(t_data *data, int i)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	while (data->par_line[len])
		len++;
	i = run_line(data, i, &flag);
	if (flag > 1)
		command_not_found(data);
	if (i == len)
		return (-1);
	return (i - 1);
}

void	brain(t_data *data)
{
	int	i;

	i = -1;
	if (data->line == NULL || data->line[0] == '\0')
		return ;
	while (data->par_line[++i])
	{
		if (builtin_detector(data, data->par_line[i]) >= 0)
		{
			parse_builtin(data, i, data->built.b_counter);
			exec_builtin(data, data->redir.r_counter, i);
			data->built.b_counter++;
		}
		else if (cmd_detector(data, data->par_line[i]) > 0 && \
			data->paths.p_str != NULL)
		{
			run_command(data, data->redir.r_counter, data->cmd.c_counter, i);
			data->cmd.c_counter++;
			data->redir.r_counter++;
		}
		i = walk_till_executable(data, i);
		if (i < 0)
			break ;
	}
	close_files(data);
}

void	close_files(t_data *data)
{
	int	i;
	int	size;

	i = -1;
	size = data->cmd.cmd_nbr + data->built.builtin_n;
	if (size == 0)
		free_heredoc(data);
	while (++i < size)
		close(data->ids.pfd[i][1]);
	i = -1;
	while (++i < size)
		close(data->ids.pfd[i][0]);
	i = -1;
	while (++i < size)
		waitpid(data->ids.id[i], &g_exit, 0);
	signal(SIGINT, sig_handler);
	WEXITSTATUS(g_exit);
	if (g_exit == 2)
		g_exit = 130;
	else if (g_exit == 131)
		g_exit = 131;
	else
		g_exit /= 256;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc < 1 || *argv == NULL)
		return (0);
	starting(&data, envp);
	null_them_var(&data);
	while (1)
	{
		get_line(&data);
		starting_vars(&data);
		parse_line(&data);
		get_paths(&data);
		if (data.paths.p_str != NULL)
		{
			parse_alloc(&data);
			if (redirect(&data) < 0)
				continue ;
			parse_cmds(&data);
			brain(&data);
			free_line_info(&data);
		}
	}
	return (0);
}
