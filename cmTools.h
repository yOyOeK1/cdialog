/* file: [ ./cmTools.c ] */
void cmtDeb_dump();
int cmtDeb( char *blame, const char *format, ... );
void cmt_start_byNode( machNode mn );
void cmt_NodeName( char *type, int id, char *name );
void cmt_hashsDump( );
void cmt_dump_msgs( int nId, cnn_Msg *msgT );
void cmt_debug_on( int nId, cnn_Msg *msgT );
void cmt_debug_off( int nId, cnn_Msg *msgT );
