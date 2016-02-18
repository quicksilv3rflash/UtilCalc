/* UTILCALC V1.0 Finishes the backbone algorithm. One more modifier is added to compensate for overvaluing
of entities without neurons. 7500000000 human lives seems like too much value to assign to the life of a redwood,
which is the result of utilcalc v0.2; correcting this will be the final modification to the core algorithm, so this
is now utilcalc V1.0. A bonus is given for neurons, based on data transmission speed vs non-innervated transmission
speed (The numbers for human data transmission speed are for a myelinated axon, the numbers for non-innervated
transmission speed are taken from an experiment with tomato plants talking to each other about an aphid attack 
through a fungal (mycelial) network). The primary ethical value in neurons is assumed to be their speed -- that is,
entities which process information more quickly live more life in the same amount of time, and are assumed
to have proportionally higher complexity values. To assign this bonus fairly, synthetic neural networks (on chips, etc)
are given a further bonus above humans proportional to their speed in a manner analogous to the way in which humans
are given a speed bonus over things such as trees.

The paper "How rapid is aphid-induced signal transfer between plants via common mycelial networks?" (Zdenka Babikova et. al.)
begins to determine the communications speed of plant-mycelial networks, finding the signal can traverse 15 cm in 24 hours, 
which is 2 micrometers / second, roughly.

Human axon conduction speed is approximately micrometers / second and a human neuron takes xxx seconds to respond to a signal
at one of its input synapses.

UTILCALC V0.2. Switches to double precision floating point and uses a new input method (scientific notation)
for lifetime, neuron number, volume, et cetera. V0.2 should elminate the bug in V0.1 which caused the value
of Globicephala melas to be erroneously underestimated vs H. sapiens
(G. melas should be about 4.3x more valuable than H. sapiens ignoring lifespan differences)

estimate the ethical utility value of the lives of entities! 

good in the universe is assumed to be equal to the following function:
	SUM FROM n = 0 to n = (total # of perceptive structures in existence) of
		INTEGRAL dt FROM Entity n BIRTH TIME to Entity n DEATH TIME of function
			TRUTH(n,t)*HAPPINESS(n,t)*(COMPLEXITY(n,t))^2

Where 0 <= TRUTH <= 1 and -1 <= HAPPINESS <= 1, unitless normalized functions
In UTIL CALC V0.2, these are taken from user input directly or set to 0.5 (by default)

COMPLEXITY is measured in THERMOSTATS. The THERMOSTAT is the unit of complexity which represents the
full - duplex link between a OLD-STYLE BIMETALLIC COIL MERCURY TILT-SWITCH THERMOSTAT which DIRECTLY ACTUATES a ROOM HEATER.
This system observes the universe and attempts to keep it in a particular configuration. The ethical value of the system
is assumed to exist in the LINKS BETWEEN ACTIVE NODES, such that it increases on the order of (#of_nodes)^2.

We can use this as a hack unit for complexity in the following manner: we assume different conversion methods depending on the
type of perceptive structure we're analyzing.

Machinery + electronics:
THERMOSTATS = #active_parts / 2

Non-innervated biological entities:
THERMOSTATS = #proteins / 2
(proteins are the active parts of life!)

Innervated biological entities without central nervous systems:
THERMOSTATS = (#proteins_in_average_human / 2)*(#neurons_in_entity / #neurons_in_average_human)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)

Nonmammals with central nervous systems, also, synthetic neural networks implemented physically or in simulations,
which will be considered "floating brains" for the purposes of this ethical system:
THERMOSTATS = (#proteins_in_average_human / 2)*(#neurons_in_bio_entity_brain / #neurons_in_average_human_brain)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)
-OR-
(because most synthetic neurons -- used in things like multilayer perceptrons -- are much simpler than biological neurons)
THERMOSTATS = (#proteins_in_average_human / 2)*(#of_input_synapses_per_synthetic_neuron / #of_input_synapses_in_average_human_neuron)*(#neurons_in_entity_neural_network / #neurons_in_average_human_brain)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)*(response_time_of_human_neuron / response_time_of_synthetic_neuron) 

Mammals:
THERMOSTATS = (#proteins_in_average_human / 2)*(#neurons_in_entity_cerebral_cortex / #neurons_in_average_human_cerebral_cortex)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)

The most glaring bug with this system as far as I can tell is that non-innervated biological things which are physically larger
and live longer than humans are ranked more highly. In UTIL CALC V0.2, redwoods are the most valuable entity by far! Some sort of adjustment
to raw protein count is probably the best way to patch that.

The output unit of UTIL CALC V0.2 is the SQUARE THERMOSTAT SECOND, or T2s.
This unit is the amount of global utility generated by a Thermostat-heater-room system appearing from no-where (poof!),
existing for 1 second in conditions which satisfy the setting of the thermostat without requiring it to actuate the heater,
and disappearing after 1 second (poof again!).
*/

#include <stdio.h>
#include <math.h>

int main(void){
	int consider_truth = 0; //truth defaults to 0.5
	int consider_happiness = 0; //happiness defaults to 0.5
	
	int user_input = 0; //variable for parsing integer user input
	double float_user_input = 0; //variable for parsing float user input
	double mantissa = 0; //for representing base 10 scientific notation
	double exponent = 0; //for representing base 10 scientific notation

	double response_time_of_synthetic_neuron = 0.1; //this number must be given in milliseconds!
	double response_time_of_human_neuron = (double)1.5 * pow(10.0, 2.0);// 150 milliseconds time constant of recovery "High Bandwidth Synaptic Communication and Frequency Tracking in Human Neocortex" (Guilherme Testa-Silva et. al.)
	double conduction_speed_of_myelinated_axon = (double)1.2 * pow(10.0, 8.0); //120000000 micrometers per second! (max speed for myelinated axon neural signal propagation)
	double conduction_speed_of_mycelial_network = (double)2.0; //2 micrometers per second! (via an experiment with tomato plants and aphids)
	double number_of_proteins_in_human = (double)7.44 * pow(10.0, 22.0);
	//the human cell line HeLa has about 2.0 * 10^9 proteins per cell (Nagaraj et al.)
	//the human body has about 3.72 * 10^13 cells
	//so the number of proteins per human would be about 7.44 * 10^22
	double number_of_neurons_in_human = pow(10.0, 12.0);//about 1 * 10^12 neurons in a whole human
	double number_of_neurons_in_human_brain = pow(10.0, 11.0); //about 100 billion neurons in a human brain
	double number_of_neurons_in_human_cerebral_cortex = (double)2.0 * pow(10.0, 10.0); //about 20 billion neurons in a human cerebral cortex
	
	double synthetic_neural_network_correction_factor = 0; //(#of_input_synapses_per_synthetic_neuron / #of_input_synapses_in_average_human_neuron)
	double standard_C_of_n = 0; //in THERMOSTATS
	double life_time = 0;	//in seconds
	double truth[] = {0.5, 0.5, 0.5}; //unitless
	double happiness[] = {0.5, 0.5, 0.5}; //unitless
	double T2s_value = 0; //the final output, units: T^2 s
	
	//your typical welcome message
	printf("Welcome to UTIL CALC V0.2! \n KNOWN BUGS: \n -Does not support cyborgs \n \n");
	printf("\n Begin to describe the structure \n you wish to ascertain the ethical value of the life of. \n Does it perceive and interact with reality?");
	printf("\n 1 = yes, 0 = no \n");
	scanf("%d", &user_input);
	if(user_input == 0){ //we don't consider nonperceptive structures ethically valuable
		printf("\n Value of structure's existence:\n 0 \n unit: T2s (square thermostat seconds)\n");
		printf("[later questions irrelevant, exit program window] \n");
		scanf("%d", &user_input);
	}
	if(user_input == 1){ //it perceives! let's get our special case out of the way first
		printf("\n Is the structure a synthetic neural network, \n such as a multilayer perceptron? \n");
		printf("\n 1 = yes, 0 = no \n");
		scanf("%d", &user_input);
		if(user_input == 1){	//it's a special case because we have a special correction factor!		
			printf("\n How many input synapses does each synthetic neuron have? \n");
			printf("\n We will use scientific notation in the following form:\n");
			printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
			scanf("%lf", &float_user_input);
			mantissa = float_user_input;
			printf("\n B=");
			scanf("%lf", &float_user_input);
			exponent = float_user_input;
			//"each human neuron has on average 7,000 synaptic connections to other neurons"
			synthetic_neural_network_correction_factor = ((mantissa * pow(10.0, exponent))/7000.0);
			
			printf("\n What is the response time of an individual synthetic neuron in milliseconds? \n");
			printf("\n We will use scientific notation in the following form:\n");
			printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n -150<= B <= 150 \n \n A=");
			scanf("%lf", &float_user_input);
			mantissa = float_user_input;
			printf("\n B=");
			scanf("%lf", &float_user_input);
			exponent = float_user_input;
			response_time_of_synthetic_neuron = (mantissa * pow(10.0, exponent)); //synthetic neuron response time in milliseconds (a human neuron responds/recovers in about 150 milliseconds)
			printf("\n How many synthetic neurons does the structure have? \n");
			printf("\n We will use scientific notation in the following form:\n");
			printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
			scanf("%lf", &float_user_input);
			mantissa = float_user_input;
			printf("\n B=");
			scanf("%lf", &float_user_input);
			exponent = float_user_input;
			//THERMOSTATS = (#proteins_in_average_human / 2)*(#of_input_synapses_per_synthetic_neuron / #of_input_synapses_in_average_human_neuron)*(#neurons_in_entity_neural_network / #neurons_in_average_human_brain)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)*(response_time_of_human_neuron / response_time_of_synthetic_neuron)
			standard_C_of_n = (number_of_proteins_in_human / 2.0)*(synthetic_neural_network_correction_factor)*((mantissa * pow(10.0, exponent))/number_of_neurons_in_human_brain)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)*(response_time_of_human_neuron / response_time_of_synthetic_neuron);
			user_input = 7;
		}
		if(user_input == 0){		
			printf(" Is the structure a biological entity? \n"); // we handle those differently.
			printf("\n 1 = yes, 0 = no \n");
			scanf("%d", &user_input);
			if(user_input == 0){
				printf("\n Does the structure have active electrical \n or mechanical parts?"); // no active parts, no ethical value!
				printf("\n 1 = yes, 0 = no \n");
				scanf("%d", &user_input);
				if(user_input == 0){
					printf("\n Value of structure's existence:\n 0 \n unit: T2s (square thermostat seconds)\n"); // no active parts, no ethical value!
					printf("[later questions irrelevant, exit program window] \n");
					scanf("%d", &user_input);
				}
				if(user_input == 1){
					printf("\n How many active components does the structure possess?\n");
					printf("\n We will use scientific notation in the following form:\n");
					printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
					scanf("%lf", &float_user_input);
					mantissa = float_user_input;
					printf("\n B=");
					scanf("%lf", &float_user_input);
					exponent = float_user_input;
					standard_C_of_n = ((mantissa * pow(10.0, exponent)) / 2);
					user_input = 7;
					//Machinery + electronics:
					//THERMOSTATS = #active_parts / 2
				}
			}
			if(user_input == 1){
				printf("\n Does the structure have neurons? \n 1 = yes, 0 = no \n");
				scanf("%d", &user_input);
				if(user_input == 0){
					printf("\n What is the volume of living cell(s) \n contained within the structure, in microliters? \n");
					printf("\n We will use scientific notation in the following form:\n");
					printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
					scanf("%lf", &float_user_input);
					mantissa = float_user_input;
					printf("\n B=");
					scanf("%lf", &float_user_input);
					exponent = float_user_input;
					standard_C_of_n = (((mantissa * pow(10.0, exponent)) * (3.0 * pow(10.0, 15))) / 2); // 3 * 10^15 proteins per microliter!
					user_input = 7;
					//"we estimate a range of 2–4 million proteins per cubic micron (i.e. 1?fL) in bacteria, yeast, and mammalian cells"
					// 3 million proteins per femtoliter!					
					
					//Non-innervated biological entities:
					//THERMOSTATS = #proteins / 2
					//(proteins are the active parts of life!)	
				}
				if(user_input == 1){
					printf("\n Does the structure have a brain? \n 1 = yes, 0 = no \n");
					scanf("%d", &user_input);
					if(user_input == 0){
						printf("\n How many neurons does the structure have? \n"); 
						//brainless but innervated things are compared with the total human number of neurons
						
						//Innervated biological entities without central nervous systems:
						//THERMOSTATS = (#proteins_in_average_human / 2)*(#neurons_in_entity / #neurons_in_average_human)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)
						printf("\n We will use scientific notation in the following form:\n");
						printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
						scanf("%lf", &float_user_input);
						mantissa = float_user_input;
						printf("\n B=");
						scanf("%lf", &float_user_input);
						exponent = float_user_input;
						standard_C_of_n = (number_of_proteins_in_human / 2.0)*((mantissa * pow(10.0, exponent))/ number_of_neurons_in_human)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network);
						user_input = 7;
	
					}
					if(user_input == 1){
						printf("\n Is the structure a mammal? \n 1 = yes, 0 = no \n");
						scanf("%d", &user_input);
						if(user_input == 0){ //nonmammals with brains!
							printf("\n How many neurons are in the structure's brain? \n");
							//Nonmammals with central nervous systems
							//THERMOSTATS = (#proteins_in_average_human / 2)*(#neurons_in_bio_entity_brain / #neurons_in_average_human_brain)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)
							printf("\n We will use scientific notation in the following form:\n");
							printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
							scanf("%lf", &float_user_input);
							mantissa = float_user_input;
							printf("\n B=");
							scanf("%lf", &float_user_input);
							exponent = float_user_input;
							standard_C_of_n = (number_of_proteins_in_human / 2.0)*((mantissa * pow(10.0, exponent))/ number_of_neurons_in_human_brain)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network);
							user_input = 7;	
						}
						if(user_input == 1){
							printf("\n How many neurons are in the structure's cerebral cortex? \n");
							//Mammals:
							//THERMOSTATS = (#proteins_in_average_human / 2)*(#neurons_in_entity_cerebral_cortex / #neurons_in_average_human_cerebral_cortex)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network)
							printf("\n We will use scientific notation in the following form:\n");
							printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
							scanf("%lf", &float_user_input);
							mantissa = float_user_input;
							printf("\n B=");
							scanf("%lf", &float_user_input);
							exponent = float_user_input;
							standard_C_of_n = (number_of_proteins_in_human / 2.0)*((mantissa * pow(10.0, exponent))/ number_of_neurons_in_human_cerebral_cortex)*(conduction_speed_of_myelinated_axon / conduction_speed_of_mycelial_network);
							user_input = 7;	
					
						}
					}
				}
			}	
		}
	}
	//now we have complexity value stored in standard_C_of_n (value is in thermostats and is a double precision flaot)
	printf("\n What is the structure's lifespan in seconds? \n");
	printf("\n We will use scientific notation in the following form:\n");
	printf("\n A * (10 ^ B)\n 1.0 <= A <= 9.9 \n 0   <= B <= 150 \n \n A=");
	scanf("%lf", &float_user_input);
	mantissa = float_user_input;
	printf("\n B=");
	scanf("%lf", &float_user_input);
	exponent = float_user_input;
	life_time = (mantissa * pow(10.0, exponent));
	
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
		truth[0] = ((double)user_input / 10.0);
		
		printf("\n How much understanding of the universe \n (versus the maximum possible for that structure) \n did the structure have during the \n middle third of its existence?\n");
		printf("\n The scale is whole numbers from 0 to 10, \n with 0 being no understanding, and 10 being");
		printf("\n the best understanding the structure could possibly have. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		truth[1] = ((double)user_input / 10.0);
		
		printf("\n How much understanding of the universe \n (versus the maximum possible for that structure) \n did the structure have during the \n last third of its existence?\n");
		printf("\n The scale is whole numbers from 0 to 10, \n with 0 being no understanding, and 10 being");
		printf("\n the best understanding the structure could possibly have. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		truth[2] = ((double)user_input / 10.0);
	}
	if(consider_happiness == 1){	
		printf("\n How enjoyable \n (from the structure's perspective) \n was the beginning third of the structure's existence?\n");
		printf("\n The scale is whole numbers from -10 to 10, \n with -10 being the worst discomfort the structure \n could feel, and 10 being");
		printf("\n the best satisfaction the structure could feel. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		happiness[0] = ((double)user_input / 10.0);
		
		printf("\n How enjoyable \n (from the structure's perspective) \n was the middle third of the structure's existence?\n");
		printf("\n The scale is whole numbers from -10 to 10, \n with -10 being the worst discomfort the structure \n could feel, and 10 being");
		printf("\n the best satisfaction the structure could feel. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		happiness[1] = ((double)user_input / 10.0);
		
		printf("\n How enjoyable \n (from the structure's perspective) \n was the last third of the structure's existence?\n");
		printf("\n The scale is whole numbers from -10 to 10, \n with -10 being the worst discomfort the structure \n could feel, and 10 being");
		printf("\n the best satisfaction the structure could feel. \n Typical structures will be between 2 and 7. \n");
		scanf("%d", &user_input);
		happiness[2] = ((double)user_input / 10.0);
	}
	T2s_value = T2s_value + (1.0/3.0)*(life_time)*(truth[0])*(happiness[0])*(standard_C_of_n)*(standard_C_of_n);
	T2s_value = T2s_value + (1.0/3.0)*(life_time)*(truth[1])*(happiness[1])*(standard_C_of_n)*(standard_C_of_n);
	T2s_value = T2s_value + (1.0/3.0)*(life_time)*(truth[2])*(happiness[2])*(standard_C_of_n)*(standard_C_of_n);
	printf("\n \n \n The value of the structure's life is:\n");
	printf("%2.1E", (double)T2s_value);
	printf("\n unit: T2s (square thermostat seconds)\n \n \n");
	printf("[later questions irrelevant, exit program window] \n");
	scanf("%d", &user_input);	
}






