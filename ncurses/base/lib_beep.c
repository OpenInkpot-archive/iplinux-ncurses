/****************************************************************************
 * Copyright (c) 1998-2005,2009 Free Software Foundation, Inc.              *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *
 *     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *
 *     and: Thomas E. Dickey                        1996-on                 *
 *     and: Juergen Pfeifer                         2009                    *
 ****************************************************************************/

/*
 *	beep.c
 *
 *	The routine beep().
 *
 */

#include <curses.priv.h>
#include <term.h>		/* beep, flash */

MODULE_ID("$Id: lib_beep.c,v 1.11 2009/02/15 00:32:06 tom Exp $")

/*
 *	beep()
 *
 *	Sound the current terminal's audible bell if it has one.   If not,
 *	flash the screen if possible.
 *
 */

NCURSES_EXPORT(int)
NCURSES_SP_NAME(beep) (NCURSES_SP_DCL0)
{
    int res = ERR;

    T((T_CALLED("beep()")));

    /* FIXME: should make sure that we are not in altchar mode */
    if (cur_term == 0) {
	res = ERR;
    } else if (bell) {
	TPUTS_TRACE("bell");
	res = putp(bell);
	_nc_flush();
    } else if (flash_screen) {
	TPUTS_TRACE("flash_screen");
	res = putp(flash_screen);
	_nc_flush();
    }

    returnCode(res);
}

#if NCURSES_SP_FUNCS
NCURSES_EXPORT(int)
beep(void)
{
    return NCURSES_SP_NAME(beep) (CURRENT_SCREEN);
}
#endif
