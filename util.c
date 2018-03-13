/*
 * Copyright (c) 2018 Jan Klemkow <j.klemkow@wemelug.de>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool
bell_match(const char *str, const char *regex_file)
{
	FILE *fh = NULL;
	char cmd[BUFSIZ];

	if (access(regex_file, R_OK) == -1)
		return true;

	snprintf(cmd, sizeof cmd, "exec grep -qf %s", regex_file);

	if ((fh = popen(cmd, "w")) == NULL)
		err(EXIT_FAILURE, "popen");

	if (fputs(str, fh) == EOF)
		err(EXIT_FAILURE, "fputs");

	if (pclose(fh) == 0)
		return true;

	return false;
}
