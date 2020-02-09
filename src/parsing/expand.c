#include "tilde_exp.h"
#include "param_exp.h"
#include "quotes.h"

static void	rm_quotes(char **str)
{
	char	*dup;
	char	*pdup;
	char	*pstr;
	int		qmode;
	int		old_qmode;

	if (!*str)
		return ;
	pstr = *str;
	dup = NULL;
	old_qmode = NO_QUOTE;
	while (*pstr)
	{
		if ((qmode = get_qmode(old_qmode, *pstr)) != old_qmode && !dup)
		{
			dup = ft_strncat(ft_strnew(ft_strlen(*str)), *str, pstr - *str);
			pdup = dup + (pstr - *str);
		}
		else if ((qmode == old_qmode || qmode == (old_qmode & ~BSQUOTE)) && dup)
			*pdup++ = *pstr;
		old_qmode = qmode;
		++pstr;
	}
	*str = dup ? ft_strcpy(*str, dup) : *str;
	ft_memdel((void **)&dup);
}


char		*expand(t_sh_data *shd, char *str)
{
	char	*expanded;

	if ((expanded = ft_strdup(str)))
		tilde_exp(shd, &expanded);
	if (expanded)
		param_exp(shd, &expanded);
	if (expanded)
		rm_quotes(&expanded);
	return (expanded);
}
