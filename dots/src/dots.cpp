//dot-game

#include "Cdots.h"
#include "stdio.h"
#include "types.h"
#include "stdlib.h"
#include <unistd.h>
#include <iostream>
//#include <string>
#include <termios.h>
#include "getchar_unblock.h"

const int c_maxDots = 20;
const int c_maxDotpos = 30;
//int m_dotcnt =0;
char m_dotstripe[c_maxDotpos+2] = {};

//char m_dottype[6] = { (char*)".ox*OX" };
const char* m_dottype = { (char*)".ox*OX" };


typedef struct _SDotbox{
  CDots* dot;
  _SDotbox* next;
  _SDotbox* prev;
}SDotbox, *PDotbox;

static PDotbox m_dots = NULL;

void update(void){
  PDotbox pd = m_dots;
  while(pd){
    pd->dot->doProc();
    pd = pd->next;
  }
}

void showDots(void){
  for(U32 i=0; i<=c_maxDotpos; i++){
    m_dotstripe[i] = ' ';
  }
  //m_dotstripe[28]=m_dottype[3];
  PDotbox pd = m_dots;
  while(pd){
    m_dotstripe[pd->dot->getPos()] = m_dottype[pd->dot->getColor()];
    //printf(" id:%i, p:%i, c:%i\r\n", pd->dot->getId(), pd->dot->getPos(), pd->dot->getColor());
    pd=pd->next;
  }  
  printf(">%s<\r", m_dotstripe);

  //cout << m_dotstripe << endl;
  //cout << m_dotstripe << "\n";
}

PDotbox getLast(void){
  PDotbox db = m_dots;
  if(!db){ 
    return NULL;
  }
  while(db->next){
    db=db->next;
  }
  return db;
}

void addDot(ws2812Color color, float speed){
  PDotbox db = (PDotbox)malloc(sizeof(SDotbox));
  db->dot = new CDots( color, c_maxDotpos,  speed);
  db->next = NULL;
  db->prev = getLast();
  if(db->prev){
    db->prev->next = db;
  }else{  //1st<
    m_dots = db;
  }
}

PDotbox getDotBoxByPos(U32 pos){
  PDotbox db = m_dots;
  while(db){
    if(db->dot->getPos() == pos){
      return db;
    }
    db=db->next;
  }
  return NULL;
}
void delDotByPos(U32 pos){
  PDotbox db = getDotBoxByPos(pos);
  if(db) delete(db);
}

int main(int argc, char** argv){
  float sleeptime = 11e3;
  printf("hi 0.6.\n");
  addDot(1, 10e-3);
  addDot(2, 20e-3);
  addDot(3, 30e-3);
  addDot(4, 40e-3);
  addDot(5, 50e-3);

  set_conio_terminal_mode();
  
  while(1){
    if (kbhit()){
      int ch = getch();
      switch(ch){
        case '-': sleeptime -= 1e3; printf("t:%f\n",sleeptime); break;
        case '+': sleeptime += 1e3; printf("t:%f\n",sleeptime); break;
        //case 'x': getchar_unlocked(); break;
        case 3:
        case 'C': reset_terminal_mode(); exit(0);
        default:
          printf("c:%02x\n", ch);
      }
      if(ch>0){
        usleep(2e5); }
      
    }
    update();
    showDots();
    usleep(sleeptime);
  }
  return 0;
}

//eof
