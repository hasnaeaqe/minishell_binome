/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:22 by haqajjef          #+#    #+#             */
/*   Updated: 2025/05/06 10:12:14 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	ft_cd(char **argv)
{
	int		r;
	char	*path;

	if (!argv[1])
	{
		perror("path manquant!");
		return ;
	}
	path = argv[1];
	r = chdir(path);
	if (r == -1)
	{
		perror("operation echoue!");
	}
}

// int	main(int argc, char**argv)
// {
// 	if (argc > 1)
// 	{
// 		ft_cd(argv);
// 	}
// 	printf("new cwd : %s\n", getcwd(NULL, 0));
// }
