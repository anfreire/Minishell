/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:57:02 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/11 15:19:05 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

static void	extra_p_free_2(t_data *data)
{
	int	valor;

	if (data->ids.outp_list)
		free(data->ids.outp_list);
	if (data->redir.output)
	{
		if (data->ids.indicador)
			valor = data->ids.indicador[1];
		while (--valor >= 0)
			free(data->redir.output[valor]);
		free(data->redir.output);
	}
	free(data->ids.indicador);
	null_them_var(data);
}

void	extra_protection_free(t_data *data)
{
	int	valor;

	if (data->ids.indicador)
		valor = data->ids.indicador[0];
	if (data->ids.pfd)
	{
		while (--valor >= 0)
			free(data->ids.pfd[valor]);
		free(data->ids.pfd);
	}
	if (data->ids.id)
		free(data->ids.id);
	if (data->redir.input)
	{
		if (data->ids.indicador)
			valor = data->ids.indicador[1];
		while (--valor >= 0)
			free(data->redir.input[valor]);
		free(data->redir.input);
	}
	extra_p_free_2(data);
}
