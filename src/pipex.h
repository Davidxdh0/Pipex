/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:17:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/05 19:19:48 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>

typedef struct s_data
{
	char	**argv;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
	char	**paths;
	char	*cmd;
	int		flag;
	char	*path;
	char	*envps;
	int		i;
}	t_data;

//pipex.c
//int	main(int argc, char **argv, char **envp);
int		flow(t_data *data, char **envp);

//process.c
int		access_path(t_data *data, int cmd);
void	exec_command(int cmd, t_data *data, char **envp);
void	child_process(t_data *data, int *fd, char **envp);
void	parent_process(t_data *data, int *fd, char **envp);
void	exception_messages(t_data *data, int cmd);

//free.c
// void	test(t_data *data);
void	free_arr(char **arg);
void	clean_exit(char *message, int errormessage);
void	perror_exit(int errornumber, char *msg);
void	message(char *msg);
char	*env_var(char **envp, t_data *data);
void	free_all(t_data *data);

//path.c
void	cmd_paths(t_data *data);
void	input_parse(t_data *data, char **argv, char **envp, int cmd);
void	relat_path(t_data *data, int cmd);
void	path_splitter(t_data *data);
char	*path_split(t_data *data, int cmd);

//exceptions.c
void	awk(t_data *data, int cmd);

#endif