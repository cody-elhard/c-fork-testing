#include <stdio.h>
// Import the fork function from the unistd.h header file.
#include <unistd.h>
// Import the wait function from the unistd.h header file.
#include <sys/wait.h>

// To Run:
// gcc forkAndSum.c -o forkAndSum && ./forkAndSum

// This program creates 4 forks and sums the numbers 1-1000.
// The parent process will wait for all the children to finish before printing the sum.

int pipefd[2];

int main() {
  // Create the pipe.
  pipe(pipefd);

  int i;
  int pid;

  for (i = 0; i < 4; i++) {
    pid = fork();
    if (pid == 0) {
      // Child process
      int childSum = 100;
      printf("Child %d: %d\n", i, childSum);
      // Write 100 to the pipe.
      write(pipefd[1], &childSum, sizeof(childSum));
      return 0;
    }
  }

  // Parent process
  int status;

  for (i = 0; i < 4; i++) {
    wait(&status);
    printf("Process finished with status: %d\n", status);
  }

  int sumFromPipe;
  // Read 100 from the pipe.
  read(pipefd[0], &sumFromPipe, sizeof(sumFromPipe));
  
  printf("Sum: %d\n", sumFromPipe);
  return 0;
}

