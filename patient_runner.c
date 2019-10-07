#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "patient.h"

#define PRINT_OPTIONS printf("OPTIONS:\n1.Add patient\n2.Delete patient\n3.Modify patient\n4.Search patient by id\n5.Search patient by number\n0.Exit\n");

void custom_print(char *string);
void print_error(int status);


void main(int argc, char *argv[])
{
  int io_count = 0;
  char db_name[20];
  int option,status;
  int rec_size = sizeof(struct Patient);
  printf("Enter database name\n");
  gets(db_name);
  status = initialize_db( db_name, rec_size );
  if( status == 0 )
    custom_print("SUCCESS");
  else if( status == 1 )
    custom_print("PDS_FILE_ERROR");
  else if( status == 12 )
    custom_print("PDS_REPO_ALREADY_OPEN");

  while(1)
  {
    io_count++;
    PRINT_OPTIONS
    printf("\nEnter option: ");
    scanf("%d",&option);

    if( option == 0)
    {
      close_db();
      exit(0);
    }
    struct Patient p;

    if( option == 1)
    {
      printf("Enter patient id: ");
      scanf("%d", &p.patient_id);
      fill_patient_attributes( &p );
      status = add_patient( &p );
      print_error(status);
    }

    else if( option == 2)
    {
      printf("Enter patient id: ");
      scanf("%d", &p.patient_id);
      status = delete_patient( &p );
      print_error(status);
    }

    else if( option == 3)
    {
      int id,newId;
      printf("Enter patient id: ");
      scanf("%d",&id);
      printf("Enter new id: ");
      fflush(stdin);
      scanf("%d", &newId);
      p.patient_id = newId;
      fill_patient_attributes( &p );
      status = modify_patient( id, &p );
      print_error(status);

    }
    else if( option == 4)
    {
      printf("Enter patient id: ");
      scanf("%d", &p.patient_id);
      status = get_patient_by_key( &p );
      if(status == 0)
        print_patient_info(p);
      print_error(status);
    }
    else if( option == 5)
    {
      printf("Enter patient number: ");
      scanf("%d", &p.patient_number);
      status = get_patient_by_number( &p, io_count );
      if(status == 0)
        print_patient_info(p);
      print_error(status);
    }
    else
      printf("\nPlease enter a valid option\n\n\n");
  }
}

void custom_print(char *string)
{
    printf("\n======================================\n %s \n======================================\n\n\n", string);
}

void print_error(int status)
{
    char s[5];
    char output[100] = "";
    if( status == 0)
      custom_print("SUCCESS");
    else
    {
      sprintf(s,"%d",status);
      strcat(output, "Database returned error code: ");
      strcat(output, s);
      custom_print(output);
    }
}
