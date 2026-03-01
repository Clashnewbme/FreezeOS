#ifndef FREEZE_OS_TIMER_H
#define FREEZE_OS_TIMER_H

void timer_init();
void update_display_time();
void read_rtc(uint32_t* hours, uint32_t* minutes, uint32_t* seconds);

#endif