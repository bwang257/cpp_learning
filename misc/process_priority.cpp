/*
Exploration of fork, pid, and priority
*/

#include <iostream>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Priority (nice values) affects how much CPU time a process gets over time, not execution order.
The scheduler won't preempt a running process mid-slice just because a higher-priority process
becomes ready (context expensive). For guaranteed ordering, use synchronization primitives or sched_yield().
*/

int main(){
  std::cout << "Starting process: " << getpid() << "\n";
  int pid;
  if ((pid = fork()) != 0){
    std::cout << "Creating forked process with pid: " << pid << "\n";
  }
  if (pid != 0){
    setpriority(PRIO_PROCESS, 0, 19); // 0 means this process
  } else {
    setpriority(PRIO_PROCESS, 0, -5); // silently fails, default propert is 0
  }
  std::cout << "current process: " << getpid() <<  " with priority: " << getpriority(PRIO_PROCESS, getpid()) << std::endl;
  if (pid != 0){
    int status;
    std::cout << "Parent process waitng\n";
    wait(&status);
    std::cout << "ending parent process with id " << getpid() << "\n";
  }
  else {
    std::cout << "ending child process with pid " << getpid() << "\n";
  }
}