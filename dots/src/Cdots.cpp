//$Id: doAdc.c 82 2014-08-28 18:45:21Z beb $


#include "Cdots.h"
#include "stdlib.h"

static U32 m_cnt = 0;
static U32 m_id = 0;

CDots::CDots(ws2812Color color, U32 maxpos, float speed, BOOL direction) {
  this->init(color, maxpos, speed, direction);
}

void CDots::init(ws2812Color color, U32 maxpos, float speed, BOOL direction) {
  this->color = color;
  this->speed = speed;
  this->direction = direction;
  this->pos = 0;
  this->maxPos = maxpos;
  this->id = ++m_id;
  m_cnt++;
}

CDots::~CDots(){
  m_cnt--;
}

void CDots::doProc(){
  pos += speed * direction;
  if(pos >= maxPos){
    pos = maxPos;
    direction = -direction;
  }
  if(pos <= 0){
    pos = 0;
    direction = -direction;
  }
}

U32 cdotsGetCnt(void){
  return m_cnt;
}

ws2812Color CDots::getColor(void){
  return this->color;
}

U32 CDots::getPos(void){
  return static_cast<U32>(this->pos);
}
U32 CDots::getId(void){
  return this->id;
}

//eof

