#ifndef PDS_H
#define PDS_H

// Error codes
#define PDS_SUCCESS 0
#define PDS_FILE_ERROR 1
#define PDS_ADD_FAILED 2
#define PDS_REC_NOT_FOUND 3
#define PDS_REPO_ALREADY_OPEN 12
#define PDS_NDX_SAVE_FAILED 13
#define PDS_REPO_NOT_OPEN 14

// Repository status values
#define PDS_REPO_OPEN 10
#define PDS_REPO_CLOSED 11

struct PDS_NdxInfo{
	int key;
	int offset;
};

struct PDS_RepoInfo{
	char pds_name[30];
	FILE *pds_data_fp;
	FILE *pds_ndx_fp;
	int repo_status; 
	int rec_size; // For fixed length records
	struct BST_Node *pds_bst;
};

extern struct PDS_RepoInfo repo_handle;

// pds_open
// Open the data file and index file in rb+ mode
// Update the fields of PDS_RepoInfo appropriately
// Build BST and store in pds_bst by reading index entries from the index file
// Close only the index file
int pds_open( char *repo_name, int rec_size );

// pds_load_ndx
// Internal function used by pds_open to read index entries into BST
int pds_load_ndx();

// put_rec_by_key
// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to BST using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
int put_rec_by_key( int key, void *rec );

// get_rec_by_key
// Search for index entry in BST
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
int get_rec_by_ndx_key( int key, void *rec );

// Search based on a key field on which an index 
// does not exist. This function actually does a full table scan 
// by reading the data file until the desired record is found.
// The io_count is an output parameter to indicate the number of records
// that had to be read from the data file for finding the desired record
int get_rec_by_non_ndx_key( 
void *key,  			/* The search key */
void *rec,  			/* The output record */
int (*matcher)(void *rec, void *key), /*Function pointer for matching*/
int *io_count  		/* Count of the number of records read */
); 

// pds_close
// Open the index file in wb mode (write mode, not append mode)
// Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
// Free the BST by call bst_destroy()
// Close the index file and data file
int pds_close();


#endif
