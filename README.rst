rol - rotate a set of symlinks
==============================

Usage
-----

::

    rol via dst... end

Description
-----------

The ``rol`` utility changes the destinations of one or more symlinks atomically
using rename(2) to move a newly created symlink from *via* to its destination.
During this process, a symlink is always present at each location *dst* if one
existed beforehand, so path resolution errors due to transient symlink absence
do not occur: unlike e.g. ``ln -f``, ``rol`` does not unlink each *dst* before
creating a new symlink in the same location.

Each link *dst* is updated to point to whatever the next *dst* currently points
to; the last *dst* is updated to point at *end*.

Caveats
~~~~~~~

Symlink replacement is only atomic in the context of a single change. When more
than one link is being updated, ``rol`` is subject to race conditions if more
than one instance is run simultaneously on a set of links; in this case, only
the final *dst* is guaranteed to be updated correctedly to *end*.

If any of the *dst* files are not links, the preceding *dst* will be updated to
its current location, just as if it were *end*: internally, ``rol`` does not
actually distinguish *end* from intermediate *dst* links, except that the last
argument on the command line does not get updated! Since an intermediate *dst*
file will be subsequently replaced with another link, this is unlikely to be a
useful operation.

Conversely, if *end* is a symlink, the last *dst* will be updated to point to
its target, rather than *end* itself. This might be situationally useful. If
you really need a symlink to a symlink, you can provide a symlink to the
symlink as *end* to ``rol``.

``rol`` silently skips links if it can't find a destination for them. This is
intended to allow ``rol`` to be called with a list of names which do not all
exist, so that new entries are added as needed.

Gratuitous use of BSD error functions.

License
-------

ISC License, see COPYING.
