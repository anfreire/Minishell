/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:36:36 by anfreire          #+#    #+#             */
/*   Updated: 2023/01/06 19:58:10 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

void	popullate_echo(t_data *data, int index)
{
	int	i;

	i = index + 2;
	while (data->par_line[i])
	{
		if (ft_strncmp(data->par_line[i], "|", 2) == 0 \
			|| ft_strncmp(data->par_line[i], "<", 2) == 0 \
			|| ft_strncmp(data->par_line[i], ">", 2) == 0 \
			|| ft_strncmp(data->par_line[i], "<<", 3) == 0 \
			|| ft_strncmp(data->par_line[i], ">>", 3) == 0)
			break ;
		printf("%s", data->par_line[i]);
		if (data->par_line[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

static void	b_echo_aux(t_data *data, int index, char *flag)
{
	if (ft_strncmp(data->par_line[index + 1], flag, 3) == 0)
	{
		popullate_echo(data, index);
	}
	else
	{
		popullate_echo(data, index - 1);
		printf("\n");
	}
	g_exit = 0;
}

void	b_echo(t_data *data, int index)
{
	char	flag[3];

	flag[0] = '-';
	flag[1] = 'n';
	flag[2] = '\0';
	if (!data->par_line[index + 1])
	{
		printf("\n");
		return ;
		g_exit = 0;
	}
	b_echo_aux(data, index, flag);
}
