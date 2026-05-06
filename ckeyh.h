/* file: [ ./ckeyh.c ] */
void key_mouseKey_disable();
void key_mouseKey_disable_byNode( int nId, cnn_Msg *msgT );
void key_mouseKey_modeMouse( int modeNo );
void key_mouseKey_enable();
void key_mouseKey_enable_byNode( int nId, cnn_Msg *msgT );
char *key_getCurrentMode_name();
int key_chk_KeyBinds(  );
void cnn_keyBind_on_OK( int kbId );
void keyPrintf_helpForCurrentMode();
int keyBindDoIt();
