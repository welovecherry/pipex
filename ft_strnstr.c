/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:43:21 by jungmiho          #+#    #+#             */
/*   Updated: 2023/10/11 22:46:22 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_all_same(char *haystack_ptr, size_t h_idx, char *needle_ptr, size_t len)
{
	size_t	n_idx;
	size_t	total_idx;

	n_idx = 0;
	total_idx = h_idx;
	while (needle_ptr[n_idx] && (total_idx < len))
	{
		if (needle_ptr[n_idx] != haystack_ptr[h_idx + n_idx])
		{
			return (0);
		}
		else
		{
			n_idx++;
			total_idx = n_idx + h_idx;
		}
	}
	if (needle_ptr[n_idx] == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*needle_ptr;
	char	*haystack_ptr;
	size_t	h_idx;

	haystack_ptr = (char *)haystack;
	needle_ptr = (char *)needle;
	if (*needle == '\0')
		return (haystack_ptr);
	h_idx = 0;
	while (haystack_ptr[h_idx] && (h_idx < len))
	{
		if ((haystack_ptr[h_idx] == needle_ptr[0]) \
		&& (is_all_same(haystack_ptr, h_idx, needle_ptr, len)))
			return (&haystack_ptr[h_idx]);
		h_idx++;
	}
	return (0);
}
