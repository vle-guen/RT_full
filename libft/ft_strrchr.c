/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:54:51 by avella            #+#    #+#             */
/*   Updated: 2015/11/24 15:55:19 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int index;

	index = 0;
	while (s[index] != '\0')
		index++;
	while (index >= 0)
	{
		if (s[index] == (char)c)
			return ((char *)&s[index]);
		index--;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[index]);
	}
	return (NULL);
}
