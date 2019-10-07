#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pds.h"
#include "patient.h"


int initialize_db( char *db_name , int rec_size )
{
  return pds_open( db_name, rec_size );
}
int add_patient(struct Patient *p)
{
	return put_rec_by_key( p->patient_id, p );
}

int get_patient_by_key(struct Patient *p )
{
	return get_rec_by_ndx_key(p-> patient_id, p );
}

int get_patient_by_number(struct Patient *p , int io_count)
{
  return get_rec_by_non_ndx_key( p->patient_number, p, match_patient_number, io_count);
}

int modify_patient(int id, struct Patient *p )
{
	return modify_rec_by_key( id, p );
}

int delete_patient(struct Patient *p )
{
  return delete_rec_by_ndx_key( p->patient_id );
}

int match_patient_number( struct Patient *p, int number )
{
  if( p->patient_number == number)
    return 0;
  else
    return 1;
}


int close_db()
{
  return pds_close();
}

int fill_patient_attributes( struct Patient *p )
{
  char id[50];
  sprintf(id,"%d",p->patient_id);
	p->patient_number = p->patient_id + 10000;
	strcpy(p->firstname, "firstname of " );
	strcpy(p->lastname, "lastname of " );
	strcpy(p->phone, "phone of " );
  strcpy(p->address, "address of " );
  strcpy(p->email, "email of " );
	strcat(p->firstname, id);
	strcat(p->lastname, id);
	strcat(p->phone, id);
  strcat(p->address, id);
  strcat(p->email, id);
  p->gender = p->patient_id % 2;   //return 0 or 1
	p->age = p->patient_id%90;       // returns something less than 90
  p->blood_pressure = p->patient_id%20;
  p->cholestrol = p->patient_id%20;
  p->bmi = p->patient_id%20;
  p->insulin = p->patient_id%20;
}

void print_patient_info( struct Patient p)
{
  printf("\n\nAttributes of patient:\npatient_id : %d\npatient_number : %d\nfirstname : %s\nlastname : %s\nphone : %s\naddress : %s\nemail : %s\ngender : %d\nage : %d\nblood_pressure : %f\ncholestrol : %f\nbmi : %f\ninsulin : %f\n",
      p.patient_id,
      p.patient_number,
      p.firstname,
      p.lastname,
      p.phone,
      p.address,
      p.email,
      p.gender,
      p.age,
      p.blood_pressure,
      p.cholestrol,
      p.bmi,
      p.insulin);
}
