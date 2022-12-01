#include "../../includes/minishell.h"

void	ft_set_term(t_shell *shell)
{
	tcgetattr(0, &shell->new);
	shell->new.c_lflag &= ~ECHOCTL;
	shell->new.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->new);
}

void	ft_unset_term(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->old);
}

void	ft_signal_reset(int nothing)
{
	(void)nothing;
}

int	ft_signal_handle(int pid)
{
	if (WIFSIGNALED(pid))
	{
		if (WTERMSIG(pid) == SIGQUIT)
		{
			printf("Quit: 3\n");
			g_return_value = 131;
			return (1);
		}
		else if (WTERMSIG(pid) != SIGPIPE)
		{
			g_return_value = 130;
			printf("\n");
			return (1);
		}
	}
	return (0);
}

void	ft_sig_ignit(int nothing)
{
	(void)nothing;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}