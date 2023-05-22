/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:01:52 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/05/22 02:56:10 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINISHELL/vector.h"

void	vector_set_char(void *buffer, void *character)
{
	*(char *) buffer = *(char *) character;
}

void	vector_set_int(void *buffer, void *integer)
{
	*(int *) buffer = *(int *) integer;
}

void	vector_set_string(void *buffer, void *string)
{
	*(char **) buffer = (char *) string;
}

void	vector_set_ptr(void *buffer, void *ptr)
{
	*(void **) buffer = ptr;
}
