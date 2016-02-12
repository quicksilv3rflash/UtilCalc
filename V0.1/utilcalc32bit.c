/* UTILCALC V0.1 !
estimate the ethical utility value of the lives of entities! */
#include <stdio.h>

int main(void){
	int i = 0;
	float standard_C_of_n;
	float life_time;
	long long int user_input = 0;
	int consider_truth = 0;
	int consider_happiness = 0;
	int truth[] = {5, 5, 5};
	int happiness[] = {5, 5, 5};
	double T2s_value = 0;
	printf("Welcome to UTIL CALC V0.1! \n KNOWN BUGS: \n -Does not support cyborgs \n -Values giant neuronless blobs of cells, \n such as trees, more than humans.\n");
	printf("\n Begin to describe the structure \n you wish to ascertain the ethical value of the life of. \n Does it perceive and interact with reality?");
	printf("\n 1 = yes, 0 = no \n");
	scanf("%d", &user_input);
	if(user_input == 0){
		printf("\n Value of structure's existence:\n 0 \n unit: T2s (square thermostat seconds)\n");
		printf("[later questions irrelevant, exit program window] \n");
		scanf("%d", &user_input);
	}
	if(user_input == 1){
		printf(" Is the structure a biological entity? \n");
		printf("\n 1 = yes, 0 = no \n");
		scanf("%d", &user_input);
		if(user_input == 0){
			printf("\n Does the structure have active electrical \n or mechanical parts?");
			printf("\n 1 = yes, 0 = no \n");
			scanf("%d", &user_input);
			if(user_input == 0){
				printf("\n Value of structure's existence:\n 0 \n unit: T2s (square thermostat seconds)\n");
				printf("[later questions irrelevant, exit program window] \n");
				scanf("%d", &user_input);
			}
			if(user_input == 1){
				printf("\n How many active components does the structure possess?\n Enter an integer.\n");
				scanf("%d", &user_input);
				standard_C_of_n = ((float)user_input / 2);
				user_input = 7;

			}
		}
		if(user_input == 1){
			printf("\n Does the structure have neurons? \n 1 = yes, 0 = no \n");
			scanf("%d", &user_input);
			if(user_input == 0){
				printf("\n What is the volume of living cell(s) \n contained within the structure, in microliters? \n Enter an integer. \n");
				scanf("%d", &user_input);
				standard_C_of_n = ((float)user_input * (1500000000000000));
				user_input = 7;

			}
			if(user_input == 1){
				printf("\n Does the structure have a brain? \n 1 = yes, 0 = no \n");
				scanf("%d", &user_input);
				if(user_input == 0){
					printf("\n How many neurons does the structure have? \n Enter an integer. \n");
					scanf("%d", &user_input);
					standard_C_of_n = (((float)user_input / 86000000000) * 186000000000000000000000.0);
					user_input = 7;

				}
				if(user_input == 1){
					printf("\n Is the structure a mammal? \n 1 = yes, 0 = no \n");
					scanf("%d", &user_input);
					if(user_input == 0){
						printf("\n How many neurons are in the structure's brain? \n Enter an integer. \n");
						scanf("%d", &user_input);
						standard_C_of_n = (((float)user_input / 100000000000) * 186000000000000000000000.0);
						user_input = 7;

					}
					if(user_input == 1){
						printf("\n How many neurons are in the structure's cerebral cortex? \n Enter an integer. \n");
						scanf("%d", &user_input);
						standard_C_of_n = (((float)user_input / 21000000000) * 186000000000000000000000.0);
						user_input = 7;
				
					}
				}
			}
		}	
	}
	//now we have complexity value stored in standard_C_of_n (value is in thermostats and a flaot)
	printf("\n What is the structure's lifespan in seconds? \n Enter an integer. \n");
	scanf("%d", &user_input);
	life_time = (float)user_input;
	
	printf("\n Do you want to consider truth? \n (Most calculations do not require it.) \n 1 = yes, 0 = no \n");
	scanf("%d", &user_input);
	if(user_input == 0){
		consider_truth = 0;
	}
	if(user_input == 1){
		consider_truth = 1;
	}
	printf("\n Do you want to consider happiness? \n (Considering happiness is recommended.) \n 1 = yes, 0 = no \n");
	scanf("%d", &user_input);
	if(user_input == 0){
		consider_happiness = 0;
	}
	if(user_input == 1){
		consider_happiness = 1;
	}
	
	if(consider_truth == 1){
		printf("\n How much understanding of the universe \n (versus the maximum possible for that structure) \n did the structure have during the \n beginning third of its existence?\n");
		printf("\n The scale is whole numbers from 0 to 10, \n with 0 being no understanding, and 10 being");
		printf("\n the best understanding the structure could possibly have. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		truth[0] = (int)user_input;
		
		printf("\n How much understanding of the universe \n (versus the maximum possible for that structure) \n did the structure have during the \n middle third of its existence?\n");
		printf("\n The scale is whole numbers from 0 to 10, \n with 0 being no understanding, and 10 being");
		printf("\n the best understanding the structure could possibly have. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		truth[1] = (int)user_input;
		
		printf("\n How much understanding of the universe \n (versus the maximum possible for that structure) \n did the structure have during the \n last third of its existence?\n");
		printf("\n The scale is whole numbers from 0 to 10, \n with 0 being no understanding, and 10 being");
		printf("\n the best understanding the structure could possibly have. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		truth[2] = (int)user_input;
	}
	if(consider_happiness == 1){	
		printf("\n How enjoyable \n (from the structure's perspective) \n was the beginning third of the structure's existence?\n");
		printf("\n The scale is whole numbers from -10 to 10, \n with -10 being the worst discomfort the structure \n could feel, and 10 being");
		printf("\n the best satisfaction the structure could feel. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		happiness[0] = (int)user_input;
		
		printf("\n How enjoyable \n (from the structure's perspective) \n was the middle third of the structure's existence?\n");
		printf("\n The scale is whole numbers from -10 to 10, \n with -10 being the worst discomfort the structure \n could feel, and 10 being");
		printf("\n the best satisfaction the structure could feel. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		happiness[1] = (int)user_input;
		
		printf("\n How enjoyable \n (from the structure's perspective) \n was the last third of the structure's existence?\n");
		printf("\n The scale is whole numbers from -10 to 10, \n with -10 being the worst discomfort the structure \n could feel, and 10 being");
		printf("\n the best satisfaction the structure could feel. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		happiness[2] = (int)user_input;
	}
	T2s_value = T2s_value + (1.0/300.0)*((double)life_time)*(((double)truth[0]))*(((double)happiness[0]))*((double)standard_C_of_n)*((double)standard_C_of_n);
	T2s_value = T2s_value + (1.0/300.0)*((double)life_time)*(((double)truth[1]))*(((double)happiness[1]))*((double)standard_C_of_n)*((double)standard_C_of_n);
	T2s_value = T2s_value + (1.0/300.0)*((double)life_time)*(((double)truth[2]))*(((double)happiness[2]))*((double)standard_C_of_n)*((double)standard_C_of_n);
	printf("\n \n \n The value of the structure's life is:\n");
	printf("%4.3E", (double)T2s_value);
	printf("\n unit: T2s (square thermostat seconds)\n \n \n");
	printf("[later questions irrelevant, exit program window] \n");
	/*
	for(i=0;i<3;i++){
		printf("%d \n", truth[i]);
		printf("%d \n", happiness[i]);
	}
	*/
	scanf("%d", &user_input);	
}






