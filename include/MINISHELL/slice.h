/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:59:49 by htsang            #+#    #+#             */
/*   Updated: 2023/06/16 22:19:58 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGSLICE_H
# define STRINGSLICE_H

# include <stddef.h>

typedef struct s_slice
{
	void	*content;
	size_t	size;
}				t_slice;

typedef t_slice	t_string_slice;

char	*string_slice_to_cstring(t_string_slice slice);

char	*string_slice_content(t_string_slice *slice);

#endif