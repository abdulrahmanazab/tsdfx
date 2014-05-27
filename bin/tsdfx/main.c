/*-
 * Copyright (c) 2013-2014 Universitetet i Oslo
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if HAVE_BSD_UNISTD_H
#include <bsd/unistd.h>
#endif

#include "tsdfx.h"
#include "tsdfx_log.h"

#if HAVE_SETPROCTITLE_INIT
extern char **environ;
#endif

static void
usage(void)
{

	fprintf(stderr, "usage: tsdfx -m mapfile\n");
	exit(1);
}

int
main(int argc, char *argv[])
{
	const char *mapfile;
	int opt;

#if HAVE_SETPROCTITLE_INIT
	setproctitle_init(argc, argv, environ);
#endif
#if HAVE_SETPROCTITLE
	setproctitle("master");
#endif

	mapfile = NULL;
	while ((opt = getopt(argc, argv, "m:v")) != -1)
		switch (opt) {
		case 'm':
			mapfile = optarg;
			break;
		case 'v':
			++tsdfx_verbose;
			break;
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();
	if (mapfile == NULL)
		usage();

	if (tsdfx_log_init() != 0)
		exit(1);
	if (tsdfx_init(mapfile) != 0)
		exit(1);
	// add daemonization etc.
	tsdfx_run(mapfile);
	exit(0);
}
