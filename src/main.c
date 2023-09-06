static const int VIDEO_MAX_COLS = 80;
static const int VIDEO_MAX_ROWS = 25;

unsigned short* video_memory = (unsigned short*)0xb8000;

void clear_screen() {
  for(int i = 0; i <= VIDEO_MAX_COLS*VIDEO_MAX_ROWS; ++i){
    video_memory[i] = (unsigned short)0x0000;
  }
}

void main() {
  clear_screen();
  while(1){}
}
