/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:04:11 by rkulahin          #+#    #+#             */
/*   Updated: 2018/10/26 10:19:16 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *app, size_t n)
{
	size_t	i;
	int		j;
	size_t	dest_n;
	size_t	app_n;

	dest_n = ft_strlen(dest);
	app_n = ft_strlen(app);
	j = 0;
	i = dest_n;
	if (n > dest_n)
		ft_strncat(dest, app, n - dest_n - 1);
	else if (dest_n > n)
		return (app_n + n);
	return (dest_n + app_n);
}
