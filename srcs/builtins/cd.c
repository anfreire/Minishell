/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 04:02:05 by anfreire          #+#    #+#             */
/*   Updated: 2022/11/12 16:06:20 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

extern int	g_exit;

static void	b_cd_aux(t_data *data, int index, int i)
{
	if (i > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		g_exit = 1;
		return ;
	}
	else if (i == 2 || (strncmp(data->par_line[++index], "~", 2) == 0 \
		&& i == 2))
	{
		chdir(getenv("HOME"));
		g_exit = 0;
		return ;
	}
	else if (chdir(data->par_line[++index]) != 0)
	{
		printf("Minishell: cd: %s: No such file or directory\n", \
		data->par_line[1]);
		g_exit = 1;
		return ;
	}
	g_exit = 0;
}

void	b_cd(t_data *data, int index)
{
	int	i;

	i = 0;
	while (data->par_line[i])
	{
		if (ft_strncmp(data->par_line[i], "|", 2) == 0 \
			|| ft_strncmp(data->par_line[i], "<", 2) == 0 \
			|| ft_strncmp(data->par_line[i], ">", 2) == 0 \
			|| ft_strncmp(data->par_line[i], "<<", 3) == 0 \
			|| ft_strncmp(data->par_line[i], ">>", 3) == 0)
			break ;
		i++;
	}
	b_cd_aux(data, index, i);
}
