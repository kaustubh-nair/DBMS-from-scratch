#ifndef PATIENT_H
#define PATIENT_H

#define PATIENT_SUCCESS 0
#define PATIEN_FAILURE 1
 
struct Patient{
	int patient_id;
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

int add_patient();
int get_patient_by_key();
int get_patient_by_phone();
int modify_patient();
int delete_patient();
