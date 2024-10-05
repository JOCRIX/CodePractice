//Callback function type deklaration
typedef int(*CallbackFunction)(int); //Definition af callback type.
/*Det skal læses som "pointer til function, som tager en integer som argument 
* og returnerer en integer.
*/

int SomeFunction(int number);
int performOperation(int value, CallbackFunction callback);

int c = 0;

void setup() {
  Serial.begin(115200);
;
}

void loop() {
  delay(1000);
  c = performOperation(3, SomeFunction);
  Serial.println(c);
}



int SomeFunction(int number){
  //Serial.println(number);
return number * 2;
}

/*
performOperation kan tage en callbackfunction som input og den kaldes inde i funktionen.
*/
int performOperation(int value, CallbackFunction callback){ 
  int a = 0;
  if(callback != NULL){
    a = callback(value);
  }
  //Serial.println(a);
  int b = a + value;

  return b;
}
