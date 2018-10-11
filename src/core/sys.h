// System
// (c) 2018 Jani Nykänen

#ifndef __SYS__
#define __SYS__

// Initialize system
void sys_init();

// Start application
void sys_start_prog(void (*cb) (void));

#endif // __SYS__
