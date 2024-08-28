
/* ft_toke_utils.c */
char	*list_length_create(const char *str, const int *i);
char	*fill_qoute_case(const char *str, char *list, int *i, char a);
char	*fill_word(const char *str, char *list, int *i);
char	**ft_token_fill(const char *str, char **list);

/* ft_token_split.c */
int		count_qoute(const char *str, int i, char a);
int		token_count_words(const char *str);
char	**ft_token_split(char const *s);