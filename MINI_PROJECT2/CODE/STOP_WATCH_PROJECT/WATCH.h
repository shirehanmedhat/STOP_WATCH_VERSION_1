/*
 ============================================================================
 Name        : STOP_WATCH.h
 Author      : Shirehan Medhat Abdelsalam Ali
 Description : Header File Of Mini Project 2
 ============================================================================
 */
#ifndef WATCH_H_
#define WATCH_H_

//MACROS
#define NULL ((void*)0)
#define SEC1Counter  0
#define SEC2Counter  1
#define MIN1counter  2
#define MIN2counter  3
#define HOUR1counter 4
#define HOUR2counter 5
#define TEST_1                     215998     // 59 Hour 59 Min 58 Sec _CRITICAL_POINT
#define TEST_2                     359998    // 99 Hour 59 Min 58 Sec  _OVER_FLOW_OCCURS
#define TEST_NORMAL_FROM_ZERO      0         // NORMAL CASE
//**********************************************************************//
//FUNCTIONS
void TIMER0_INIT_DELAY_3mseconds(void);
void TIMER1_INIT (void);
void EXI0_INIT(void);
void EXI1_INIT(void);
void EXI2_INIT(void);
void CONVERT_SECONDS_TO_TIME_FORM (char *PTR_TO_DATA_ARRAY);
void DISPLAY_TIME (char *PTR_TO_ARRAY);
void L7447N_INIT (void);
void SEGMENT_CONTROL_INIT (void);
void PUSH_BUTTONS_INIT (void);


#endif /* WATCH_H_ */
