#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JJ Rabago Jr");
MODULE_DESCRIPTION("hw3");
MODULE_VERSION("1.0");

static int inp_pid=0;

static struct task_struct *p;
static struct list_head *head;

static int __init start(void){

	printk("PROCESS NAME\tPID\tSTATE\tPRIORITY\tS_PRIORITY\tN_PRIORITY\n");
	for_each_process(p){
		printk(" %-11s\t%-4d\t%-4ld\t%-8d\t%-8d\t%-8d\n"
		,p->comm,p->pid,p->state,p->prio,p->static_prio,p->normal_prio); 
		
		printk("CHILDREN\n");
		
		list_for_each( head , &p->children ){
			 p = list_entry( head, struct task_struct, children );
			printk(" %-11s\t%-4d\t%-4ld\t%-8d\t%-8d\t%-8d\n"
		,p->comm,p->pid,p->state,p->prio,p->static_prio,p->normal_prio); 
			
		}
	}

	return 0;
}




static void __exit end(void){
	printk("The end\n");
}

module_init(start);
module_exit(end);
