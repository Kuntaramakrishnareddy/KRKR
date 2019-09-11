/*****************************************************************************
-> Licence
-> Author
-> Module Description
-> Module Version
-----------------------------------------------------------------------------

-> Licence: GPL, or the GNU General public Licence, is an open source
 licence meant for software.
-> modinfo can show license info for users wanting to vet their setup
 is free

 -> We can give the License for our driver (module) like below. For
  this you need to include the Linux/module.h header file.
ex1:  MODULE_LICENCE("GPL");
ex2:  MODULE_LICENCE("GPL v2");

-> Using MODULE_AUTHOR Macro we can mention that who is wrote this
driver or module. So modinfo can show author name for users wanting
to know. We can give the Author name for our driver (module) like below.
ex1: MODULE_AUTHOR("KRKReddy");

-> MODULE_DESCRIPTION for description of driver
-> MODULE_VERSION for specifing driver version

----------------------Init Function------------------------
->This is the function which will executes first when the driver
is loaded into the kernel. For example when we load the driver
using insmod, this function will execute.
----------------------Exit Function------------------------
->This is the function which will executes last when the driver
is unloaded from the kernel. For example when we unload the driver
using rmmod, this function will execute.

---------------------printk-------------------------------
One of the differences is that printk lets you classify messages
according to their severity by associating different loglevels,
or priorities, with the messages. You usually indicate the loglevel
with a macro

KERN_EMERG: Used for emergency messages, usually those that precede a crash.
KERN_ALERT: Situation requiring immediate action.
KERN_CRIT: Critical conditions, often related to serious hardware or software
 failures.
KERN_ERR: Used to report error conditions; device drivers often use KERN_ERR
 to report hardware difficulties.
KERN_WARNING: Warnings about problematic situations that do not, in themselves,
 create serious problems with the system.
KERN_NOTICE: Situations that are normal, but still worthy of note. A number of
 security-related conditions are reported at this level.
KERN_INFO: Informational messages. Many drivers print information about the
 hardware they find at startup time at this level.
KERN_DEBUG: Used for debugging messages.
******************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init rk_init(void)
{
	printk(KERN_INFO "In side %s\n", __func__);
	return 0;
}

void __exit rk_exit(void)
{
	printk(KERN_INFO "In side %s\n", __func__);
}

module_init(rk_init);
module_exit(rk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KRKReddy");
MODULE_DESCRIPTION("Simple Test Driver");
MODULE_VERSION("1.0");

