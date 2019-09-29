#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>


#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int32_t *kptr;
dev_t dev;
static struct class *dev_class;
static struct cdev rk_cdev;

static int __init rk_init(void);
static void __exit rk_exit(void);
static int rk_open(struct inode *inode, struct file *file);
static int rk_release(struct inode *inode, struct file *file);
static ssize_t rk_read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t rk_write(struct file *file, const char *buf, size_t len, loff_t *off);
static long rk_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops=
{
   .open = rk_open,
   .release =rk_release,
   .read = rk_read,
   .write = rk_write,
   .unlocked_ioctl = rk_ioctl,
};

static int rk_open(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "%s\n",__func__);
  kptr = kmalloc(1024, GFP_USER);
  return 0;
}

static int rk_release(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "%s\n",__func__);
  return 0;
}

static ssize_t rk_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "%s\n",__func__);
  return 0;
}

static ssize_t rk_write(struct file *file, const char *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "%s\n",__func__);
  return 0;
}

static long rk_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int32_t *ptr, *tkptr, i;
    printk(KERN_INFO "Inside ioctl\n");
    switch(cmd){
	    case WR_VALUE:
		    ptr = (int32_t *)arg;
		    tkptr = kptr;
		    printk(KERN_INFO "Inside Write ioctl\n");
		    /*Here if we don't use 'copy_from_user' API if we directly
		      try coping using userspace buffer virtual address incase
		      if the physicall memory is not mapped in that case
		      page_fault exception occurs if so kernel will not handle
		      faults so kernel panic happens to avoid this we have
		      copy_to_user and copy_from_user APIs which will handle
		      page_fault exceptions
		      TO test allocate 4k size buffer in userspace app and
		      without touching it pass it to the kernel driver and in
		      side driver try coping without copy to/from user APIs
		      then kernel panic you can see in dmesg. below command
		      helps you check the status of whether kernel panic enabled
		      sudo sysctl -a|grep kernel|grep -e panic_on_oops -e sysrq
		      */
		    copy_from_user(kptr,ptr, 1024);
		    for(i = 0; i < 1024; i++)
		    {
			    printk(KERN_INFO "%x ",*tkptr++);
		    }
		    break;
	    case RD_VALUE:
		    ptr = (int32_t *)arg;
		    tkptr = kptr;
		    printk(KERN_INFO "Inside Read ioctl\n");
		    for(i = 0; i < 1024; i++)
		    {
			    *tkptr = ~(*tkptr);
			    tkptr++;
		    }
		    copy_to_user(ptr, kptr, 1024);
		    break;
    }
    return 0;
}

int __init rk_init(void)
{

    /*Allocate Major number*/
   if((alloc_chrdev_region(&dev, 0, 1, "KRKReddy")) < 0){
	   printk(KERN_ERR "Cannot allocate major number\n" );
	   return -1;
   }

   printk(KERN_INFO "Major num = %d Minor num = %d\n", MAJOR(dev), MINOR(dev));

    /*Create character device structure*/
   cdev_init(&rk_cdev, &fops);

    /*Adding character device to the system*/
   if((cdev_add(&rk_cdev, dev, 1)) < 0){
	   printk(KERN_INFO "Cannot add the device to the system\n");
	   goto r_class;
   }

   /*creating struct class*/
   if((dev_class = class_create(THIS_MODULE, "KRKReddy")) == NULL){
	   printk(KERN_INFO "Cannot create struct class\n");
	   goto r_class;
   }

  if((device_create(dev_class, NULL, dev, NULL, "KRKReddy")) == NULL){
	   printk(KERN_INFO "Cannot create device\n");
	   goto r_device;
  }

  printk(KERN_INFO "Device driver inserted successfully...!!\n");
  return 0;

r_device:
  class_destroy(dev_class);
r_class:
  unregister_chrdev_region(dev, 1);
  return -1;
}

void __exit rk_exit(void)
{
  device_destroy(dev_class, dev);
  class_destroy(dev_class);
  cdev_del(&rk_cdev);
  unregister_chrdev_region(dev, 1);
  printk(KERN_INFO "Device driver removed successfully...!!\n");
}

module_init(rk_init);
module_exit(rk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRKReddy");
MODULE_DESCRIPTION("Device driver with basic file operations sudo code");
MODULE_VERSION("1.5");
