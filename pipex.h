/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:03:57 by eberkowi          #+#    #+#             */
/*   Updated: 2024/06/12 15:54:10 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h> //write
#include <fcntl.h> //O_RDONLY
#include <stdio.h> //PERROR
#include <sys/wait.h> //waitpid
#include <stdlib.h> //exit

typedef struct s_struct
{
    int infile;
    int outfile;
    pid_t *pid;
    char **argv;
    int argc;
    char **envp;
    int current_fd[2]; //file descriptors for the pipe
    int previous_fd;
    int position;
    char *full_path; //whole path line before split
    char **split_path; //split up path line
    char **cmd_args; //the individual commands. example: "wc" "-l"
    char *cmd_exec; //the final command for the execve
}   t_pipex;

char    *get_command(t_pipex pipex);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int     error_parent(t_pipex pipex, char *error);
int     error_child(t_pipex pipex, char *error);
void	create_path(t_pipex *pipex);
void    create_children(t_pipex pipex);
void	create_command(t_pipex *pipex);
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);

#endif