#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	parse_line(char *str, t_commands *cmds, t_token *token)
{
	int		i;
	char	*word;

	i = -1;
	word = 0;
	while (str[++i])
	{
		if (str[i] == " ")
			end_of_word(cmds, token, word);
		else if (str[i] == "\"")
			parse_double_quotation(token, word);
		else if (str[i] == "\'")
			parse_single_quotation(token, word);
		else if (str[i] == "<" || str[i] == ">")
			parse_redirection(token, word);
		else if (str[i] == "|")
			parse_pipe(cmds, token);
		else if (str[i] == "$")
			parse_dollar(cmds, token, word);
		else
			word = make_word(word, str[i]);
		if (token->heredoc == 1)
			read_heredoc(cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	int			temp_fd;
	t_commands	*cmds;
	t_token		*token;

	str = 0;
	while (1)
	{
		str = readline("minishell> : ");
		init_structures(cmds, token, envp); // cmds, token 구조체 할당 및 값 초기화
		parse_line(str, cmds, token); // 한 캐릭터씩 읽으면서 구조체에 실행시킬 명령어 저장
		execute_cmds(cmds); // 명령어 실행
		add_history(str); // line 저장
		free_line(str, cmds, token); // 사용이 끝난 line, 커맨드, 토큰 구조체 free
		if (!str)
			exit_shell();
	}
}

//exit long long 범위까지 256으로 나눠서 exit값 반환