#include "../src/libft/includes/libft.h"

int	main(void)
{
	char	*input;
	int		rd;

	ft_printf("$> ");
	rd = get_next_line(0, &input);
	if (*input)
	{
		ft_printf("input is: %s\n", input);
		free(input);
	}
/*	while ((rd = get_next_line(0, &input)) > 0)
	{
		if (rd)
		{
			if (*input)
				ft_printf("input is: %s\n$> ", input);
			else
				ft_printf("$> ");
			free(input);
		}
	}
*/
	return (0);
}
