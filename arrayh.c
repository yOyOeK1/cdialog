
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFMAX 4098


struct msg{
	int inDb;
	char topic[BUFMAX];
	int topicId;
	char msg[BUFMAX];
	int entryDate;
};


struct topic{
	int id;
	char topic[BUFMAX];
	char tableName[BUFMAX];
};

int topicsCount = 0;
struct topic * topics;



struct topic topicPut( int id, char *topic, char *tableName){
	struct topic tmp[topicsCount];
	for(int t=0;t<topicsCount;t++){
		tmp[t] = topics[t];
	}
	topics = malloc( (topicsCount+1)*sizeof(struct topic) );
	for(int t=0;t<topicsCount;t++){
		topics[t] = tmp[t];
	}

	topics[ topicsCount ].id = id;
	strcpy( topics[topicsCount].topic, topic );
	strcpy( topics[topicsCount].tableName, tableName );

	topicsCount++;

	return topics[ (topicsCount-1) ];
}





int getTopicIndex( char *topic ){
	for(int t=0;t<topicsCount;t++)
		if( strcmp(topics[t].topic, topic ) == 0 )
			return t;

	return -1;
}

struct topic getTopic(char *topic){
	int index = getTopicIndex( topic );
	if( index != -1 ){
		printf("topic from cashe\n");
		return topics[index];
	}

	return topicPut( 1, topic, "aa");
}



// putMsg( message->topic, message->payload );
int main(){

	printf("array test ... \n");
	int idC = 0;
	topicPut( idC++, "testId0", "as table name is id:0" );
	topicPut( idC++, "testId1", "as table name is id:1" );

	int fRes = getTopicIndex( "testId1" );
	printf(" ... find result is [ %i ] = [ 1 ]\n", fRes );
	printf(" ... topic of [0] [ %s ]\n" , topics[0].topic );

	printf("array test ... DONE\n");
	

}
