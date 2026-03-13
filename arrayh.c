
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



struct aItem aItemPut( int id, char *topic, char *payload){
	struct aItem tmp[aItemsCount];
	for(int t=0;t<aItemsCount;t++){
		tmp[t] = aItems[t];
	}
	aItems = malloc( (aItemsCount+1)*sizeof(struct aItem) );
	for(int t=0;t<aItemsCount;t++){
		aItems[t] = tmp[t];
	}

	aItems[ aItemsCount ].id = id;
	strcpy( aItems[aItemsCount].topic, topic );
	strcpy( aItems[aItemsCount].payload, payload );

	aItemsCount++;

	return aItems[ (aItemsCount-1) ];
}





int getTopicIndex( char *topic ){
	for(int t=0;t<aItemsCount;t++)
		if( strcmp(aItems[t].topic, topic ) == 0 )
			return t;

	return -1;
}

struct aItem getTopic(char *topic){
	int index = getTopicIndex( topic );
	if( index != -1 ){
		printf("aItem from cashe\n");
		return aItems[index];
	}

	return aItemPut( 1, topic, "aa");
}



// putMsg( message->topic, message->payload );
int main(){

	printf("array test ... \n");
	int idC = 0;
	aItemPut( idC++, "testId0", "as table name is id:0" );
	aItemPut( idC++, "testId1", "as table name is id:1" );

	int fRes = getTopicIndex( "testId1" );
	printf(" ... find result is [ %i ] = [ 1 ]\n", fRes );
	struct aItem ait = getTopic("testId0");
	printf(" ... find result is [ %i ] = [ 0 ]\n", ait.id );
	printf(" ... aItem of [0] [ %s ]\n" , aItems[0].topic );

	printf("array test ... DONE\n");
	

}
