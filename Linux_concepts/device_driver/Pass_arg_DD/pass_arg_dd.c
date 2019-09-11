#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

#define ARR_SIZE 5

int rk_val, rk_arr[ARR_SIZE] = {0};
char *rk_str;
int cb_rkval; //callback

module_param(rk_val, int, 0660);
module_param(rk_str, charp, 0660);
module_param_array(rk_arr, int, NULL, 0660);


int notify_param(const char *val, const struct kernel_param *kparam)
{
  int i;
  int res = param_set_int(val, kparam); // Use helper for write variable
  if(res == 0){
	  printk(KERN_INFO " Callback function called...\n");
	  printk(KERN_INFO " New value of cb_rkval is %d\n", cb_rkval);
	printk(KERN_INFO "rk_val = %d \n", rk_val);
	printk(KERN_INFO "cb_rkval = %d \n", cb_rkval);
	printk(KERN_INFO "rk_str = %s \n", rk_str);
	for(i = 0; i < ARR_SIZE; i++){
	     printk(KERN_INFO "rk_arr[%d] = %d\n", i, rk_arr[i]);
	}
          return 0;
  }
  return -1;
}

int param_get_int(char *buf, const struct kernel_param *kparam)
{
	  printk(KERN_INFO " Read Callback function called...\n");
	  *buf = cb_rkval;
	  return 0;
}
/**********************************************************************
struct kernel_param_ops {
        int (*set)(const char *val, const struct kernel_param *kp);
        int (*get)(char *buffer, const struct kernel_param *kp);
        void (*free)(void *arg);
};
**********************************************************************/
const struct kernel_param_ops rk_param_ops = {
     .set = notify_param,
     .get = param_get_int,
};

module_param_cb(cb_rkval, &rk_param_ops, &cb_rkval, S_IRUGO|S_IWUSR);

static int __init rk_init(void){
	int i;

	printk(KERN_INFO "rk_val = %d \n", rk_val);
	printk(KERN_INFO "cb_rkval = %d \n", cb_rkval);
	printk(KERN_INFO "rk_str = %s \n", rk_str);
	for(i = 0; i < ARR_SIZE; i++){
	     printk(KERN_INFO "rk_arr[%d] = %d\n", i, rk_arr[i]);
	}
	printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
	return 0;
}

void __exit rk_exit(void){
	printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}

module_init(rk_init);
module_exit(rk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRKReddy");
MODULE_DESCRIPTION("A example driver to notify change of value");
MODULE_VERSION("1.0");
/*** STEP to understand ***
make
sudo insmod pass_arg_dd.ko rk_val=49 rk_str="RamakrishnaReddy" rk_arr=11,22,33,44,55
sudo chmod 007 /sys/module/pass_arg_dd/parameters/cb_rkval
sudo chmod 007 /sys/module/pass_arg_dd/parameters/rk_val
sudo echo 1899 >> /sys/module/pass_arg_dd/parameters/rk_val
sudo echo 1899 >> /sys/module/pass_arg_dd/parameters/cb_rk_val
********************/
