/*
#AGGELOS NIKOLAOS POTAMIANOS, 1084537
#GRIGORIOS TZWRTZAKIS, 1084538
#ANDREAS KATSAROS, 1084522
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PROCESSES 100

typedef enum {
  READY,
  RUNNING,
  STOPPED,
  EXITED
} process_state_t;

typedef struct process {
  int pid;
  char exec_file[100];
  int priority;
  process_state_t state;
  struct process *prev;
  struct process *next;
  //Aparaithta gia tous algorithmous
  int burst_time; 
  int wait_time; 
  int turn_around_time;
  //telos edw
} process_t;

process_t *head = NULL;
process_t *tail = NULL;

void insert_process(process_t *process) {
  if (head == NULL) {
    head = tail = process;
  } else {
    tail->next = process;
    process->prev = tail;
    tail = process;
  }
}

process_t *pop_process() {
  process_t *process = head;
  if (head != NULL) {
    head = head->next;
    if (head != NULL) {
      head->prev = NULL;
    }
  }
  return process;
}


void run_fcfs() {
  process_t *current_process = head;
  while (current_process != NULL) {
    if (current_process->state == READY) {
      int child_pid = fork();
      if (child_pid == 0) {
        // diadikasia paidiou
        execl(current_process->exec_file, current_process->exec_file, (char *)NULL);
      } else {
        //diadikasia gonea
        current_process->pid = child_pid;
        current_process->state = RUNNING;
        int status;
        waitpid(child_pid, &status, WUNTRACED);
        if (WIFSTOPPED(status)) {
          current_process->state = STOPPED;
        } else {
          current_process->state = EXITED;
        }
      }
    }
    current_process = current_process->next;
  }
}

void schedule_SJF() {
  process_t *curr = head;

  while (curr != NULL) {
    process_t *shortest = curr;
    process_t *temp = curr->next;

    while (temp != NULL) {
      if (temp->priority < shortest->priority) {
        shortest = temp;
      }
      temp = temp->next;
    }

    if (shortest != curr) {
      if (shortest->prev != NULL) {
        shortest->prev->next = shortest->next;
      }
      if (shortest->next != NULL) {
        shortest->next->prev = shortest->prev;
      }

      shortest->prev = curr->prev;
      shortest->next = curr;

      if (curr->prev != NULL) {
        curr->prev->next = shortest;
      }
      curr->prev = shortest;
    }
    curr = curr->next;
  }
}

void run_RR( process_t processes[], int n, int quantum) {
  int current_time = 0; 
  int remaining_processes = n; 
  
  while (remaining_processes) {
    for (int i = 0; i < n; i++) {
      if (processes[i].burst_time > 0) {
        if (processes[i].burst_time > quantum) {
          current_time += quantum; 
          processes[i].burst_time -= quantum; 
        } else {
          current_time += processes[i].burst_time; 
          processes[i].wait_time = current_time - processes[i].burst_time; 
          processes[i].turn_around_time = current_time; 
          processes[i].burst_time = 0; 
          remaining_processes--; 
        }
      }
    }
  }
}


int main(int argc, char *argv[]) {
  char filename[100];
  printf("Enter file name: ");
  scanf("%s", filename);

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  int pid, priority;
  char exec_file[100];
  char state_str[20];
  int count = 0;
  while (fscanf(fp, "%d %s %d %s", &pid, exec_file, &priority, state_str) != EOF && count < MAX_PROCESSES) {
    process_t *process = (process_t *)malloc(sizeof(process_t));
    process->pid = pid;
    strcpy(process->exec_file, exec_file);
    process->priority = priority;
    if (strcmp(state_str, "READY") == 0) {
      process->state = READY;
    } else if (strcmp(state_str, "RUNNING") == 0) {
      process->state = RUNNING;
    } else if (strcmp(state_str, "STOPPED") == 0) {
      process->state = STOPPED;
    } else if (strcmp(state_str, "EXITED") == 0) {
      process->state = EXITED;
    }
    insert_process(process);
    count++;
  }
  fclose(fp);

  
    process_t *process = pop_process();
    printf("pid: %d\n", process->pid);
    printf("exec_file: %s\n", process->exec_file);
    printf("priority: %d\n", process->priority);
    printf("state: ");
    switch (process->state) {
      case READY:
        printf("READY\n");
        int child_pid = fork();
        if (child_pid == 0) {
          // diadikasia paidiou
          execl(process->exec_file, process->exec_file, (char *)NULL);
        } else {
          // diadikasia gonea
          process->pid = child_pid;
          process->state = RUNNING;
          int status;
          waitpid(child_pid, &status, WUNTRACED);
          if (WIFSTOPPED(status)) {
            process->state = STOPPED;
          } else {
            process->state = EXITED;
          }
          insert_process(process);
        }
        break;
      case RUNNING:
        printf("RUNNING\n");
        break;
      case STOPPED:
        printf("STOPPED\n");
        break;
      case EXITED:
        printf("EXITED\n");
        break;
    }
    free(process);
  
   

  
    run_fcfs();
  
  
    schedule_SJF();
  
  
return 0;

}
