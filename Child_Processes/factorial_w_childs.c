 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/wait.h>
 
 int main()
{
	 int factorial = 1;
	 //Crear primer hijo

	 if(fork() == 0){

		 for(int i = 1; i <= 10; i++){
			 factorial *= i;

			 printf("\nFrom Child_A, Factorial = %d", factorial);
		 }
	 }
	 else{
		 //Padre
		 if(fork() == 0){


			 for(int i = 1; i <= 10; i++){
				 factorial *= i;
				 printf("\nFrom Child_B, Factorial = %d", factorial);
			 }
		 }
	 }

	for(int i=0;i<2;i++) // 2 hijos = 2 waits
    wait(NULL);

    return 0;
}
