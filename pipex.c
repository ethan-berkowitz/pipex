/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:53:11 by eberkowi          #+#    #+#             */
/*   Updated: 2024/06/12 15:54:07 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> //REMOVE

static void	create_pids(t_pipex *pipex)
{
	pipex->pid = (pid_t *)malloc((pipex->argc - 3) * sizeof(pid_t));
	if (!pipex->pid)
		exit (1);
}

int main(int argc, char *argv[], char *envp[])
{
    t_pipex pipex;
    
    if (argc < 5)
        error_parent(pipex, "Invalid number of arguments");
    pipex.argc = argc;
    pipex.argv = argv;
    pipex.envp = envp;
    pipex.position = 0;
    create_path(&pipex);
    create_pids(&pipex);
    create_children(pipex);
    free_parent(&pipex);
    return (0);
}
