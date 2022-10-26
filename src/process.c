/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:49:56 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/26 11:09:34 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	access_path(t_data *data, int cmd)
{
	if (cmd == 0 && !access(data->cmd1[0], X_OK))
	{
		data->path = data->cmd1[0];
		return (1);
	}
	else if (cmd == 1 && !access(data->cmd2[0], X_OK))
	{
		data->path = data->cmd2[0];
		return (1);
	}
	return (0);
}

void	exception_messages(t_data *data, int cmd)
{
	if (data->argv[cmd + 2][0] == '\0' && data->flag < 5)
	{
		data->flag = 2;
		clean_exit("./pipex permission denied", 126);
	}
	if (cmd == 1 && !data->cmd2[0] && data->flag != 3)
		clean_exit("./pipex command not found: ", 127);
	if (cmd == 0 && data->flag == 1 && data->argv[cmd + 2][0] != '\0')
		message("./pipex command not found: \n");
}

void	exec_command(int cmd, t_data *data, char **envp)
{
	char	*temp;

	input_parse(data, data->argv, envp, cmd);
	exception_messages(data, cmd);
	if (!access_path(data, cmd))
	{
		temp = path_split(data, cmd);
		if (!temp)
		{
			if (cmd == 0)
				perror_exit(127, *data->cmd1);
			else
				perror_exit(127, *data->cmd2);
		}
	}
	if (cmd == 0)
	{
		if (execve(data->path, data->cmd1, data->envp) == -1)
			perror_exit(127, data->path);
	}
	else
		if (execve(data->path, data->cmd2, data->envp) == -1)
			perror_exit(127, data->path);
	clean_exit("exec_command fails", 127);
}

void	child_process(t_data *data, int *fd, char **envp)
{
	int	infile;

	infile = open(data->argv[1], O_RDONLY, 0777);
	if (infile == -1)
		perror_exit(1, data->argv[1]);
	dup2(fd[1], 1);
	close(fd[0]);
	dup2(infile, 0);
	close(infile);
	exec_command(0, data, envp);
}

void	parent_process(t_data *data, int *fd, char **envp)
{
	int	outfile;

	outfile = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		perror_exit(1, data->argv[4]);
	dup2(fd[0], 0);
	close(fd[1]);
	dup2(outfile, 1);
	close(outfile);
	exec_command(1, data, envp);
}
