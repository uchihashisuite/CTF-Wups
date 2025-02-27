#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
// --------------------------------------------------- SETUP

void ignore_me_init_buffering() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

void kill_on_timeout(int sig) {
  if (sig == SIGALRM) {
  	printf("[!] Anti DoS Signal. Patch me out for testing.");
    _exit(0);
  }
}

void ignore_me_init_signal() {
	signal(SIGALRM, kill_on_timeout);
	alarm(60);
}

// --------------------------------------------------- MENU

unsigned int get_uint()
{
    char buf[16];
    read(0,buf,16);
    buf[15]='\0';
    unsigned int res=atoi(buf);
    return res;
}
unsigned int block_number=0;
unsigned int block_size=0;
unsigned int code_size=0;

typedef  struct _BrainFMachine
{
    unsigned char * code;
    unsigned char * brain_pointer;
    unsigned char * data_pointer;
    unsigned int block_number;
    unsigned int block_size;
    unsigned int code_size;
    
} BrainFMachine;

void brain_run(BrainFMachine *machine)
{
    unsigned long long machine_size=machine->block_size;
    machine_size*=machine->block_number;
    unsigned long long upper_bound_data=(unsigned long long )machine->brain_pointer+machine_size;
    unsigned long long lower_bound_data=(unsigned long long )machine->brain_pointer;
    unsigned long long upper_bound_code=(unsigned long long )machine->code+machine->code_size;
    unsigned long long lower_bound_code=(unsigned long long )machine->code;
    while(1)
    {
        switch (*machine->code)
        {
            case '+':
                *machine->data_pointer=*machine->data_pointer+1;
                //printf("+ data %p\n",machine->data_pointer);
                break;
            case '-':
                *machine->data_pointer=*machine->data_pointer-1;
                //printf("- data %p\n",machine->data_pointer);
                break;
            case '>':
                //printf("%p %p %p\n",lower_bound_data,(unsigned long long )machine->data_pointer+machine->block_size,upper_bound_data);
                if ((unsigned long long )machine->data_pointer+machine->block_size>=lower_bound_data && (unsigned long long )machine->data_pointer+machine->block_size<upper_bound_data)
                {
                    machine->data_pointer+=machine->block_size;
                    //printf("> data %p\n",machine->data_pointer);
                }
                else
                {
                
                    puts("Access violation");
                    exit(-1);
                }
                break;
            case '<':
                //printf("%x %x %x\n",lower_bound_data,(unsigned long long )machine->data_pointer-machine->block_size,upper_bound_data);
                if ((unsigned long long )machine->data_pointer-machine->block_size>=lower_bound_data && (unsigned long long )machine->data_pointer-machine->block_size<upper_bound_data)
                {
                    machine->data_pointer-=machine->block_size;
                    //printf("< data %p\n",machine->data_pointer);
                }
                else
                {
                
                    puts("Access violation");
                    exit(-1);
                }
                break;
            case '.':
                write(1,machine->data_pointer,machine->block_size);
                //printf(". data %p\n",machine->data_pointer);
                break;
            case ',':
                read(0,machine->data_pointer,machine->block_size);
                //printf(", data %p\n",machine->data_pointer);
                break;
            case '[':
                //printf("[ code %p\n",machine->code);
                if(*machine->data_pointer==0)
                {
                    
                    while(*machine->code!=']')
                    {
                        //printf("[ code %c\n",*machine->code);
                        machine->code++;
                        if ((unsigned long long )machine->code>lower_bound_code && (unsigned long long )machine->code<upper_bound_code)
                        {
                            continue;
                        }
                        else
                        {
                            puts("Runtime error");
                            exit(-1);
                        }
                    }
                }
                //printf("[ code %c\n",*machine->code);    
                break;    
            case ']':
                //printf("] code %p\n",machine->code);
                if(*machine->data_pointer!=0)
                {
                    
                    while(*machine->code!='[')
                    {
                    //printf("] code %c\n",*machine->code);
                    
                        machine->code--;
                        if ((unsigned long long )machine->code>lower_bound_code && (unsigned long long )machine->code<upper_bound_code)
                        {
                            continue;
                        }
                        else
                        {
                            puts("Runtime error");
                            exit(-1);
                        }
                    }
                }
                break;    
            default:
                puts("End execution");
                exit(-1);
        }
            machine->code++;    
            
    }
    
}
void main(int argc, char* argv[]) 
{
	ignore_me_init_buffering();
	ignore_me_init_signal();
	
    puts("@nghiadt1098: Ever heard Brainf*ck?");
    
    // Input machine paramaters
    puts("Input RAM ammount(blocks)?");
    block_number=get_uint();
    puts("Input block size(bytes)?");
    block_size=get_uint();
    puts("Input code size(bytes)?");
    code_size=get_uint();
    
    // Allocate memory
    unsigned int allocated_block=block_number*block_size;
    unsigned char*brain_pointer = (unsigned char*) malloc(allocated_block);
    
    if(brain_pointer==0)
    {
        printf("Not enough memory");
        exit(0);
    }
    memset(brain_pointer,0,allocated_block);
    unsigned char*code =(unsigned char*) malloc(code_size);
    if(code==0)
    {
        printf("Not enough memory");
        exit(0);
    }
    printf("Input brainf*** code %d bytes?\n",code_size);
    read(0,code,code_size);
    
    // Init and run 
    BrainFMachine * machine=(BrainFMachine*) malloc(sizeof(BrainFMachine));
    if(machine==0)
    {
        printf("Not enough memory");
        exit(0);
    }
    printf("BrainF**k block_number %d\n",block_number);
    printf("BrainF**k block_size %d\n",block_size);
    printf("BrainF**k code_size %d\n",code_size);
    machine->code=code;
    machine->brain_pointer=brain_pointer;
    machine->data_pointer=brain_pointer;
    machine->block_number=block_number;
    machine->block_size=block_size;
    machine->code_size=code_size;
    // Run
    brain_run(machine);
        
   
  	
}

