/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlourenc <xlourenc@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:38 by xaviermonte       #+#    #+#             */
/*   Updated: 2024/08/21 17:15:39 by xlourenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//extra functions.
//STRJOIN - JOINING THE BUFFER TO THE GLOBAL VARIABLE.
//STRCHR - USED TO SEARCH TRUE THE STRING FOR A "\n" and give use a flag 0 or 1. 
int ft_strlen(char *str)
{
	int i;

	i = 0;
	if(!str)
		return(0);
	while(str[i])
	{
		i++;
	}
	return i;
}
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		a;
	char	*str3;

	i = 0;
	a = 0;
	if (!s2)
		return (NULL);
	
	str3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str3)
		return (NULL);
	while (s1 != NULL && s1[a])
	{
		str3[i] = s1[a];
		i++;
		a++;
	}
	a = 0;
	while (s2 != NULL && s2[a])
	{
		str3[i] = s2[a];
		i++;
		a++;
	}
	str3[i] = '\0';
	return (str3);
}

int ft_strchr(const char *str, char c)
 {
	int i;
	
	i = 0;
	if(str == NULL)
		return 0;
	while(str[i] != c && str[i] != '\0')
	i++;
	if(str[i] == '\0')
		return(1);
	if(str[i] == c)
		return (1);
	return 0;
} 