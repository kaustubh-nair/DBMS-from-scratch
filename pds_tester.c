#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "contact.h"

#define TREPORT(a1,a2) printf("Status %s: %s\n\n",a1,a2); fflush(stdout);

void process_line( char *test_case );

main(int argc, char *argv[])
{
	FILE *cfptr;
	char test_case[50];

	if( argc != 2 ){
		fprintf(stderr, "Usage: %s testcasefile\n", argv[0]);
		exit(1);
	}

	cfptr = (FILE *) fopen(argv[1], "r");
	while(fgets(test_case, sizeof(test_case)-1, cfptr)){
		// printf("line:%s",test_case);
		if( !strcmp(test_case,"\n") || !strcmp(test_case,"") )
			continue;
		process_line( test_case );
	}
}

void process_line( char *test_case )
{
	char repo_name[30];
	char command[50], param1[50], param2[50], info[1000];
	char phone_num[10];
	int contact_id, status, rec_size, expected_status, expected_io, actual_io;
	char expected_name[50], expected_phone[50];
	struct Contact testContact;

	rec_size = sizeof(struct Contact);

	sscanf(test_case, "%s%s%s", command, param1, param2);
	printf("Test case: %s", test_case); fflush(stdout);
	if( !strcmp(command,"OPEN") ){
		strcpy(repo_name, param1);
		if( !strcmp(param2,"0") )
			expected_status = CONTACT_SUCCESS;
		else
			expected_status = CONTACT_FAILURE;

		status = pds_open( repo_name, rec_size );
		if(status == PDS_SUCCESS)
			status = CONTACT_SUCCESS;
		else
			status = CONTACT_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"pds_open returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
	else if( !strcmp(command,"STORE") ){
		if( !strcmp(param2,"0") )
			expected_status = CONTACT_SUCCESS;
		else
			expected_status = CONTACT_FAILURE;

		sscanf(param1, "%d", &contact_id);
		testContact.contact_id = contact_id;
		sprintf(testContact.contact_name,"Name-of-%d",contact_id);
		sprintf(testContact.phone,"Phone-of-%d",contact_id);
		status = add_contact( &testContact );
		if(status == PDS_SUCCESS)
			status = CONTACT_SUCCESS;
		else
			status = CONTACT_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"add_contact returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
	else if( !strcmp(command,"NDX_SEARCH") ){
		if( strcmp(param2,"-1") )
			expected_status = CONTACT_SUCCESS;
		else
			expected_status = CONTACT_FAILURE;

		sscanf(param1, "%d", &contact_id);
		testContact.contact_id = -1;
		status = search_contact( contact_id, &testContact );
		if(status == PDS_SUCCESS)
			status = CONTACT_SUCCESS;
		else
			status = CONTACT_FAILURE;
		if( status != expected_status ){
			sprintf(info,"search key: %d; Got status %d",contact_id, status);
			TREPORT("FAIL", info);
		}
		else{
			// Check if the retrieved values match
			if( expected_status == 0 ){
				sprintf(expected_name,"Name-of-%d",contact_id);
				sprintf(expected_phone,"Phone-of-%d",contact_id);
				if (testContact.contact_id == contact_id && 
					strcmp(testContact.contact_name,expected_name) == 0 &&
					strcmp(testContact.phone,expected_phone) == 0){
						TREPORT("PASS", "");
				}
				else{
					sprintf(info,"Contact data not matching... Expected:{%d,%s,%s} Got:{%d,%s,%s}\n",
						contact_id, expected_name, expected_phone, 
						testContact.contact_id, testContact.contact_name, testContact.phone
					);
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"NON_NDX_SEARCH") ){
		if( strcmp(param2,"-1") )
			expected_status = CONTACT_SUCCESS;
		else
			expected_status = CONTACT_FAILURE;

		sscanf(param1, "%s", phone_num);
		sscanf(param2, "%d", &expected_io);
		testContact.contact_id = -1;
		int actual_io = 0;
		if(status == PDS_SUCCESS)
			status = CONTACT_SUCCESS;
		else
			status = CONTACT_FAILURE;
		status = search_contact_by_phone( phone_num, &testContact, &actual_io );
		if( status != expected_status ){
			sprintf(info,"search key: %d; Got status %d",contact_id, status);
			TREPORT("FAIL", info);
		}
		else{
			// Check if the retrieved values match
			// Check if num block accesses match too
			// Extract the expected contact_id from the phone number
			sscanf(phone_num+sizeof("Phone-of"), "%d", &contact_id);
			sprintf(expected_name,"Name-of-%d",contact_id);
			sprintf(expected_phone,"Phone-of-%d",contact_id);
			if( expected_status == 0 ){
				if (testContact.contact_id == contact_id && 
					strcmp(testContact.contact_name, expected_name) == 0 &&
					strcmp(testContact.phone, expected_phone) == 0 ){
						if( expected_io == actual_io ){
							TREPORT("PASS", "");
						}
						else{
							sprintf(info,"Num I/O not matching for %d... Expected:%d Got:%d\n",
								contact_id, expected_io, actual_io
							);
							TREPORT("FAIL", info);
						}
				}
				else{
					sprintf(info,"Contact data not matching... Expected:{%d,%s,%s} Got:{%d,%s,%s}\n",
						contact_id, expected_name, expected_phone, 
						testContact.contact_id, testContact.contact_name, testContact.phone
					);
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"CLOSE") ){
		if( !strcmp(param1,"0") )
			expected_status = CONTACT_SUCCESS;
		else
			expected_status = CONTACT_FAILURE;

		status = pds_close();
		if(status == PDS_SUCCESS)
			status = CONTACT_SUCCESS;
		else
			status = CONTACT_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"pds_close returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
}


