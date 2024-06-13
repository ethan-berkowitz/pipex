/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:48:26 by eberkowi          #+#    #+#             */
/*   Updated: 2024/06/12 15:59:59 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> //REMOVE

static char    *get_cmd_exec(t_pipex pipex)
{
    char    *tmp;
    char    *result;

	while (*pipex.split_path)
	{
    	tmp = ft_strjoin(*pipex.split_path, "/");
		if (!tmp)
			return (NULL);
		result = ft_strjoin(tmp, pipex.cmd_args[0]);
		if (!result)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		tmp = NULL;
		if (access(result, F_OK) == 0)
			return (result);
		free(result);
		result = NULL;
		pipex.split_path++;
	}
    return (NULL);
}

void	create_command(t_pipex *pipex)
{
	if (ft_strncmp("./", pipex->argv[pipex->position + 2], 2) == 0)
		pipex->cmd_exec = pipex->argv[pipex->position + 2];
	else
	{
		pipex->cmd_args = ft_split(pipex->argv[pipex->position + 2], ' ');
    	pipex->cmd_exec = get_cmd_exec(*pipex);
    	if (!pipex->cmd_exec)
        	error_child(*pipex, "Command not found\n");
	}
}

static char 	*find_path(t_pipex *pipex)
{
    while (ft_strncmp("PATH", *pipex->envp, 4) != 0)
		pipex->envp++;
	if (!*pipex->envp)
		error_parent(*pipex, "No such file or directory\n");
	return (*pipex->envp + 5);
}

void	create_path(t_pipex *pipex)
{
	pipex->full_path = find_path(pipex);
	pipex->split_path = ft_split(pipex->full_path, ':');
}
