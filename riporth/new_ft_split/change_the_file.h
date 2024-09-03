
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/* ft_toke_utils.c */
char	*list_length_create(const char *str, const int *i);
char	*fill_qoute_case(const char *str, char *list, int *i, char a);
char	*fill_word(const char *str, char *list, int *i);
char	**ft_token_fill(const char *str, char **list);

/* ft_token_split.c */
int		token_count_words(const char *str);
char	**ft_token_split(char const *s);
char	*fill_direct(const char *str, char *list, int *i);

/**
 * uitls 2/*/

 int	count_qoute(const char *str, int i, char a);