/**********************************************************
Is it possible to pass the argument to the Device Driver?
-> module_param()         module_param(name, type, perm);
-> module_param_array()   module_param_array(name,type,num,perm);
-> module_param_cb()

Before discuss these macros we have to know about permissions of the variable.
There are several types of permissions:
    S_IWUSR
    S_IRUSR
    S_IXUSR
    S_IRGRP
    S_IWGRP
    S_IXGRP
In this S_I is common header.
R = read ,W =write ,X= Execute.
USR =user ,GRP =Group
Using OR ‘|’ (or operation) we can set multiple permissions at a time.

module_param(RK_var, int, S_IRUSR|S_IWUSR);
This will create the sysfs entry.
   (/sys/module/hello_world_module/parameters/RK_var)
You can change the value of RK_var from command line by
echo 1 > /sys/module/hello_world_module/parameters/RK_var

If you want to get notification whenever value got change. we need
to register our handler function to its file operation structure.
struct kernel_param_ops {
        int (*set)(const char *val, const struct kernel_param *kp);
        int (*get)(char *buffer, const struct kernel_param *kp);
        void (*free)(void *arg);
};

***********************************************************/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

int RK_var, arr_RK[4];
char *nameRK;
int cb_RK = 0;

module_param(RK_var, int, S_IRUSR|S_IWUSR);    //integer value
module_param(nameRK, charp, S_IRUSR|S_IWUSR);  //string
module_param_array(arr_RK, int, NULL, S_IRUSR|S_IWUSR);

int notify_param(const char *val, const struct kernel_param *kp)
{
   int res = param_set_int(val, kp);

   if(res == 0){
              printk(KERN_INFO "Call back function called...\n");
              printk(KERN_INFO "Latest value of cb_RK = %d\n", cb_RK);
	      return 0;
   }
   return -1;
}

const struct kernel_param_ops my_param_ops =
{
     .set = &notify_param,
     .get = &param_get_int,
};

module_param_cb(cb_RK, &my_param_ops, &cb_RK, S_IRUGO|S_IWUSR);

static int __init rk_init(void)
{
   int i;
      printk(KERN_INFO "RK_var = %d \n", RK_var);
      printk(KERN_INFO "cb_RK = %d \n", cb_RK);
      printk(KERN_INFO "nameRK = %s \n", nameRK);
       for(i = 0; i < (sizeof arr_RK/sizeof(int)); i++){
           printk(KERN_INFO " arr_RK[%d] = %d \n", i, arr_RK[i]);
       }
      printk(KERN_INFO "Kernel Module Inserted Successfully..\n");
    return 0;
}

void __exit rk_exit(void)
{
      printk(KERN_INFO "Kernel Module Removed Successfully..\n");
}

module_init(rk_init);
module_exit(rk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRKReddy");
MODULE_DESCRIPTION("Passing arguments to Driver");
MODULE_VERSION("1.2");
