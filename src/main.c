static const int VIDEO_MAX_COLS = 80;
static const int VIDEO_MAX_ROWS = 25;

unsigned short* video_memory = (unsigned short*)0xb8000;

int video_cur_pos_cols = 1;
int video_cur_pos_rows = 1;

void clear_screen(void);
void main(void);

void putchar(const char c) {
  if(c == '\n') {
    ++video_cur_pos_rows;
    video_cur_pos_cols = 1;
  }

  unsigned short tmp = (c | 7 << 8);
  video_memory[(video_cur_pos_rows - 1) * VIDEO_MAX_COLS + (video_cur_pos_cols - 1)] = tmp;
  ++video_cur_pos_cols;
}

void clear_screen(void) {
  for(int i = 0; i <= VIDEO_MAX_COLS*VIDEO_MAX_ROWS; ++i) {
    video_memory[i] = (unsigned short)0x0000;
  }
}

void main(void) {
  clear_screen();

  putchar('H');
  putchar('e');
  putchar('l');
  putchar('l');
  putchar('o');
  putchar(',');
  putchar(' ');
  putchar('w');
  putchar('o');
  putchar('r');
  putchar('l');
  putchar('d');
  putchar('!');

  while(1){}
}
