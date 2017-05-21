#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "env.h"
# include "termios.h"
# include "term.h"
# define KEY_ESCAPE 0x1B
# define KEY_SPACE 0x20
# define KEY_UP 0x415B1B
# define KEY_DOWN 0x425B1B
# define KEY_RIGHT 0x435B1B
# define KEY_LEFT 0x445B1B
# define KEY_ENTER 0xA
# define KEY_BACKSPACE 0x7F
# define KEY_DELETE 0x7E335B1B
# define KEY_HOME 4741915
# define KEY_END 4610843 
# define KEY_SHIFT_UP 71683997260571
# define KEY_SHIFT_DOWN 72783508888347

typedef struct		s_line
{
	unsigned int		pos;
	unsigned int		len;
	char		*buff;
	struct termios	*old_term;
}			t_line;

typedef struct		s_edit_func
{
	unsigned long long	keycode;
	int			(*f)(t_line *);
}			t_edit_func;

void	edit_line_init(void);
char	*edit_get_input(t_env *env);
void	conf_term_in(void);
void	conf_term_out(void);
void	put_termcap(char *capacity);
t_line	*line(void);

int		edit_end(t_line *line);
int		edit_home(t_line *line);
int		edit_right(t_line *line);
int		edit_left(t_line *line);
int	edit_backspace(t_line *line);
void	edit_add(int keycode, t_line *line);
void	edit_refresh(int signum, t_env *env);

void	put_prompt(t_env *env);

# endif
