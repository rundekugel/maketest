//$Id: doAdc.h 68 2014-08-18 16:02:47Z beb $


#ifndef __CDOTS_H__
#define __CDOTS_H__

//#include "rtl.h"
#include "types.h"
//#include "ws2812.h"

#define CDOTS_MAX  (230)

#ifdef __cplusplus
  extern "C" {
#endif

U32 cdotsGetCnt(void);

#ifdef __cplusplus
  }
#endif

#define ws2812Color   int

class CDots {
  public:
    CDots(ws2812Color color, U32 maxpos, float speed, BOOL direction);
    CDots(ws2812Color color, U32 maxpos, float speed){ 
      this->init(color, maxpos, speed, 1);
    }

    ~CDots();
    
    void init(ws2812Color color, U32 maxpos, float speed, BOOL direction);
    ws2812Color getColor(void);
    U32 getPos(void);
    U32 getId(void);
    void doProc();

  private:
    ws2812Color color;
    float speed;
    S8 direction;
    float pos;
    U32 maxPos;
    U32 id;
};


#endif // __BARGRAPH_H__


//eof

