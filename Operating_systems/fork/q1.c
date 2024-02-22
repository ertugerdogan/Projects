#include <stdio.h> // printf
#include <unistd.h> // fork
#include <stdlib.h> // exit
#include <sys/wait.h> // wait

// This function exists to create exactly 1 left children from the main process.
void create_one_child_processes(int m) {
    if (m == 0) {
        return;
    }

    int pid;
    if ((pid = fork()) == -1) { // Error
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        printf(" Left Child process with PID %d, Parent Process ID %d\n", getpid(), getppid());
        create_one_child_processes(m - 1);
        exit(0);
    } else { // Parent process
        int status;
        wait(&status); // Wait for child process to terminate
    }
}

void functionb(int n, int m) {
    int i = 0;
    int pid, prev_pid = 0;
    while (i < n) {
        if(i == 0){
            create_one_child_processes(m);
            prev_pid = getpid();
        } else {
            if ((pid = fork()) == -1) { // Error
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) { // Child process
                printf(" Right Child process with PID %d, Parent Process ID %d\n", getpid(), prev_pid);
                create_one_child_processes(m);
                exit(0);
            } else { // Parent process
                int status;
                wait(&status); // Wait for child process to terminate
                prev_pid = pid;
            }
        }
        i++;
    }
}

int main() {
    int N;
    printf("Enter N value:  \n");
    scanf("%d", &N);
    
    
    printf("Parent process with PID %d\n", getpid());
    functionb(N+1, 1);
    return 0;
}
