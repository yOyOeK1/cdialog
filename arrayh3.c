

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct{
	int id;
	int pts;
} arhItem;

typedef struct{
	char name[512];
	//arhItem items[];
	int *ids;
	unsigned long *items;
	int count;
	int nextId;
} arhArray;


arhArray arh_init( char *aname ){
	arhArray atr;
	strcpy( atr.name, aname );
	atr.count = 0;
	atr.ids = (int*)malloc( (1)*sizeof( int ) );
	atr.items = (unsigned long *)malloc( (1)*sizeof( unsigned long ) );
	atr.nextId = 1;
	return atr;
}

/** to add new item */
int arh_put( arhArray *apts, unsigned long pts ){
	printf( "arh ... put count[%i] pts[%p]\n", apts->count, pts );
	int itms[ apts->count ];

	for( int t=0; t<apts->count; t++ ){
		itms[ t ] = apts->items[ t ];
	} 
	
	apts->items = malloc( ( apts->count+1 )*sizeof( unsigned long ) );
	for( int t=0; t<apts->count; t++ ){
		apts->items[ t ] = itms[ t ];
	} 
	
	apts->items[ apts->count ] = pts;
	apts->ids[ apts->count ] = apts->nextId;

	apts->count++;
	apts->nextId++;

	return apts->nextId - 1;
}

int arh_getIndex( arhArray *apts, int id ){
	for( int t=0; t<apts->count; t++ ){
		if( apts->ids[ t ] == id ){
			return t;
		}
	}
	return -1;
}

#ifdef CPPARRAYH

arhArray ar0;

int main(){
		
	ar0 = arh_init("a_test_001");
	printf("ar0 name [%s]\n", ar0.name );
	char *strTmp0 = "hello array with pointers";
	printf(" pts to str [%p]\n", (void*)strTmp0 );
	arh_put( &ar0, 11 );
	arh_put( &ar0, 12 );
	arh_put( &ar0, 13 );
	arh_put( &ar0, 14 );
	int sId = arh_put( &ar0, (unsigned long)strTmp0 );

	printf("ar0.items[0] [%i]\n", ar0.items[0] );
	printf("ar0.items[2] [%i]\n", ar0.items[2] );
	printf("ar0.items[4] [%i]\n", ar0.items[4] );
	printf("ar0.items[4] [%s] ... as char* with id[%i]/[%i]\n", (char *)ar0.items[4], ar0.ids[4], sId  );
	int arId2 = arh_getIndex( &ar0, 2 );
	printf("ar0.items by id 2 [%i] index [%i]\n", ar0.items[ arId2 ], arId2 );
	return 0;
}
#endif
