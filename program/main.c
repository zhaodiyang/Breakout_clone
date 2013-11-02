#include <reg52.h>
#include "game.h"

//timer1 init value
#define TH1value 0x63
#define TL1value 0xC0
//refesh screen count
#define screen_count 3

extern bit bar_direction;


//count for timer
unsigned char count=0;

//Use timer1 to count time
//timer1 initial
//timer -> 0.01s
void init_timer1(){
	TMOD=0x10;
	TH1=TH1value;
	TL1=TL1value;
	TR1=1;
}

//External int init
void init_external(){
	IT0=1;
	IT1=1;
}

//int init
void init_int(){
	EA=1;
	ET1=1;
	EX0=1;
	EX1=1;
}

void hardware_init(){
	init_timer1();
	init_external();
	init_int();
}

void main(){
	//init timer1 and two external interrupts
	hardware_init();
	//init screen
	game_init();
	//begin game
	while(1){
		//every 0.03s refresh screen
		if(count>=screen_count){
			//refresh screen
			refresh_screen();
			//clear count
			count=0;
		}
	}
}

void int_timer1() interrupt 3{
	count++;
	TH1=TH1value;
	TL1=TL1value;
}

void int_external0() interrupt 0{
	bar_direction=0;
}

void int_external1() interrupt 2{
	bar_direction=1;
}