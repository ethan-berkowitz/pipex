/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:59:33 by eberkowi          #+#    #+#             */
/*   Updated: 2024/06/12 15:54:10 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_child(t_pipex *pipex)
{
    int i;

    if (pipex->cmd_args)
    {
        i = 0;
        while (pipex->cmd_args[i])
            free(pipex->cmd_args[i++]);
        free(pipex->cmd_args);
    }
}

void	free_parent(t_pipex *pipex)
{
    int i;
    
    if (pipex->split_path)
    {
        i = 0;
        while (pipex->split_path[i])
            free(pipex->split_path[i++]);
        free(pipex->split_path);
    }
}

int error_child(t_pipex pipex, char *error)
{
    perror(error);   
    exit (1);
}

int error_parent(t_pipex pipex, char *error)
{
    perror(error);
    exit (1);
}