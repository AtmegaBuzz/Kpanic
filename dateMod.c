#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/ctype.h>
#include <linux/time.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swapnil Shinde");
MODULE_DESCRIPTION("This is a kernel module developed for LFX Task It takes date as input from user and tells if the date is correct or not");

static char* today_date;

module_param(today_date,charp,S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(today_date,"today's date in dd/mm/yy format");


static int parse_date(const char* inputDate, struct tm *storeDate){
    return sscanf(inputDate, "%d/%d/%ld", &storeDate->tm_mday, &storeDate->tm_mon, &storeDate->tm_year);
}   



static int __init date_module_init(void){

    struct tm input_date_tm = {0};
    struct timespec64 curr_time;
    struct tm curr_date_tm;
    int res;

    res = parse_date(today_date,&input_date_tm);
    
    ktime_get_real_ts64(&curr_time);
    time64_to_tm(curr_time.tv_sec,0,&curr_date_tm);

    // adjust date
    curr_date_tm.tm_mon += 1;
    curr_date_tm.tm_year += 1900;

    if (input_date_tm.tm_mday == curr_date_tm.tm_mday &&
        input_date_tm.tm_mon == curr_date_tm.tm_mon &&
        input_date_tm.tm_year == curr_date_tm.tm_year){
        printk(
            KERN_INFO "Correct!, you entered correct date i.e %d/%d/%ld \n",
            input_date_tm.tm_mday,
            input_date_tm.tm_mon,
            input_date_tm.tm_year
        );
    }

    else {
        printk(
            KERN_INFO "Wrong! you entered wrong date %d/%d/%ld today is %d/%d/%ld \n",
            input_date_tm.tm_mday,
            input_date_tm.tm_mon,
            input_date_tm.tm_year,

            curr_date_tm.tm_mday,
            curr_date_tm.tm_mon,
            curr_date_tm.tm_year

        );
    }

    return 0;
}



static void __exit date_module_exit(void){
    printk(KERN_INFO "dateMod module removed");
}



module_init(date_module_init);
module_exit(date_module_exit);
