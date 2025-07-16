// void handle_heredoc(t_tree *tree, t_env *env, int *stop_herdoc)
// {
// 	t_redir_node *redir;
// 	pid_t pid;
// 	int fd;
// 	int status;
// 	int fdread;
// 	char *filename;

// 	if (!tree)
// 		return ;
// 	if (tree->kind == NODE_PIPE)
// 	{
// 		handle_heredoc(tree->left,env, stop_herdoc);
// 		handle_heredoc(tree->right,env, stop_herdoc);
// 		return ;
// 	}
// 	redir = tree->redirs;
// 	while (redir)
// 	{
// 		if (*stop_herdoc == 1)
// 			return;
// 		redir->ishd = 0;
// 		if (redir->kind == REDIR_HEREDOC)
// 		{
// 			redir->ishd = 1;
// 			filename = generate_filename();
// 			fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			fdread = open(filename, O_RDONLY, 0644);
// 			if (fd == -1 || fdread == -1)
// 			{
// 				perror("heredoc open");
// 				return ;
// 			}
// 			unlink(filename);
// 			free(filename);
// 			pid = fork();
// 			if (pid == -1)
// 			{
// 				perror("fork");
// 				return;
// 			}
			
// 			if (pid == 0)
// 			{
// 				handle_heredoc_signals();
// 				close(fdread);
// 				write_in_herdoc(redir, env, fd);
// 				exit(0);
// 			}
// 			else
// 			{
// 				close(fd);
// 				signal(SIGINT, SIG_IGN);
// 				waitpid(pid, &status, 0);
// 				exit_status(WEXITSTATUS(status), 0);
// 				if (WEXITSTATUS(status) == 1)
// 				{
// 					*stop_herdoc = 1;
// 					break;
// 				}
// 				redir->fd = fdread;
// 				redir->kind = REDIR_INPUT;
// 			}
// 		}
// 		redir = redir->next;
// 	}
// 	return ; 
// }
