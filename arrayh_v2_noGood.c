
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFMAX 4098


struct aItem{
	int id;
	char topic[BUFMAX];
	char payload[BUFMAX];
};
int aItemsCount = 0;
struct aItem * aItems;

struct aItem aItemPut( struct aItem *aIts, int id, char *topic, char *payload){
	struct aItem tmp[aItemsCount];
	printf("1\n");
	for(int t=0;t<aItemsCount;t++)
		tmp[t] = aIts[t];
	
	aIts = malloc( (aItemsCount+1)*sizeof(struct aItem) );
	for(int t=0;t<aItemsCount;t++)
		aIts[t] = tmp[t];
	

	aIts[ aItemsCount ].id = id;
	strcpy( aIts[aItemsCount].topic, topic );
	strcpy( aIts[aItemsCount].payload, payload );
	aItemsCount++;
	return aIts[ (aItemsCount-1) ];
}

/*
int getTopicIndex(  struct aItem &aIts, char *topic ){
	for(int t=0; t<aItemsCount ; t++ )
		if( strcmp( aIts[t].topic, topic ) == 0 )
			return t;
	return -1;
}

struct aItem getTopic( struct aItem &aIts, char *topic){
	int index = getTopicIndex( aIts, topic );
	if( index != -1 ){
		printf("aItem from cashe\n");
		return aIts[index];
	}

	return aItemPut( aIts, 1, topic, "aa");
}

*/

// putMsg( message->topic, message->payload );
int main(){

	printf("array test ... \n");
	
	struct aItem *myIts; 
	int idC = 0;
	
	aItemPut( myIts, idC++, "testId0", "as table name is id:0" );
//	aItemPut( &myIts, idC++, "testId1", "as table name is id:1" );

	//int fRes = getTopicIndex( myIts, "testId1" );
	//printf(" ... find result is [ %i ] = [ 1 ]\n", fRes );
	//struct aItem ait = getTopic( myIts, "testId0");
	//printf(" ... find result is [ %i ] = [ 0 ]\n", ait.id );
	printf(" ... aItem of [0] [ %s ]\n" , myIts[0].topic );

	printf("array test ... DONE\n");
	

}
