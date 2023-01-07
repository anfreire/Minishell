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
		if (ft_strncmp(data->par_line[i], "|", 2) == 0 ||
			ft_strncmp(data->par_line[i], "<", 2) == 0 ||
			ft_strncmp(data->par_line[i], ">", 2) == 0 ||
			ft_strncmp(data->par_line[i], "<<", 3) == 0 ||
			ft_strncmp(data->par_line[i], ">>", 3) == 0)
			break ;
		printf("%s", data->par_line[i]);
		if (data->par_line[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

void	b_echo(t_data *data, int index)
{
	int		j;
	char	flag[3];

	j = index;
	flag[0] = '-';
	flag[1] = 'n';
	flag[2] = '\0';
	if (!data->par_line[index + 1])
	{
		printf("\n");
		return ;
		g_exit = 0;
	}
	if (ft_strncmp(data->par_line[index + 1], flag, 3) == 0)
	{
		popullate_echo(data, index);
	}
	else
	{
		while (data->par_line[++j] &&
				redir_detector(data, data->par_line[j]) != 1)
		{
			printf("%s", data->par_line[j]);
			if (data->par_line[j + 1])
				printf(" ");
		}
		printf("\n");
	}
	g_exit = 0;
}
