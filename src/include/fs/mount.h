/*
 *  Copyright (C) 2008 Sven Köhler
 *
 *  This file is part of Nupkux.
 *
 *  Nupkux is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Nupkux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Nupkux.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MOUNT_H
#define _MOUNT_H

#include <fs/vfs.h>

#ifndef _VFSMOUNT
#define _VFSMOUNT
typedef struct _vfsmount vfsmount;
#endif

struct _vfsmount {
	const char *devname;
	const char *dirname;
	UINT flags;
	super_block *sb;
	vfsmount *next;
};

#endif
