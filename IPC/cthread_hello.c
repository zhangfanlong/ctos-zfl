/*this is an exaple about chtread

waring: pass -lthread to gcc
*/

#include <cthreads.h>
#include <stdio.h>
//cthread_init();
//cthread_t function_thread;
//cthread_t cthread_fork (any_t (*function)(any_t), any_t arg);

any_t print_string(any_t string)
{
	printf((char *)(string));
	return NULL;
}
void main()
{
	//for declare/assigining/launching the cthread
	cthread_t print_thread;
	print_thread=cthread_fork(print_string,"Hello World\n");
	cthread_join(print_thread);//cthread_join would have wait until the return( something )
	//cthread_detach(print_thread);//not wait
	return 0;
}