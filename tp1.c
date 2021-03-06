#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "tp2.h"

//#define TRACE

//nb parfait = la somme de toute ses diviseurs except lui-meme

unsigned long min,max;

//validation du fichier
int fichierValide(FILE *fp){
	return fp && fscanf(fp,"%ld %ld",&min, &max) == 2;
}

int main(int argc, char *argv[]) {

	int num;
	int i = 1;
	int argumentC = 1;
	int argumentI = 1;
	int argumentO = 1;
	int avecO = 0;
	int avecI = 0;
	
	
	char output[100];
	char temp[100];

	unsigned long ntemp;
	
	FILE *fp = NULL;
	FILE *fw = NULL;

	//on vérifie tous les arguments
	while(i < argc){
		
		#ifdef TRACE
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
				case 'c' : printf("c\n"); break;
						
			
				case 'i' : printf("i\n"); break;
				case 'o' : printf("o\n"); break;
	
				default: exit(3); break;
			}
		}
		#endif

		//strcomp retourne 0 si egale		
		if(strcmp(argv[i],"-c") == 0 || strcmp(argv[i],"-C") == 0){
			if(argv[i+1] == NULL || argv[i+1][0] == '-' ){
				argumentC =0;
			} else if(!cpValide(argv[i+1])){
				exit(2);
			} else {
				fw = fopen("code.txt","w");	
				fprintf(fw,"%s\n",argv[i+1]);	
			}

		} else if(strcmp(argv[i],"-i") == 0 || strcmp(argv[i],"-I") == 0){
			
			avecI = 1;
			
			if(argv[i+1] == NULL){
				argumentI=0;
			} else {

				fp=fopen(argv[i+1],"r");

				if(!fichierValide(fp)){
					exit(5);
				}
			}

		} else if(strcmp(argv[i],"-o") == 0 || strcmp(argv[i],"-O") == 0){

			avecO = 1;

			if(argv[i+1]==NULL || argv[i+1][0] == '-'){
				argumentO=0;
			} else {
				strcpy(output,argv[i+1]);
				fw = fopen(output,"w");
			}
 
		} else {
			exit(3);
		}

		i+=2;
	}

	if(argc<2 || !argumentC){
		fprintf(stderr, "Usage: %s <-c CODEpermanent> [-i fichier.in] [-o fichier.out] \n", argv[0]);
		exit(0);
	} else if(!argumentI){
		exit(5);
	} else if(!intervalleValide(min,max)){
		exit(4);
	} else if(!argumentO){
		exit(6);
	} 

	if(!avecI){

		fseek (stdin, 0, SEEK_END);
		num = ftell (stdin);
		
		rewind(stdin);
			
		// < data.txt
		if(num > 0){
			
			fgets(temp,100,stdin);
			strtok(temp, "\n");

			char *r;
			char *ptr;
				
			r = strtok(temp," ");
			min = strtol(r,&ptr,10);
			
			r = strtok(NULL," "),
			max= strtol(r,&ptr,10);

		//sinon on demande input
		} else {
			printf("fichier entree: \n");

			fgets(temp,100,stdin);
			strtok(temp, "\n");
			
			fp=fopen(temp,"r");

			if(!fichierValide(fp)){
				exit(5);
			}
		}
	}	

	if(!avecO){

		fseek (stdin, 0, SEEK_END);
		num = ftell (stdin);
		
		// > p.txt
		if(num > 0){

			//pardonnez-moi 
		} else {
	
			//printf("fichier sortie:\n");
			
			//fgets(output,100,stdin);
			//strtok(output, "\n");
			
			//printf("%s\n");
			//fw = fopen(output,"w");	
		} 
	} 

	if(min > max){
		ntemp = max;
		max = min;
		min = ntemp;
	}

	for(unsigned long i = min; i<= max; i++){
		if(estParfait(i)){

			if(avecO){
				fprintf(fw,"%ld\n",i);
			} else {
				printf("%ld\n",i);
			}
		} 
	}

	fclose(fp);
	fclose(fw);

        return 0;
}
