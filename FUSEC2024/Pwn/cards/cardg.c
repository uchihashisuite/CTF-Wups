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

int get_int(){
    char buf[16];
    read(0,buf,16);
    buf[15]='\0';
    int res=atoi(buf);
    return res;
}
long long current_gold=100;
void print_menu()
{
    puts("Hi i'm @nghiadt1098 and I'm rich as f*ck.");
    puts("If you correctly guess the total score of the cards in my hand, I will reward you alot of VND");
    puts("1. Play");
    puts("2. Buy flag");
    printf("Your money :%lld VND\n",current_gold);
    printf("Your choice: >");
}
// --------------------------------------------------- MAIN
void play()
{
    puts("How many cards you want me to suffle?");
    int cards =get_int();
    if (cards>10)
    {
        puts("Hell nope...");
        return;
    }
    int total=0;
    puts("How much gold you want to bet?");
    int bet=get_int();
    if (cards*bet>current_gold)
    {
        puts("Not enough $$$...");
        return;
    }
    printf("Careful!!! You will lost %d VND if lose\n",cards*bet);
    puts("Can you guess total score of the cards?");
    int guess_score =get_int();
    
    for (int i=0;i<cards;++i)
    {
        total+=rand()%13+1;//From A to K
    }
    if(total==guess_score)
    {
        current_gold+=cards*bet;
        printf("Correct!!! Here your money %d VND\n",cards*bet);
    } else
    {
        current_gold-=cards*bet;
        printf("Incorrect!!! I will take %d VND\n",cards*bet);
    }
    
}
void buy_flag()
{
    puts("This flag cost 1 billion VND");
    if (current_gold>=1000000000)
    {
        current_gold-=1000000000;
        system("cat flag");
        exit(0);
        
    } else
    {
    puts("Tien it ma doi hit fl** thom");
    exit(-1);
    }
    
}
void main(int argc, char* argv[]) {
	ignore_me_init_buffering();
	ignore_me_init_signal();
    srand(time(0));
    while(1)
    {
    	print_menu();
    	int choice =get_int();
    	switch (choice)
        {
            case 1:
                play();
                break;
            case 2:
                buy_flag();
                break;
            default:
                break;
        }
    }
  	
}

