/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:57:13 by eberkowi          #+#    #+#             */
/*   Updated: 2024/06/12 15:54:09 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex)
{
	create_command(&pipex);
    pipex.infile = open(pipex.argv[1], O_RDONLY);
    if (pipex.infile < 0)
        error_child(pipex, "Infile");
    dup2(pipex.infile, STDIN_FILENO);
    close(pipex.infile);
    dup2(pipex.current_fd[1], STDOUT_FILENO);
    close(pipex.current_fd[0]);
    close(pipex.current_fd[1]);
    execve(pipex.cmd_exec, pipex.cmd_args, pipex.envp);
}

void	middle_child(t_pipex pipex)
{
    create_command(&pipex);
    dup2(pipex.previous_fd, STDIN_FILENO);
    close(pipex.previous_fd);
    dup2(pipex.current_fd[1], STDOUT_FILENO);
    close(pipex.current_fd[0]);
    close(pipex.current_fd[1]);
    execve(pipex.cmd_exec, pipex.cmd_args, pipex.envp);
}

void	last_child(t_pipex pipex)
{
    create_command(&pipex);
    pipex.outfile = open(pipex.argv[pipex.argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (pipex.outfile < 0)
        error_child(pipex, "Outfile");
    dup2(pipex.outfile, STDOUT_FILENO);
    close(pipex.outfile);
    dup2(pipex.previous_fd, STDIN_FILENO);
    close(pipex.previous_fd);
    execve(pipex.cmd_exec, pipex.cmd_args, pipex.envp);
}

void	create_children(t_pipex pipex)
{
    int i;
    //FIRST AND MIDDLE CHILD
    while (pipex.position < pipex.argc - 4)
    {
        if (pipe(pipex.current_fd) < 0)
            error_parent(pipex, "Pipe");
        pipex.pid[pipex.position] = fork();
        if (pipex.pid[pipex.position] == 0 && pipex.position == 0)
            first_child(pipex);
        else if (pipex.pid[pipex.position] == 0)
            middle_child(pipex);
        close(pipex.current_fd[1]);
        if (pipex.previous_fd)
            close(pipex.previous_fd);
        pipex.previous_fd = pipex.current_fd[0];
        pipex.position++;
    }
    //LAST CHILD
    pipex.pid[pipex.position] = fork();
    if (pipex.pid[pipex.position] == 0)
        last_child(pipex);
    close(pipex.previous_fd);
    //WAIT FOR CHILDREN
    i = 0;
    while (i < pipex.argc - 3)
        waitpid(pipex.pid[i++], NULL, 0);
}
