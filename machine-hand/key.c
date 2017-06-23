
#include	"includes.h"


void key_1(){
	if(control==0) control=1;
	LED_DATA=control;
	return;
}
void key_2(){
	if(control==0) control=2;
	LED_DATA=control;
	return;
}
void key_3(){
	if(control==0) control=3;
	LED_DATA=control;
	return;
}
void key_4(){
	if(control==0) control=4;
	LED_DATA=control;
	return;
}
void key_5(){
	if(control==0) control=5;
	LED_DATA=control;
	return;
}
void key_6(){
	if(control==0) control=6;
	LED_DATA=control;
	return;
}
void key_7(){

}
void key_8(){

}
void key_9(){

}
void key_0(){

}
void key_A(int *ctl){
	//left 27
	if(control>0)
	ctl[control-1]=(ctl[control-1]-1)%50;
}
void key_B(int *ctl){
	//right 27
	if(control>0)
	ctl[control-1]=(ctl[control-1]+1)%50;
}
void key_C(int *ctl){
	//reset
	ctl[control-1]=30;
}
void key_D(int *ctl){
	return;
}
void key_star(){
	control=0;
	LED_DATA=control;
}
void key_sharp(){
	control=-1;
	//LED_DATA=control;
}
