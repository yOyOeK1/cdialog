#include "ccNode.h"

/* auto header for [ ./ccanvas.c ] */

int *fUpdateDef( struct ccNode *cN, int frameNo );
int *widgetTick(  struct ccNode *cN, int frameNo );
void *dogBatteryLooper( void *vargp );
void *dogTimeLooper( void *vargp );
void *dogLooper( void *vargp );
void dogsStart();
void dogsStop();
int ccInit_FB();
int ccFree_FB();
int ccInit();
char *cc_getPx( int x, int y );
int ccUpdate();
int cc_clear( char cBlank );
int cc_printf( int x, int y, char *msg );
int ccDraw();
void ccRender();


