#include <lpc214x.h>
#define bit(x) (1 << x)
#define delay for(i = 0; i < 70000; i++);
#define RAIN (IO1PIN & (1 << 24))

unsigned int i;

void lcd_init();
void dat(unsigned char);
void cmd(unsigned char);
void string(unsigned char *);

void main() {
    IO0DIR = 0xFFF;  // P0.0 - P0.11 as output
    IO1DIR = 0x0;    // P1 as input (rain sensor)
    lcd_init();
    cmd(0x80);
    string("Alert");
    delay; delay;
    
    while(1) {
        if(RAIN == 0) {  // Active low when rain detected
            string("!Rain Detected!");
            delay; delay;
            cmd(0x01);  // Clear display
        }
    }
}

void lcd_init() {
    cmd(0x38);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x01);
    cmd(0x80);
}

void cmd(unsigned char a) {
    IO0PIN &= 0x00;
    IO0PIN |= (a << 0);
    IO0CLR |= bit(8);
    IO0CLR |= bit(9);
    IO0SET |= bit(10);
    delay;
    IO0CLR |= bit(10);
}

void dat(unsigned char b) {
    IO0PIN &= 0x00;
    IO0PIN |= (b << 0);
    IO0SET |= bit(8);
    IO0CLR |= bit(9);
    IO0SET |= bit(10);
    delay;
    IO0CLR |= bit(10);
}

void string(unsigned char *p) {
    while(*p != '\0') {
        dat(*p++);
    }
}
