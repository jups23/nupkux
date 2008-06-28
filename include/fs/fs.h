#ifndef _FS_H
#define _FS_H

#include <kernel.h>

#define NODE_NAME_LEN 256

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

#define FS_TYPE_FAT32	0xB
#define FS_TYPE_INITRD	0x1120
#define FS_TYPE_DEVFS	0xDEF5

#define NR_OPEN		64

typedef struct _fs_node fs_node;
typedef struct _mountinfo mountinfo;

typedef void (*open_proto)(fs_node*);
typedef UINT (*read_proto)(fs_node*,UINT,UINT,UCHAR*);
typedef UINT (*write_proto)(fs_node*,UINT,UINT,UCHAR*);
typedef void (*close_proto)(fs_node*);
typedef struct dirent *(*readdir_proto)(fs_node*,UINT);
typedef fs_node *(*finddir_proto)(fs_node*,char *name);

struct dirent
{
	UINT d_ino;
	char d_name[NODE_NAME_LEN];
	USHORT d_namlen;
	UCHAR d_type;
};

typedef struct _node_operations {
	open_proto open;
	read_proto read;
	write_proto write;
	close_proto close;
	readdir_proto readdir;
	finddir_proto finddir;
} node_operations;

struct _fs_node {
	UINT mode;
	UINT uid;
	UINT gid;
	UCHAR flags;
	UINT inode;
	UINT size;
	UCHAR nlinks;
	mountinfo *mi; //impl
	node_operations *f_op;
	fs_node *ptr;
};

//For every mountpoint there is such one

typedef struct _vfs_nodes {
	UINT count;
	fs_node *nodes, *root;
} vfs_nodes;

struct _mountinfo {
	UINT fs_type;
	void *discr;
	fs_node *device;
	fs_node *mountpoint;
	vfs_nodes *nodes;
	mountinfo *next;
};

typedef struct file {
	USHORT mode;
	fs_node *node;
	UINT offset;
} FILE;

//VFS functions

extern void open_fs(fs_node *node, UCHAR read, UCHAR write);
extern UINT read_fs(fs_node *node, UINT offset, UINT size, UCHAR *buffer);
extern UINT write_fs(fs_node *node, UINT offset, UINT size, UCHAR *buffer);
extern void close_fs(fs_node *node);
extern struct dirent *readdir_fs(fs_node *node, UINT index);
extern fs_node *finddir_fs(fs_node *node, char *name);

//Managment of mountpoints

extern mountinfo *fs_add_mountpoint(UINT fs_type, void *discr, fs_node *mountpoint, fs_node *device, vfs_nodes *nodes);
extern UINT fs_del_mountpoint(mountinfo *mi);

//Variables

extern FILE *filep[NR_OPEN];
extern fs_node *fs_root;

//functions NOT in fs.c

extern fs_node *namei(char *filename);

#endif
