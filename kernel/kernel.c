#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define MAX_LEN 0xb8fa1

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;

#include "../libc/libc.h"
#include "../drivers/screen.h"
#include "../drivers/io.h"
#include "../drivers/keyboard.h"


int main() {
  enableKeyboard();
  char string[] = "Hello, World!";
  char two[] = "Welcome to NIGHTMARE OS!!!";
  char test[] = "1234567890123456789012345678901234567890123456789012345678901234";
  uint8 color = 0x00;
  clear_screen(' ', color);
  kprint(test, 0, 0);
  
  while (1) {
    handleKeyboardInput();
  }
  return 0;
}