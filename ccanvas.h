
/* auto header for [ ./ccanvas.c ] */

int *fUpdateDef( struct ccNode *cN, int frameNo );
int *widgetTick(  struct ccNode *cN, int frameNo );
void *dogBatteryLooper( void *vargp );
void *dogTimeLooper( void *vargp );
void *dogLooper( void *vargp );
void dogsStart();
void dogsStop();
int ccInit_FB_byPointer( char **pts, int dcol, int drow );
int ccInit_FB();
int ccFree_FB();
char *cc_getPx( int x, int y );
char *cc_getPx_byPointer( char *pts, int x, int y, int icol);
int ccInit();
int ccUpdate();
int cc_clear( char cBlank );
int cc_clear_byPointer( char **pts, char chf, int drow, int dcol );
int cc_printf( int x, int y, char *msg );
int ccDraw();
void ccRender();
void ccRender_byId( int cId );


