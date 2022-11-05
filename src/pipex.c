/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:16:14 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/05 17:52:37 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	flow(t_data *data, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (pipe(fd) < 0)
		message("pipe went wrong");
	pid1 = fork();
	if (pid1 == 0)
		child_process(data, fd, envp);
	else
	{
		waitpid(pid1, NULL, 0);
		parent_process(data, fd, envp);
	}
	clean_exit("flow", 5000);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 5)
	{
		data.envp = envp;
		data.argv = argv;
		data.flag = 0;
		flow(&data, envp);
	}
	else
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		return (10);
	}
	return (0);
}
