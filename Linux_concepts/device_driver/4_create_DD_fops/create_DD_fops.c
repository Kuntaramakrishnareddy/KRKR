/***********************************************************************
 In linux kernel "struct inode" structure is used to represent files. Therefore,
it is different from the file structure that represents an open file descriptor.
There can be numerous file structures representing multiple open descriptors on
a single file, but they all point to a single inode structure.

 The inode structure contains a great deal of information about the file. As a
general rule, cdev structure is useful for writing driver code:

 struct cdev is one of the elements of the inode structure. As you probably may
know already, an inode structure is used by the kernel internally to represent
files. The 'struct cdev' is the kernel’s internal structure that represent
char devices. This field contains a pointer to that structure when the inode
refers to a char device file.
-----------
struct cdev {
    struct kobject kobj;
    struct module *owner;
    const struct file_operations *ops;
    struct list_head list;
    dev_t dev;
    unsigned int count;
};
------------

 The file_operations structure is how a char driver sets up this connection. The
structure, defined in <linux/fs.h>, is a collection of function pointers. Each
open file  is associated with its own set of functions . The operations are
mostly in charge of implementing the system calls and are therefore, named open,
read, and so on.

  A file_operations structure or a pointer to one is called fops. Each field in
the structure must point to the function in the driver that implements a
specific operation, or be left NULL for unsupported operations. The whole
structure is mentioned below snippet.
static struct file_operations fops =
{
.owner          = THIS_MODULE,
.read           = rk_read,
.write          = rk_write,
.open           = rk_open,
.release        = rk_release,
};
************************************************************************/






#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>

dev_t dev = 0;
static struct class *dev_class;
static struct cdev rk_cdev;

static int __init rk_init(void);
static void __exit rk_exit(void);
static int rk_open(struct inode *inode, struct file *file);
static int rk_release(struct inode *inode, struct file *file);
static ssize_t rk_read(struct file *fp, char __user *buf, size_t len, loff_t *off);
static ssize_t rk_write(struct file *fp, const char *buf, size_t len, loff_t *off);

static struct file_operations fops=
{
  .owner = THIS_MODULE,
  .read  = rk_read,
  .write = rk_write,
  .open  = rk_open,
  .release = rk_release,
};


static int rk_open(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "In side %s\n",__func__);
  return 0;
}
static int rk_release(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "In side %s\n",__func__);
  return 0;
}
static ssize_t rk_read(struct file *fp, char __user *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "In side %s\n",__func__);
  return 0;
}
static ssize_t rk_write(struct file *fp, const char *buf, size_t len, loff_t *off)
{
  printk(KERN_INFO "In side %s\n",__func__);
  return 0;
}

int __init rk_init(void)
{

 if((alloc_chrdev_region(&dev, 0, 1, "KRKReddy")) < 0){
   printk(KERN_ERR "Cannot allocate major number\n" );
   return -1;
 }

   printk(KERN_INFO "Major num = %d Minor num = %d\n", MAJOR(dev), MINOR(dev));

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
}

module_init(rk_init);
module_exit(rk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRKReddy");
MODULE_DESCRIPTION("Device driver with basic file operations sudo code");
MODULE_VERSION("1.4");
