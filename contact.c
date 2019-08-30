#include<stdio.h>
#include<stdlib.h>

#include "pds.h"
#include "contact.h"

// Load all the contacts from a CSV file
int store_contacts( char *contact_data_file )
{
	FILE *cfptr;
	char contact_line[500], token;
	struct Contact c, dummy;

	cfptr = (FILE *) fopen(contact_data_file, "r");
	while(fgets(contact_line, sizeof(contact_line)-1, cfptr)){
		//printf("line:%s",contact_line);
		sscanf(contact_line, "%d%s%s", &(c.contact_id),c.contact_name,c.phone);
		print_contact( &c );
		add_contact( &c );
	}
}

void print_contact( struct Contact *c )
{
	printf("%d,%s,%s\n", c->contact_id,c->contact_name,c->phone);
}

// Use get_rec_by_key function to retrieve contact
int search_contact( int contact_id, struct Contact *c )
{
	return get_rec_by_ndx_key( contact_id, c );
}

// Add the given contact into the repository by calling put_rec_by_key
int add_contact( struct Contact *c )
{
	int status;

	status = put_rec_by_key( c->contact_id, c );

	if( status != PDS_SUCCESS ){
		fprintf(stderr, "Unable to add contact with key %d. Error %d", c->contact_id, status );
		return CONTACT_FAILURE;
	}
	return status;
}

int search_contact_by_phone( char *phone, struct Contact *c, int *io_count )
{
  return get_rec_by_non_ndx_key( phone, c, match_contact_phone, io_count);
}

int match_contact_phone( struct Contact *c, char *phone )
{
  if( strcmp(c->phone, phone) == 0)
    return 0;
  else
    return 1;
}
