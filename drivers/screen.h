int cursorX = 0;
int cursorY = 0;

char *xyToVidmem(int x, int y) {
  char *vidmem = (char *)VIDEO_ADDRESS;
  vidmem += x * 2;
  vidmem += y * 2 * MAX_COLS;
  return vidmem;
}

void newl() {
  cursorY++;
  cursorX = 0;
  //// scrolling
  if (cursorY == MAX_ROWS) {
    char *vidmem = xyToVidmem(0, 1);
    while (vidmem <= MAX_LEN) {
      *(vidmem - (MAX_COLS * 2)) = *vidmem;
      vidmem++;
    }
    //// clear final line
    cursorY--;
  }
}

int print(char string[]) {
  int len = strlen(string);

  char *vidmem = xyToVidmem(cursorX, cursorY);


  while (*string != 0) {
    cursorX++;
    if (cursorX == MAX_ROWS) {
      newl();
    }

    *vidmem++ = *string++;
    *vidmem++ = 0x07;
  }

  return 0;
}

int printf(char string[]) {
  int len = strlen(string);

  char *vidmem = xyToVidmem(cursorX, cursorY);


  while (*string != 0) {
    cursorX++;
    if (cursorX == MAX_ROWS) {
      newl();
    }

    *vidmem++ = *string++;
    *vidmem++ = 0x07;
  }
  newl();

  return 0;
}



int kprint(char string[], int x, int y) {
  // don't write outside of video buffer
  if (x >= MAX_COLS || y >= MAX_ROWS || x < 0 || y < 0) return -1;

  char *vidmem = (char *)VIDEO_ADDRESS;
  vidmem += x * 2;
  vidmem += y * 2 * MAX_COLS;


  while (*string != 0) {
    if (vidmem >= MAX_LEN) return -2;
    *vidmem++ = *string++;
    *vidmem++ = 0x07;
  }

  return 0;
}

void clear_screen(char character, uint8 color) {
  char *vidmem = (char *)VIDEO_ADDRESS;
  while (vidmem <= MAX_LEN) {
    *vidmem++ = character;
    *vidmem++ = color;
  }
}

char* itoa(int val) {
  static char buffer[8];  // Static buffer

  // if (val > 255) return '\0';

  char hexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  buffer[0] = '0';
  buffer[1] = 'x';
  buffer[2] = hexChars[(val & 0xF0000) >> 16];
  buffer[3] = hexChars[(val & 0xF000) >> 12];
  buffer[4] = hexChars[(val & 0xF00) >> 8];
  buffer[5] = hexChars[(val & 0xF0) >> 4];
  buffer[6] = hexChars[val & 0x0F];
  buffer[7] = '\0';

  return buffer;
}