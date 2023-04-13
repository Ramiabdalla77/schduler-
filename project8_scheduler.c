/*My name is Rami Abdalla. Last editied 5/12/2023. U30474133. This program is a scheduler that allows users to perform various operations on a list of jobs. It has 6 functions: adding a job to the scheduler, removing a job from the scheduler, listing all jobs that belong to a specific user, listing all jobs that meet certain criteria for GPU, CPU, time, and memory, listing all jobs in the scheduler, and deleting all jobs from the scheduler. The user can select which operation they want to perform based on a list of operational codes displayed by the program. The program uses a linked list to manage the jobs in the scheduler. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//////////////////////
// data definitions //
//////////////////////

#define NAME_LEN 20
#define SIZE_LEN 3

struct job {
	char job_name[NAME_LEN+1], user_name[NAME_LEN+1];
	int num_cpus, num_gpus, memory, priority;
	double time;
	struct job *next;
};

/////////////////////////
// function prototypes //
/////////////////////////

void help();
void read(char *job_name, char *user_name, int *num_cpus, int *num_gpus, int *memory, double *time, int *priority);
struct job * add_job(struct job *scheduler, char *job_name, char *user_name, int num_cpus, int num_gpus, int memory, double time, int priority);
struct job * pop_job(struct job *scheduler);
void list_user(struct job *scheduler, char *user_name);
void list_jobs(struct job *scheduler, int num_cpus, int num_gpus, int memory, double time);
void list_all_jobs(struct job *scheduler);
struct job * clear_jobs(struct job *scheduler);

///////////////////
// main function //
///////////////////

int main() {
	char code;
	char job_name[NAME_LEN+1], user_name[NAME_LEN+1];
	int num_cpus, num_gpus, memory, priority;
	double time;

	struct job *scheduler = NULL;

	help();
	printf("\n");

	for (;;) {
		// read operation code
		printf("Enter operation code: ");
		scanf(" %c", &code);
		while(getchar() != '\n') /* skips to end of line */
			;

		// run operation
		switch (code) {
			case 'h':
				help();
				break;
			case 'a':
				read(job_name, user_name, &num_cpus, &num_gpus, &memory, &time, &priority);
				scheduler = add_job(scheduler, job_name, user_name, num_cpus, num_gpus, memory, time, priority);
				break;
			case 'p':
				scheduler = pop_job(scheduler);
				break;
			case 'u':
				read(NULL, user_name, NULL, NULL, NULL, NULL, NULL);
				list_user(scheduler, user_name);
				break;
			case 'j':
				read(NULL, NULL, &num_cpus, &num_gpus, &memory, &time, NULL);
				list_jobs(scheduler, num_cpus, num_gpus, memory, time);
				break;
			case 'l':
				list_all_jobs(scheduler);
				break;
			case 'q':
				scheduler = clear_jobs(scheduler);
				return 0;
			default:
				printf("Illegal operation code!\n");
		}
		printf("\n");
	}
}

//////////////////////////
// function definitions //
//////////////////////////

void help() {
	printf("List of operation codes:\n");
	printf("\t'h' for help;\n");
	printf("\t'a' for adding a job to the scheduler;\n");
	printf("\t'p' for removing a job from the scheduler;\n");
	printf("\t'u' for searching jobs per user;\n");
	printf("\t'j' for searching jobs per capacity;\n");
	printf("\t'l' for listing all jobs;\n");
	printf("\t'q' for quit.\n");
}

void read(char *job_name, char *user_name, int *num_cpus, int *num_gpus, int *memory, double *time, int *priority) {
	if(job_name != NULL) {
		printf("Enter the name of the job: ");
		scanf("%s", job_name);
	}
	if(user_name != NULL) {
		printf("Enter the name of the user: ");
		scanf("%s", user_name);
	}
	if(num_cpus != NULL) {
		printf("Enter the number of CPUs: ");
		scanf("%d", num_cpus);
	}
	if(num_gpus != NULL) {
		printf("Enter the number of GPUs: ");
		scanf("%d", num_gpus);
	}
	if(memory != NULL) {
		printf("Enter the amount of memory: ");
		scanf("%d", memory);
	}
	if(time != NULL) {
		printf("Enter the amount of time: ");
		scanf("%lf", time);
	}
	if(priority != NULL) {
		printf("Enter the priority: ");
		scanf("%d", priority);
	}
}

// Function to add a new job to the scheduler
// Takes the scheduler, job name, user name, number of CPUs, number of GPUs, memory, time, and priority as inputs
// Returns the updated scheduler after adding the new job

struct job * add_job(struct job *scheduler, char *job_name, char *user_name, int num_cpus, int num_gpus, int memory, double time, int priority) {
    // Allocate memory for the new job
    struct job *new_job = malloc(sizeof(struct job));   
    if (new_job == NULL) {       
        printf("Error allocating memory.\n");       
    }
  
    // Set the values of the new job
    strcpy(new_job->job_name, job_name);       
    strcpy(new_job->user_name, user_name);    
    new_job->num_cpus = num_cpus;
    new_job->num_gpus = num_gpus;
    new_job->memory = memory;               
    new_job->time = time;
    new_job->priority = priority;
    new_job->next = NULL;
  
   // If the scheduler is empty, set the new job as the first job
   if (scheduler == NULL) {
        scheduler = new_job;
    } 
    // Otherwise, iterate through the scheduler until the last job is found, and set the new job as the last job
    else {
        struct job *curr;
        for (curr = scheduler; curr->next != NULL; curr = curr->next) {
            
        }
        curr->next = new_job;
    }
    // Return the updated scheduler
    return scheduler;
}

/*
This function takes the head of a linked list of jobs and removes the first job from the list.
If the list is empty, it returns NULL.
It prints the details of the job that was removed before freeing its memory.
*/


struct job * pop_job(struct job *scheduler) {

  if(scheduler == NULL){     
    return NULL;              
  }

  struct job *curr = scheduler;   // Set the first job as the one to be removed
  scheduler = scheduler->next;   // Set the second job as the new head of the list
  printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
  printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
  printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
  printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", curr->job_name, curr->user_name, curr->num_cpus, curr->num_gpus, curr->memory, curr->time, curr->priority);
  printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
  
  

    

  free(curr);     // Frees the memory, removing it form scheduler 
  return scheduler;  //Returns the updated schuduler after removing 

}


void list_user(struct job *scheduler, char *user_name) {

	struct job *curr=scheduler;
  int checker=0;     // Flag to check if user_name is found in the linked list 

  // Search linked list for job with provided user_name
  while(curr!=NULL){    
    if(strcmp(curr->user_name, user_name) == 0){     // Compare user_name of job with provided user_name 
      checker=1;                                   
      break;
    }
    
    curr=curr->next; 
  }
  
  if(!checker){    // If user_name is not found, return NULL
    return NULL;      
  }
  else{  // Otherwise, print table of job details
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
     
  }    
    

  while (curr!=NULL){   // Iterate through linked list and print details of each job associated with the user_name   
    if(strcmp(curr->user_name, user_name) == 0){    // Check if job has the provided user_name

      printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", curr->job_name, curr->user_name, curr->num_cpus, curr->num_gpus, curr->memory, curr->time, curr->priority); 
      printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    } 
    curr = curr->next; // Move to the next job in the linked list
  }
}
  
    




void list_jobs(struct job *scheduler, int num_cpus, int num_gpus, int memory, double time) {
    struct job *curr = scheduler;
    int checker=0;          
    // Loop through the linked list to check if there are any jobs that meet the requirements
    for (; curr != NULL; curr = curr->next) {   
      
      if (curr->num_cpus >= num_cpus && curr->num_gpus >= num_gpus && curr->memory >= memory && curr->time <= time) {
        checker = 1;    // Set the checker to 1 if there is at least one job that meets the requirements
        break;
      }  
     }

  
    if(!checker){    // If there are no jobs that meet the requirements, return null
      return NULL;
    }
    else{      
      printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
      printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
      printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
     
    }
    
  // Loop through the linked list again to print the details of the jobs that meet the requirements
    for(struct job* curr = scheduler; curr != NULL; curr = curr->next) {
    if(curr->num_cpus >= num_cpus && curr->num_gpus >= num_gpus && curr->memory >= memory && curr->time <= time) {
        printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", curr->job_name, curr->user_name, curr->num_cpus, curr->num_gpus, curr->memory, curr->time, curr->priority); 
        printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    }
}


}


void list_all_jobs(struct job *scheduler) {
// Initialize the pointer to the first job in the scheduler
	struct job *curr=scheduler;

  // If the scheduler is not empty, print the header for the table
  if(scheduler!=NULL){   
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
    printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");    
  }
    
  // Loop through each job in the scheduler and print its information in the table format
  for (struct job* curr = scheduler; curr != NULL; curr = curr->next) {
    printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", curr->job_name, curr->user_name, curr->num_cpus, curr->num_gpus, curr->memory, curr->time, curr->priority);
    printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
}

}

struct job * clear_jobs(struct job *scheduler) { 

  struct job *first=scheduler; // Pointer to the first job in the scheduler
	struct job *curr=first;        // Current job pointer
  struct job *next;            // Pointer to the next job

  // Loop through all jobs in the scheduler and free the memory allocated for each job
  for (; curr != NULL; curr = next) {   
    next = curr->next;          // Set next pointer before freeing current job
    free(curr);                  // Free memory allocated for current job

}

}

