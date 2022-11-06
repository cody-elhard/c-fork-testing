#include <stdio.h>
// Import the fork function from the unistd.h header file.
#include <unistd.h>
// Import the wait function from the unistd.h header file.
#include <sys/wait.h>

// To Run:
// gcc forkAndSum.c -o forkAndSum && ./forkAndSum

// This program creates 4 forks and sums the numbers 1-1000.
// The parent process will wait for all the children to finish before printing the sum.


// Create an array of 4 pipes
int pipefd[4][2];

int getNumber() {
  int userInput;
  printf("Enter the number of pipes you want to create: ");
  scanf("%d", &userInput);
  return userInput;
}

int main() {
  int numPipes = getNumber();
  if (numPipes > 4) {
    // Raise an error
    printf("You can only create 4 pipes at a time.\n");
    return 1;
  }

  // Create the pipe.
  for (int i = 0; i < 4; i++) {
    pipe(pipefd[i]);
  }

  int i;
  int pid;

  for (i = 0; i < numPipes; i++) {
    pid = fork();
    if (pid == 0) {
      // Child process
      int childSum = 100;
      printf("Child %d: %d\n", i, childSum);
      // Write 100 to the pipe.
      write(pipefd[i][1], &childSum, sizeof(childSum));
      return 0;
    }
  }

  // Parent process
  int status;

  for (i = 0; i < numPipes; i++) {
    wait(&status);
    printf("Process finished with status: %d\n", status);
  }

  int totalSum = 0;
  int sumFromPipe;
  // Read 100 from the pipe.
  // For each child process, read the sum from the pipe and add it to the total sum.
  for (i = 0; i < numPipes; i++) {
    read(pipefd[i][0], &sumFromPipe, sizeof(sumFromPipe));
    totalSum += sumFromPipe;
  }

  printf("Sum: %d\n", totalSum);
  return 0;
}

