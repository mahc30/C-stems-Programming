 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/wait.h>

 int main(int argc, char *argv[])
{
	 puts("holi");
	 pid_t h1, h2;
	 h1 = fork();
	 if(h1 == 0){
		 execv("./min", argv);
	 }
	 h2 = fork();
	 if(h2 == 0){
		 execv("./max", argv);
	 }

	 if(fork() == 0){
		 execv("./promedio", argv);
	 }

	 puts("\n");
	 wait(NULL);
	 wait(NULL);
	 wait(NULL);

	 puts("Terminado padre");
	 return 0;
}

