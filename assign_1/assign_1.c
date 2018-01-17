#include<linux/init.h>
#include<linux/module.h>

int mod_init(void)
{
	printk(KERN_ALERT "Hello World\n");
	return 0;
}
void mod_exit(void)
{
	printk(KERN_ALERT "Leaving World\n");
}

module_init(mod_init);
module_exit(mod_exit);

