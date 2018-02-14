#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JJ Rabago Jr");
MODULE_DESCRIPTION("hw3");
MODULE_VERSION("1.0");

static int inp_pid=0;
module_param(inp_pid, int, 0);

static struct task_struct *p;
static struct task_struct *q;
static struct list_head *head;

static int __init start(void){

	for_each_process(p){
		if(inp_pid < p->pid){
			printk("PROCESS NAME\tPID\tSTATE\tPRIORITY\tS_PRIORITY\tN_PRIORITY\n");
			printk("PARENT\n");
			printk(" %-11s\t%-4d\t%-4ld\t%-8d\t%-8d\t%-8d\n"
			,p->comm,p->pid,p->state,p->prio,p->static_prio,p->normal_prio); 
			
			printk("CHILDREN\n");
			list_for_each( head , &p->children){
				q = list_entry( head, struct task_struct, sibling );
				printk(" %-11s\t%-4d\t%-4ld\t%-8d\t%-8d\t%-8d\n"
				,q->comm,q->pid,q->state,q->prio,q->static_prio,q->normal_prio); 
			}
			printk("\n");
		}
	}

	return 0;
}




static void __exit end(void){
	printk("The end\n");
}

module_init(start);
module_exit(end);
