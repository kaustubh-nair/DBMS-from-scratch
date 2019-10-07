#ifndef PATIENT_H
#define PATIENT_H
#include <stdbool.h>

#define PATIENT_SUCCESS 0
#define PATIENT_FAILURE 1
 
struct Patient{
	int patient_id;
	int patient_number;
	char firstname[30];
	char lastname[30];
	char phone[30];
  char address[50];
  char email[40];
  bool gender;   //0 male 1 female
	int age;
  float blood_pressure;
  float cholestrol;
  float bmi;
  float insulin;
};
extern struct PDS_RepoInfo *datastore;

int initialize_db(char *db_name, int rec_size);
int add_patient(struct Patient *p);
int get_patient_by_key(struct Patient *p );
int get_patient_by_number(struct Patient *p , int io_count);
int modify_patient(int id, struct Patient *p );
int delete_patient(struct Patient *p );
int match_patient_number( struct Patient *p, int number );
int close_db();
#endif
