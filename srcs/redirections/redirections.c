/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:31:48 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/09 13:55:36 by dmendonc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	redirect_input(t_data *data, int index)
{
	int	i;
	int	ret;

	i = find_i_for_infile(data, index);
	ret = redir_detector(data, data->par_line[i]);
	if (bridge_infiles(data, index) < 0)
		return (-1);
	if (ret == 2)
	{
		extract_input(data, index, i + 1);
		if (exec_in_redirect(data, index, 2) < 0)
			return (-1);
	}
	else
	{
		extract_hdockey(data, i + 1);
		heredoc(data, index);
	}
	return (i);
}

int	redirect_output(t_data *data, int index)
{
	int	i;
	int	ret;

	i = find_i_for_outfile(data, index);
	ret = redir_detector(data, data->par_line[i]);
	if (bridge_outfiles(data, index) < 0)
		return (-1);
	extract_output(data, index, i + 1);
	if (exec_out_redirect(data, index, ret) < 0)
		return (-1);
	return (i);
}

static int	redirect_aux(t_data *data, t_redir_tmp *var)
{
	if (var->ret > 1)
	{
		if (var->ret < 4 && var->flag_i == 0)
		{
			var->i = redirect_input(data, var->index);
			if (var->i < 0)
				return (-1);
			else
				var->flag_i = 1;
		}
		if (var->ret > 3 && var->flag_o == 0)
		{
			var->i = redirect_output(data, var->index);
			if (var->i < 0)
				return (-1);
			else
				var->flag_o = 1;
		}
	}
	return (0);
}

int	redirect(t_data *data)
{
	t_redir_tmp	var;

	var.i = 0;
	var.index = -1;
	var.flag_i = 0;
	var.flag_o = 0;
	var.size = data->cmd.cmd_nbr + data->built.builtin_n;
	while (++var.index <= var.size)
	{
		while (data->par_line[var.i])
		{
			var.ret = redir_detector(data, data->par_line[var.i]);
			if (var.ret == 1)
			{
				var.i++;
				break ;
			}
			if (redirect_aux(data, &var) == -1)
				return (-1);
			var.i++;
		}
		var.flag_i = 0;
		var.flag_o = 0;
	}
	return (1);
}
