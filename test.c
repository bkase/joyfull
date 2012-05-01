/* Copyright (c) 2012 Brandon Kase 
 * MIT License
 *
 * Testing from tutorial http://www.mjmwired.net/kernel/Documentation/input/joystick-api.txt
 * With a Logitech Attack 3
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include <errno.h>
#include <stropts.h>

#define IS_BUTTON(type) ((type) & 0x1)
#define IS_INIT(type) (((type) >> 0x7) & 0x1)

//The 11 Buttons
#define TRIGGER 0x0
#define DOWN_TOP 0x1
#define UP_TOP 0x2
#define LEFT_TOP 0x3
#define RIGHT_TOP 0x4
#define BOT_LEFTUP 0x5
#define BOT_LEFTDOWN 0x6
#define BOT_CENTERLEFT 0x7
#define BOT_CENTERRIGHT 0x8
#define BOT_RIGHTDOWN 0x9
#define BOT_RIGHTUP 0xA

void process_event(struct js_event e) {

    /*printf("time: %lu, value: %d, type: 0x%X, number: 0x%X\n",*/
            /*e.time, e.value, e.type, e.number);*/

    if (IS_BUTTON(e.type) & !IS_INIT(e.type)) {
        printf("Pressed ");
        switch(e.number) {
            case TRIGGER: printf(" TRIGGER %d", e.value); break;
            case DOWN_TOP: printf(" DOWN_TOP %d", e.value); break;
            case UP_TOP: printf(" UP_TOP %d", e.value); break;
            case LEFT_TOP: printf(" LEFT_TOP %d", e.value); break;
            case RIGHT_TOP: printf(" RIGHT_TOP %d", e.value); break;
            case BOT_LEFTUP: printf(" BOT_LEFTUP %d", e.value); break;
            case BOT_LEFTDOWN: printf(" BOT_LEFTDOWN %d", e.value); break;
            case BOT_CENTERLEFT: printf(" BOT_CENTERLEFT %d", e.value); break;
            case BOT_CENTERRIGHT: printf(" BOT_CENTERRIGHT %d", e.value); break;
            case BOT_RIGHTDOWN: printf(" BOT_RIGHTDOWN %d", e.value); break;
            case BOT_RIGHTUP: printf(" BOT_RIGHTUP %d", e.value); break;
            default: printf("Error!"); break;
        }
        printf("\n");
    }
    else if (!IS_BUTTON(e.type) & !IS_INIT(e.type)) {
    
        printf("Analog stick: ");
        switch(e.number) {
            case 0: printf(" X: %d", e.value); break;
            case 1: printf(" Y: %d", e.value); break;
            case 2: printf(" BALL: %d", e.value); break;
            default: printf("Error!"); break;
        }
        printf("\n");
    }

}

int main() {

    struct js_event e;
    unsigned char num_buttons;

    int fd = open ("/dev/input/js0", O_NONBLOCK);
    /*int fd = open ("/dev/js0", O_RDONLY);*/


    /* blocking read */
    /*while (1) {
      read (fd, &e, sizeof(struct js_event));
      printf("time: %lu, value: %d, type: 0x%X, number: 0x%X\n", 
      e.time, e.value, e.type, e.number);
      usleep(500*1000);
      }*/

    /* There are 11 buttons on the Attack3 Logitech controller */
    /* ioctl(fd, JSIOCGBUTTONS, &num_buttons);
       printf("num_buttons: %d\n", num_buttons);
       exit(0);*/

    /* Non-blocking read */

    while (1) {
        while (read (fd, &e, sizeof(struct js_event)) > 0) {
            process_event(e);
        }
        /*EAGAIN is returned when the queue is empty*/
        if (errno != EAGAIN) {
            printf("%d\n", errno);
        }
        usleep(10*1000);
    }

}
