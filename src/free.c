/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 14:11:22 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/26 11:10:01 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
		free(arg[i++]);
	free(arg);
}

void	clean_exit(char *message, int errornumber)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(errornumber);
}

void	perror_exit(int errornumber, char *msg)
{
	ft_putstr_fd("./pipex ", 2);
	perror(msg);
	exit(errornumber);
}

void	message(char *msg)
{
	ft_putstr_fd(msg, 2);
}

void	free_all(t_data *data)
{
	if (data->paths)
		free_arr(data->paths);
	if (data->path)
		free(data->path);
	if (data->cmd1)
		free_arr(data->cmd1);
	if (data->cmd2)
		free_arr(data->cmd2);
	if (data->cmd)
		free(data->cmd);
	if (data->envp)
		free_arr(data->envp);
}

// void	test(t_data *data)
// {
// 	ft_putstr_fd("argv ", 2);
// 	ft_putstr_fd(data->argv[0], 2);
// 	ft_putstr_fd("\ncmd1 ", 2);
// 	ft_putstr_fd(data->cmd1[0], 2);
// 	ft_putstr_fd("\ncmd1 ", 2);
// 	ft_putstr_fd(data->cmd1[1], 2);
// 	ft_putstr_fd("\ncmd 2 ", 2);
// 	ft_putstr_fd(data->cmd2[0], 2);
// 	ft_putstr_fd("\ncmd 2 ", 2);
// 	ft_putstr_fd(data->cmd2[1], 2);
// 	ft_putstr_fd("\npath ", 2);
// 	ft_putstr_fd(data->path, 2);
// 	ft_putstr_fd("\ndata->envps", 2);
// 	ft_putstr_fd(data->envps, 2);
// 	ft_putstr_fd("\n", 2);
// }