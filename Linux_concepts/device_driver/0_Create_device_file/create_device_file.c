/***************************************************************************
The dev_t type (defined in <linux/types.h>) is used to hold device numbers-both
the major and minor parts. dev_t is a 32-bit quantity with 12 bits set aside for
the major number and 20 for the minor number.
----------
dev_t dev = MKDEV(235, 0);
register_chrdev_region(dev, 1, "rk_device"); To view"rk_device" cat /proc/devices
----------
-------------------------------Dynamically Allocating--------------------------
If we dont want fixed major and minor number please use this method. This method
will allocate the major number dynamically to your driver which is available.
---------------
int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
--------------
"dev" is an output-only parameter that will, on successful completion, hold the
first number in your allocated range.

"firstminor" should be the requested first minor number to use; it is usually 0.

"count" is the total number of contiguous device numbers you are requesting.

"name" is the name of the device that should be associated with this number
range; it will appear in /proc/devices and sysfs.

alloc_chrdev_region(&dev, 0, 1, "rk_device");To view"rk_device" cat /proc/devices
-------------------------Manually Creating Device File------------------------
We can create the device file manually by using mknod.

mknod -m <permissions> <name> <device type> <major> <minor>

<name> – your device file name that should have full path (/dev/name)
<device type> – Put c or b
c – Character Device
b – Block Device

<major> – major number of your driver
<minor> – minor number of your driver
-m <permissions> – optional argument that sets the permission bits of the ne
device file to permissions

Example: sudo mknod -m 666 /dev/etx_device c 246 0
Advantages:
->Anyone can create the device file using this method.
->You can create the device file even before load the driver.
-------------------------Automatic creation-------------------------------

  The automatic creation of device files can be handled with udev. Udev is the
device manager for the Linux kernel that creates/removes device nodes in the
/dev directory dynamically.

****************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

dev_t dev =0;

static struct class *dev_class;

static int __init rk_init(void)
{
	/*Allocate Major and minor number, This will register the device name
	  in /proc/devices  with major and minor num */
	if((alloc_chrdev_region(&dev, 0, 1, "rk_device")) < 0)
	{
	    printk(KERN_INFO "Cannot allocate Major number\n");
	    return -1;
	}
	printk(KERN_INFO "Major = %d Minor = %d\n",MAJOR(dev), MINOR(dev));
	/*Once we do insmod above code will give us MJ, MI then we can use those
	  numbers incase if we create device file mannually if not follow below
	*/
	/*Creating struct class*/
	if((dev_class = class_create(THIS_MODULE, "krkreddy")) == NULL)
	{
	    printk(KERN_INFO "Cannot create struct class for device\n");
	    goto r_class;
	}
	/*Creating device*/
	if(device_create(dev_class, NULL, dev, NULL,"KRKReddy_RR") == NULL)
	{
	    printk(KERN_INFO "Cannot create struct class for device\n");
	    goto r_device;
	}
	printk(KERN_INFO "Kernel module inserted successfully\n", __func__);
	return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

void __exit rk_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Kernel module removed successfully\n", __func__);
}

module_init(rk_init);
module_exit(rk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRKReddy");
MODULE_DESCRIPTION("Automatic creation of device file");
MODULE_VERSION("1.3");
