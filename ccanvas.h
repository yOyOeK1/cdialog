#include "ccNode.h"

int *widgetTick(  struct ccNode *cN, int frameNo );
int *fUpdateDef( struct ccNode *cN, int frameNo );
void *dogLooper( void *vargp );
int ccInit_FB();
int ccFree_FB();
int ccInit();
int ccUpdate();
int cc_printf( int x, int y, char *msg );
int ccDraw();
char *ccGetPX( int x, int y );
void ccClear( char cBlank );
void ccRender();
