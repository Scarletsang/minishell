# Minishell

TODO:

- [ ] universal error printer for the whole minishell
- [ ] execution reorganize enactments
- [ ] builtins
	- cd: It should also set the special varaible PWD to the current absolute path
	- pwd: It should not just read from the variable PWD
- [ ] signals, stopping a child process from parent using kill(), and then set the exit code to 128 + the signal number. A void * can be passed to the signal handler via sigaction(). This should enable the signal handler changing a state in minishell, avoiding the use of global variable. The following does not apply to the interactive mode of shell:
	- Control C sends a SIGINT signal, which is 2, so the exit code caused by such interruption is 130
	- Control \ sends a SIGQUIT signal, which is 3, so the exit code caused by such interruption is 131
- [ ] Set terminal to not show control characters
- [ ] readline