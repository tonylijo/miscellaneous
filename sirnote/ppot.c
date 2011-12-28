#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/sched.h>

static char *name = "foo";
static int major;

static int foo(read
