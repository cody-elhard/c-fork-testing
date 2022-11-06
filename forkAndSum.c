#include <stdio.h>
// Import the fork function from the unistd.h header file.
#include <unistd.h>
// Import the wait function from the unistd.h header file.
#include <sys/wait.h>

// To Run:
// gcc forkAndSum.c -o forkAndSum && ./forkAndSum

// This program creates 4 forks and sums the numbers 1-1000.
// The parent process will wait for all the children to finish before printing the sum.

// Declare the global variable sum.

int main() {
  // Create a pipe to hold the sum.
  int pipefd[2];
  // Create the pipe.
  pipe(pipefd);
  // read end of the pipe
  int readEnd = pipefd[0];
  int writeEnd = pipefd[1];

  int sum = 0;
    int i;
    int pid;

    for (i = 0; i < 4; i++) {
      pid = fork();
      if (pid == 0) {
        // Child process
        int childSum = 100;
        printf("Child %d: %d\n", i, childSum);
        // Set the write end of the pipe to the childSum.
        write(pipefd[1], &childSum, sizeof(childSum));
        return 0;
      }
    }

  // Parent process
  int status;

  for (i = 0; i < 4; i++) {
    printf("Process finished with status: %d\n", status);
    wait(&status);
  }

  // Read the sum from the pipe.
  int mySum = read(pipefd[0], &sum, sizeof(sum));
  printf("Sum: %d\n", mySum);
  return 0;
}

