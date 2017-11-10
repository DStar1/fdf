/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntdelim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 00:17:53 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/10 00:22:34 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cntdelim(const char *str, int c)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}
