//getch and more

#ifdef __cplusplus
  extern "C" {
#endif

void reset_terminal_mode(void);
void set_conio_terminal_mode(void);

int kbhit(void);
int getch(void);

#ifdef __cplusplus
}
#endif

//eof
