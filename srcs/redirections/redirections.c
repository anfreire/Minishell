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

int	redirect(t_data *data)
{
	int	i;
	int	flag_i;
	int	flag_o;
	int	index;
	int	size;
	int	ret;

	i = 0;
	index = -1;
	flag_i = 0;
	flag_o = 0;
	size = data->cmd.cmd_nbr + data->built.builtin_n;
	while (++index <= size)
	{
		while (data->par_line[i])
		{
			ret = redir_detector(data, data->par_line[i]);
			if (ret == 1)
			{
				i++;
				break ;
			}
			if (ret > 1)
			{
				if (ret < 4 && flag_i == 0)
				{
					i = redirect_input(data, index);
					if (i < 0)
						return (-1);
					else
						flag_i = 1;
				}
				if (ret > 3 && flag_o == 0)
				{
					i = redirect_output(data, index);
					if (i < 0)
						return (-1);
					else
						flag_o = 1;
				}
			}
			i++;
		}
		flag_i = 0;
		flag_o = 0;
	}
	return (1);
}
