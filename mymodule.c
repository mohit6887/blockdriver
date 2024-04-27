#include "headers.h"
#include "decleration.h"
struct Dev *bdev;
int majorno,nsectors,hardsect_size;
//int size=1024;
/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init my_init(void) {
	printk("Hello, Kernel!\n");
	int ret;
	majorno =MAJORNO;
	nsectors=NSECTORS;
	hardsect_size=HARDSECT_SIZE;
	ret=register_blkdev(majorno,DEVNAME);
	if(ret<0)
	{
                printk(KERN_ERR "register_blkdev() failure\n");
		goto OUT;

	}
	printk(KERN_INFO"mAJOR No :%d\n",majorno);
	bdev=kmalloc(sizeof(struct Dev),GFP_KERNEL);
	if(!bdev)
	{
		printk(KERN_ERR"kmalloc() failure\n");
		kfree(bdev);
		unregister_blkdev(majorno,DEVNAME);
	}
	bdev->size=nsectors*hardsect_size;
	bdev->data=vmalloc(bdev->size);
	
	if(!bdev->data)
        {
		kfree(bdev);
                printk(KERN_ERR"vmalloc() failure\n");
                unregister_blkdev(majorno,DEVNAME);
        }
	spin_lock_init(&bdev->lock);

	printk(KERN_INFO"End:%s\n",__func__);
	return 0;
OUT:
	printk(KERN_ERR"eND (ERROR): %s\n",__func__);
	return -1;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit my_exit(void) {
	vfree(bdev->data);
	kfree(bdev);
	unregister_blkdev(majorno,DEVNAME);
	printk("Goodbye, Kernel\n");

}

module_init(my_init);
module_exit(my_exit);


