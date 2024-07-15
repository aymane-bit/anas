int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	token_ptr	tokens_list;
	t_env		*env;

	signal_handler();
	env = init_env(envp);
	while (true)
	{
		if (isatty(STDIN_FILENO) == true)
			user_input = readline("kssh$ ");
		if (user_input == NULL)
			exit(EXIT_SUCCESS);
		if (ft_strncmp(user_input, "\0", 1) != 0)
			add_history(user_input);
		tokens_list = lexer(user_input);
		// add heredoc handler here.
		if (parser_tokens(tokens_list,env) == false)
		{
			free_all(tokens_list, user_input, NULL);
			continue;
		}
		tokens_expander(tokens_list, envp);
		tokens_list_optimizer(&tokens_list);
		syntax_algo(tokens_list);
		// check_tokens(tokens_list);
		executor(tokens_list, envp, user_input);
		free_all(tokens_list, user_input, NULL);
	}
	return (EXIT_SUCCESS);
}
