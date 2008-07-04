/*
 *  Copyright (C) 2007,2008 Sven Köhler
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

#include <drivers/drivers.h>
#include <kernel/ktextio.h>
#include <drivers/fdc.h>


static UINT drv_stdout_write(fs_node *node, UINT offset, UINT size, UCHAR *buffer)
{
	UINT i=size;
	
	while (i--) 
		_kputc(*(buffer++));
	
	return size;
}

node_operations stdout_ops = {0,0,&drv_stdout_write,0,0,0};

UINT setup_drivers(fs_node *devfs)
{
	if (!devfs) return 2;
	
	devfs_register_device(devfs,"stdout",0222,FS_UID_ROOT,FS_GID_ROOT,FS_CHARDEVICE,&stdout_ops);
	devfs_register_device(devfs,"stderr",0222,FS_UID_ROOT,FS_GID_ROOT,FS_CHARDEVICE,&stdout_ops);
	init_floppy(devfs);
	return 0;
}