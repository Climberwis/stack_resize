// Zwiększa stack do 64 MB na linuxie

#include <sys/resource.h>
int main(int argc, char** argv) 
{
	const rlim_t stack_size_big   = 64 * 1024 * 1024;   // reccomend stack size = 64 MB
		const rlim_t stack_size_small = 8 * 1024 * 1024;   // min stack size = 8 MB
		struct rlimit rl;
		int result;
		result = getrlimit(RLIMIT_STACK, &rl);
		if (result == 0)
		{
		    if (rl.rlim_cur < stack_size_big)
		    {
				cout << "Trying to set new stack size (64 MB)" << endl;
				cout << "Current stack size: " << (rl.rlim_cur/1048576) << endl;
		        rl.rlim_cur = stack_size_big;
		        result = setrlimit(RLIMIT_STACK, &rl);
		        if (result != 0)
		        {
					cout << endl << "WARNING!" << endl;
					cout << "Cannot set stack size 64 MB, tryin to set 8MB" << endl;
					rl.rlim_cur = stack_size_small;
		        	result = setrlimit(RLIMIT_STACK, &rl);
		            if (result != 0)
					{
					cout << endl << "WARNING!" << endl;
					cout << "Cannot set stack new size!" << endl;
					cout << "Programm may cause Segmentation Fault due to Stack Overflow when big samples are analysed" << endl;
					}
		        }
		    }
		}	
}
