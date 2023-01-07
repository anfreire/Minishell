/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendonc <dmendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:51:01 by dmendonc          #+#    #+#             */
/*   Updated: 2022/11/28 16:33:35 by dmendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	cont;

	cont = 0;
	while (str[cont])
	{
		cont++;
	}
	return (cont);
}

/*int	main(void)
{
	char	a[] = "aasadaswwdwdwdqwa";
	char	*ptr;
	int		contador;

	ptr = a;
	contador = ft_strlen(ptr);
	printf("%d\n", contador);
}*/