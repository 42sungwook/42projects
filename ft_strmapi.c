/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:42:46 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/11 16:52:44 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*return_s;

	i = 0;
	return_s = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!return_s)
		return (0);
	while (s[i] != 0)
	{
		return_s[i] = f(i, s[i]);
		i++;
	}
	return_s[i] = '\0';
	return (return_s);
}
