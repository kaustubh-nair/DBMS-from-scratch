#include<stdio.h>
#include<stdlib.h>

#include "pds.h"
#include "contact.h"

main( int argc, char *argv[] )
{
	char *datafile; 
	char *repo_name; 

	int status, rec_size;

	if( argc != 3 ){
		fprintf(stderr, "Usage: %s <repo-name> <dump-file-name>\n", argv[0]);
		exit(1);
	}
	
	repo_name = argv[1];
	datafile = argv[2];

	rec_size = sizeof(struct Contact);

	status = pds_open( repo_name, rec_size );
	if( status != PDS_SUCCESS ){
		fprintf(stderr, "Unable to open repository %s - Error %d\n", repo_name, status );
		exit(status);
	}

	store_contacts( datafile );
	pds_close();
}

