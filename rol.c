/* Copyright (c) 2016, Michael Zuo. ISC License. */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>

int main(int argc, char const *const *const argv) {
	char buf[PATH_MAX];

	if (argc < 4)
		errx(2, "usage: %s via dst... end", *argv);

	for (int n = 3; n < argc; n++) {
		char const *dst = buf;
		ssize_t len = readlink(argv[n], buf, sizeof(buf));
		if (len != -1)
			buf[len] = 0;
		else if (errno == ENOENT)
			continue;
		else if (errno == EINVAL)
			dst = argv[n];
		else
			err(n, "readlink: %s", argv[n]);

		if (symlink(dst, argv[1]) == -1)
			err(n, "symlink: %s", argv[1]);

		if (rename(argv[1], argv[n-1]) == -1)
			err(n, "rename: %s to %s", argv[1], argv[n-1]);
	}
}
