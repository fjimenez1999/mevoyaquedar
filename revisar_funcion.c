#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int es_operador(char caracter){
	int es = 0;
	if(caracter == '*' || caracter == '/' || caracter == '+' || caracter == '-' || caracter == '(' || caracter == ')'){
		es = 1;
	}//tambien revisar si es sen, cos o sqrt
	return es;
}

int es_numero(char caracter){
	int es = 0;
	if(caracter == '1' || caracter == '2' || caracter == '3' || caracter == '4' || caracter == '5' 
	|| caracter == '6' || caracter == '7' || caracter == '8' || caracter == '9' || caracter == '0'){
		es = 1;
	}
	return es;
}

int revisar_cantidad_terminos(char* funcion, int largo){ //deberia revisar que tenga 3 terminos o meno aka 2 +/- o menos
	int cantidad = 0;
	int i;
	for(i= 0; i < largo; i++){
			if(funcion[i] == '+' || funcion[i] == '-'){
				cantidad++;
			}
	}
	return cantidad+1;
}

void separar_terminos(char* funcion, int largo,char* strings[]){//separa los terminos y los mete en el arreglo de strings, probablemente no se necesite
	char copia[largo];
	strcpy(copia,funcion); //strlcopy es mejor
	char* token = strtok(copia," + - ");
	int pos = 0;
	while(token != NULL){
		strcpy(strings[pos],token);
		token = strtok(NULL, " + - ");
		pos++;
	}
}

int definir_prioridad(char operador){
	//agregar sen,cos y sqrt
	int prioridad;
	if(operador == ')'){
		prioridad = 0;
	}else if(operador == '(' ){
		prioridad = 1;
	}else if(operador == '*'){
		prioridad = 2;
	}else if(operador == '/'){
		prioridad = 3;
	}else if(operador == '+'){
		prioridad = 4;
	}else if(operador == '-')
		prioridad = 5;
}

char* substring(char *string, int posicion, int largo){
   char *pointer;
   int c;
   pointer = malloc(largo+1);
   
   for (c = 0 ; c < largo ; c++)
   {
      *(pointer+c) = *(string+posicion-1);      
      string++;  
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}
int es_numero_valido(char* funcion, int largo, int posicion){
	int i;
	bool termina =	false;
	for(i = posicion; i < largo; i++){
		if(es_numero(funcion[i]) && i == largo-1){
			termina = true;
			posicion = i;
		}else if(es_operador(funcion[i])){
			termina = true;
			posicion = i;
			break;
		}else if(es_numero(funcion[i])){
			continue;
		}else{
			break;
		}
	}
	if(termina){
		return posicion;
	}
	return -1;
}

bool revisar_funcion(char* funcion, int largo){
	//la funcion solo puede tener 3 terminos como maximo(sumas y restas) y 3 elementos por termino(e.g multiplicaciones x*x*x o asi) e.g(3*x*x + x - 2)
	int cantidad = revisar_cantidad_terminos(funcion,largo);
	bool cantidad_terminos_correcta = true;
	bool cantidad_elementos_correcto = true;

	if(cantidad > 3){
		cantidad_terminos_correcta = false;
	}
	if(cantidad_terminos_correcta){
		char** terminos;
		terminos = malloc(cantidad*sizeof(char*));
		int i;
		for(i = 0; i<cantidad; i++){
			terminos[i] = malloc(250*sizeof(char));
		}
		separar_terminos(funcion,largo,terminos);
		for(i = 0; i < cantidad; i++){
			if(revisar_cantidad_elementos(terminos[i],strlen(terminos[i]))>3){
				cantidad_elementos_correcto = false;
				break;
			}
		}	
	}

	if(cantidad_elementos_correcto){
		//revisar si está correcta la funcion(la sintaxis)
	}
}

bool revisar_sintaxis(char* funcion, int largo){
	char copia[largo];
	strcpy(copia,funcion);
	int i;
	if(largo != 1){
		for(i = 0; i < largo; i++){
			if(funcion[i] == 'x' || funcion[i] == 'y'){
				if(i != largo-1){
					if(es_operador(funcion[i+1])){
						copia[i] = '@';
						copia[i+1] = '@';
					}
				}else{
					if(es_operador(funcion[i-1])){
						copia[i] = '@';
						copia[i-1] = '@';
					}
				}
			}else if(es_numero(funcion[i])){//si el caracter es un numero
				if(i+1 < largo){
					if(es_numero(funcion[i+1])){//revisa el numero hasta encontrar el siguiente operador o el final del arreglo de caracteres
						int posicion;
						int final = es_numero_valido(funcion, largo, i);
						for(posicion = i; i < final; i++){//marcar hasta que termine el numero
							copia[i] = '@';
						}
						i = final;
					}else if(es_operador(funcion[i+1])){
						copia[i] = '@';
						copia[i+1] = '@';
					}					
				}else{
					copia[i] = '@';
				}
				
			}
		}
	}
	
}
//se debe hacer un metodo que revise los operadores de manera que a la izquierda haya un numero,x o y y a la derecha tambien


bool shuntingyard(char* funcion,char* cola[], int largo, int cantidad_elementos){
	/*char** stack;
	stack = malloc((cantidad_elementos)*sizeof(char*));
	int i;
	for(i = 0; i < cantidad_elementos; i++){
		stack[i] = malloc(250*sizeof(char));
	}*/
	int cola_cola = 0;
	for(i = 0; i < largo; i++){
		if(es_numero(funcion[i])){ //cambiar a es_numero(tokens[i])
			int final = es_numero_valido(funcion,largo,i);
			int sublargo = final-i;
			char* subs = substring(funcion,i,sublargo);
			cola[cola_cola] = subs;
			cola_cola++;
			printf("%s\n",subs);
		}else if(es_operador(funcion[i])){//cambiar a es_operador(tokens[i])

		}
	}
}


void separar_tokens(char* funcion, int largo, char* tokens[]){
	//usar para implementar sen cos y numeros de mas de un caracter
	int i;
	for(i = 0; i < largo; i++){

	}
}


//revisa en los caracteres siguientes al primer numero para ver si es un numero valido
//devuelve la posicion final del numero




int revisar_cantidad_elementos(char* termino, int largo){
	int cantidad = 0;
	int i;
	for(i= 0; i < largo; i++){
			if(termino[i] == '*' || termino[i] == '/'){
				cantidad++;
			}
	}
	return cantidad+1;
}


int cantidad_elementos_total(char* funcion, int largo){
	int cantidad = 0;
	int i;
	for(i = 0; i < largo; i++){
			if(funcion[i] == '*' || funcion[i] == '/' || funcion[i] == '+'|| funcion[i] == '-'){
				cantidad++;
			}
	}
	return cantidad+1;
}
//deberia haber otro metod que identifique sen de una variable,cos de una variable y sqrt de una variable antes de identificar estas operaciones
//antes de llamar a ambos metodos se deberia verificar que el input sea correcto, de alguna forma(usando el ejemlo de https://www.geeksforgeeks.org/c-program-detect-tokens-c-program/)
//posiciones contiene la posicion de cada operador para luego utilizarlas para hacer substrings
void id_operaciones(char* funcion, int largo,int cantidad_op, char* operaciones, int* posiciones){
//cambia el arreglo operaciones con el caracter correspondiente las operaciones entre elementos en orden,
// cantidad_op probablemente no sea necesario
	int i;
	int pos = 0;
	for(i = 0; i < largo;i++){
		if(funcion[i] == '*'){
			operaciones[pos] = '*';
			posiciones[pos] = i;
			pos++;
		}else if(funcion[i] == '/'){
			operaciones[pos] = '/';
			posiciones[pos] = i;
			pos++;
		}
	}
	for(i = 0; i < largo;i++){
		if(funcion[i] == '+'){
			operaciones[pos] = '+';
			posiciones[pos] = i;
			pos++;
		}else if(funcion[i] == '-'){
			operaciones[pos] = '-';
			posiciones[pos] = i;
			pos++;
		}
	}
}


void separar_elementos(char* strings, int largo){ // probablemente no sea necesario separar los elementos de cada termino
	//
}
int main(){
	char str[] = "5795 - 17 + 11";
	int cantidad_elementos = cantidad_elementos_total(str,strlen(str));
	//ubicar memoria
	char** cola;
	cola = malloc(cantidad_elementos*sizeof(char*));
	int i;
	for(i = 0; i<cantidad_elementos; i++){
		cola[i] = malloc(250*sizeof(char));
	}
	
	shuntingyard(str,cola,strlen(str),cantidad_elementos);
	/*for(i = 0; i < cantidad_elementos; i++){
		printf("%s\n",cola[i]);
	}*
	/*separar_terminos(str,12,terminos);
	for(i = 0; i<cantidad; i++){
		printf("length: %d, ",strlen(terminos[i]));
		printf("%s\n",terminos[i]);
	}*/
  return 0;
}