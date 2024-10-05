 /*Husk at tjekke om callback function pointers _IKKE_ er en null pointer.
  Programmet kan crashe, hvis vi ikke gør det. Vi får adgang (dereferenced)
  til memory vi ikke skulle -> segmentation fault.. Eller vi får undefined opførsel i bedste fald-> svært at debugge!!
 */

/*Struct til at indeholde callback funktioner.*/
typedef struct {
  int (*funcA)(int);
  int (*funcB)(int);
}callbacks;

struct{
  void(*programDestroyer)(int);
}uninitializedCallbacks;

callbacks globalCallbacks; 

int k = 0, n = 0;

int SumItUp(callbacks *CB, int a, int b){
  int x = 0;
  
  if((CB->funcA == NULL) && (CB->funcB == NULL)){ /*Check at func pointers er defineret*/
    return -1;
  }else{
    x += CB->funcA(a);
    //Serial.println(x);
    x += CB->funcB(b);
    //Serial.println(x);
  }
  return x;
}

int EnFunktion(int i){
  return i*2;
}
int EnAndenFunktion(int i){
  return i + 5;
}
int EnTredjeFunktion(int i, int j){
  return i*j;
}

void setup() {
  Serial.begin(115200);
  
  /*Load function pointers ind i callbacks struct*/
  globalCallbacks.funcA = EnFunktion;
  globalCallbacks.funcB = EnAndenFunktion;
}

void loop() {
  k = SumItUp(&globalCallbacks, 1,2); //Overfør og brug callback funktioner i funktionskald
  Serial.print("Test af SumItUp: ");
  Serial.println(k);
  delay(1000);

  //Kald callback funktion direkte fra struct..
  Serial.print("Test af call fra struct:");
  n = globalCallbacks.funcA(1); /*Husk at tjekke om .funcA _IKKE_ er en null pointer.
  Programmet kan crashe, hvis vi ikke gør det. Vi får adgang (dereferenced)
  til memory vi ikke skulle -> segmentation fault.. Eller vi får undefined opførsel i bedste fald-> svært at debugge!!*/
  Serial.println(n);

  //Shuffle funktionerne så operationerne laves i en anden rækkefølge
  globalCallbacks.funcA = EnAndenFunktion;
  globalCallbacks.funcB = EnFunktion;

  //Test af program efter at en null function pointer er blevet dereferenced
  //uninitializedCallbacks.programDestroyer(255);
  //Serial.prints er messed up efter det her :)
}
