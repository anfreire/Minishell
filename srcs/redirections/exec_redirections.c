/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 02:05:33 by dmendonc          #+#    #+#             */
/*   Updated: 2023/01/07 02:06:13 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

int	exec_in_redirect(t_data *data, int index, int save)
{
	if (save == 2)
	{
		data->ids.inp_list[index] = open(data->redir.input[index],
											O_RDONLY);
		if (data->ids.inp_list[index] < 0)
		{
			printf("Error: the file %s does not exist.",
					data->redir.input[index]);
			return (-1);
		}
	}
	return (1);
}

int	exec_out_redirect(t_data *data, int index, int save)
{
	if (save == 4)
	{
		data->ids.outp_list[index] = open(data->redir.output[index],
											O_CREAT | O_TRUNC | O_RDWR,
											0644);
		if (data->ids.outp_list[index] < 1)
		{
			printf("Error: the file %s had issues on open().",
					data->redir.output[index]);
			return (-1);
		}
	}
	if (save == 5)
	{
		data->ids.outp_list[index] = open(data->redir.output[index],
											O_CREAT | O_APPEND | O_RDWR,
											0644);
		if (data->ids.outp_list[index] < 1)
		{
			printf("Error: the file %s had issues on open().",
					data->redir.output[index]);
			return (-1);
		}
	}
	return (1);
}
