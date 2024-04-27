
#ifndef DEBUG
#define DEVNAME  "blkdev"
#endif
#ifndef DEBUG
#define MAJORNO 0
#endif
#ifndef DEBUG
#define NSECTORS 128
#endif
#ifndef DEBUG
#define HARDSECT_SIZE 1024
#endif

extern int majorno,nsectors,hardsect_size;
struct Dev
{
	int size;
	u8 *data;
	short users;
	spinlock_t lock;

};
extern struct Dev *bdev;



