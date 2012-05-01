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

void process_event(struct js_event e) {

    printf("time: %lu, value: %d, type: 0x%X, number: 0x%X\n",
            e.time, e.value, e.type, e.number);
    unsigned char buttons_state = 0x0;

    if ((e.type & ~JS_EVENT_INIT) == JS_EVENT_BUTTON) {
        if (e.value)
            buttons_state |= (1 << e.number);
        else
            buttons_state &= ~(1 << e.number);
    }

    /*printf("Buttons_state: %d\n", buttons_state);*/
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
        usleep(500*1000);
    }

}
