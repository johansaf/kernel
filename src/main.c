static const int VIDEO_MAX_COLS = 80;
static const int VIDEO_MAX_ROWS = 25;

unsigned short* video_memory = (unsigned short*)0xb8000;

int video_cur_pos_cols = 1;
int video_cur_pos_rows = 1;

void putchar(const char);
void printf(const char*, ...);
void clear_screen(void);
void main(void);

void putchar(const char c) {
  if(c == '\n') {
    ++video_cur_pos_rows;
    video_cur_pos_cols = 1;
  } else {
    unsigned short tmp = (c | 7 << 8);
    video_memory[(video_cur_pos_rows - 1) * VIDEO_MAX_COLS + (video_cur_pos_cols - 1)] = tmp;
    ++video_cur_pos_cols;
  }
}

void printf(const char* fmt, ...) {
  int *argp = (int*)&fmt;
  ++argp;

  while(*fmt) {
    switch(*fmt) {
      case '%':
        ++fmt;
        switch(*fmt) {
          case '%':
            putchar('%');
            break;
          case 's':
            putchar(*argp);
            ++argp;
            break;
          default: putchar(*fmt); break;
        }
      break;
      default: putchar(*fmt); break;
    }
    ++fmt;
  }
}

void clear_screen(void) {
  for(int i = 0; i <= VIDEO_MAX_COLS*VIDEO_MAX_ROWS; ++i) {
    video_memory[i] = (unsigned short)0x0000;
  }
}

void __cdecl main(void) {
  clear_screen();

  printf("Hello, world!\n");
  printf("Line two :)\n");
  printf("Line three! :D\n");
  printf("Test %% %s %c %d %lx %llu %hd %hhd\n", "abc", 'z', 1, 2ul, 3ull, (short)4, (char)5);

  while(1){}
}
