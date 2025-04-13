/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   signal_util.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jiepark <jiepark@student.42berlin.de>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/30 19:00:20 by jiepark		   #+#	#+#			 */
/*   Updated: 2025/03/30 19:00:23 by jiepark		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	set_terminal_print_off(void);
void	set_terminal_print_on(void);

void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);		// Get cur terminal settings
	term.c_lflag &= ~(ECHOCTL);			// stop printing ^C, ctr D
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply changes immediately
}

void	set_terminal_print_on(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;        // Enable printing of ^C, ctr D
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
