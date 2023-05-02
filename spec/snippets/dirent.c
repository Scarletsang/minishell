/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:11:01 by htsang            #+#    #+#             */
/*   Updated: 2023/05/02 20:54:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DIR				*directory;
	struct dirent	*entry;

	directory = opendir(".");
	if (!directory)
		return (EXIT_FAILURE);
	entry = readdir(directory);
	while (entry)
	{
		if (entry->d_type == DT_REG)
			printf("detected a file: %s\n", entry->d_name);
		else if (entry->d_type == DT_DIR)
			printf("detected a directory: %s\n", entry->d_name);
		entry = readdir(directory);
	}
	if (closedir(directory) == -1)
	{
		printf("unable to close directory\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
