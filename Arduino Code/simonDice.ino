int orden[3]; //Orden de los numeros generados aleatorios
int respuestas[3]; //Orden de los numeros presionados por el usuario
bool inicio = true; //Indica que se ejecuta espera para iniciar un nuevo juego
bool seccionAleatorio = true; //Indica que se debe ejecutar la parte de generar los numeros aleatorios
bool espera = false; //Indica que se debe ejecutar la seccion de espera
bool ejecucionUsuario = false; //Indica que se debe ejecutar la parte del usuario
bool validacionRespuestas = false;//Indica que se debe ejecutar la seccion para verificar si las respuestas fueron correctas
int victorias = 0; //Indica la cantidad de victorias del usuario

int pinRojoAleatorio = 13;//Pin para led Rojo donde se muestran los valores aleatorios
int pinAmarilloAleatorio = 12;//Pin para led Amarillo donde se muestran los valores aleatorios
int pinVerdeAleatorio = 11;//Pin para led Verde donde se muestran los valores aleatorios
//Los pines aleatorios deben ser consecutivos empezando con el VERDE como el menor y el ROJO con el mayor
int pinRojoResp = 10;//Pin para led Rojo donde se ingresan las respuestas
int pinAmarilloResp = 9;//Pin para led Amarillo donde se ingresan las respuestas
int pinVerdeResp = 8;//Pin para led Verde donde se ingresan las respuestas

int pulsadorRojo = 7;//Pin para el pulsador para que usuario elija el led ROJO
int pulsadorAmarillo = 6;//Pin para el pulsador para que usuario elija el led AMARILLO
int pulsadorVerde = 5;//Pin para el pulsador para que usuario elija el led VERDE

/*
   El 7 Segmentos utilizado es de ANODO COMUN
   Si el que es usado es de Catodo comun cambiar HIGH por LOW(En funciones inferiores de impresion de numeros)
   y hacer el cambio en las conexiones necesarias
*/
int SuperiorHorizontal = 24;//Pin de la Linea SUPERIOR HORIZONTAL
int MedioHorizontal = 28;//Pin de la Linea MEDIO HORIZONTAL
int InferiorHorizontal = 50;//Pin de la Linea INFERIOR HORIZONTAL
int IzqSuperiorVertical = 26;//Pin de la Linea IZQUIERDA SUPERIOR VERTICAL
int IzqInferiorVertical = 52;//Pin de la Linea IZQUIERDA INFERIOR VERTICAL
int DerSuperiorVertical = 22;//Pin de la Linea DERECHA SUPERIOR VERTICAL
int DerInferiorVertical = 51;//Pin de la Linea DERECHA INFERIOR VERTICAL
int Punto = 53;//Pin del PUNTO


void setup() {
  pinMode(pinRojoAleatorio, OUTPUT); //Rojo Aleatorio
  pinMode(pinAmarilloAleatorio, OUTPUT);//Amarillo Aleatorio
  pinMode(pinVerdeAleatorio, OUTPUT);//Verde Aleatorio
  //Los pines aleatorios deben ser consecutivos empezando con el VERDE como el menor y el ROJO con el mayor
  pinMode(pinRojoResp, OUTPUT); //Rojo Respuesta
  pinMode(pinAmarilloResp, OUTPUT); //Amarillo Respuesta
  pinMode(pinVerdeResp, OUTPUT); //Verde Respuesta


  pinMode(pulsadorRojo, INPUT);//Pulsador Rojo
  pinMode(pulsadorAmarillo, INPUT);//Pulsador Amarillo
  pinMode(pulsadorVerde, INPUT);//Pulsador Verde

  pinMode(InferiorHorizontal, OUTPUT);
  pinMode(DerInferiorVertical, OUTPUT);
  pinMode(IzqInferiorVertical, OUTPUT);
  pinMode(Punto, OUTPUT);
  pinMode(DerSuperiorVertical, OUTPUT);
  pinMode(SuperiorHorizontal, OUTPUT);
  pinMode(IzqSuperiorVertical, OUTPUT);
  pinMode(MedioHorizontal, OUTPUT);
}

void SeccionAleatorio() {
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(pinVerdeAleatorio, LOW);
    digitalWrite(pinAmarilloAleatorio, LOW);
    digitalWrite(pinRojoAleatorio, LOW);
    delay(2000);
    randomSeed(millis());
    int aleatorio = random(0, 60);
    orden[i] = aleatorio;
    if (aleatorio >= 0 && aleatorio < 20)//Condicion para encender el led verde PIN 11
    {
      digitalWrite(pinVerdeAleatorio, HIGH);
      delay(500);
      digitalWrite(pinVerdeAleatorio, LOW);
    }
    if (aleatorio >= 20 && aleatorio < 40)//Condicion para encender el led amarillo PIN 12
    {
      digitalWrite(pinAmarilloAleatorio, HIGH);
      delay(500);
      digitalWrite(pinAmarilloAleatorio, LOW);
    }
    if (aleatorio >= 40 && aleatorio <= 60)//Condicion para encender el led ROJO PIN 13
    {
      digitalWrite(pinRojoAleatorio, HIGH);
      delay(500);
      digitalWrite(pinRojoAleatorio, LOW);
    }
  }
  digitalWrite(pinVerdeAleatorio, LOW);
  digitalWrite(pinAmarilloAleatorio, LOW);
  digitalWrite(pinRojoAleatorio, LOW);
  seccionAleatorio = false;
  espera = true;
}

void Espera() {
  for (int i = 10 ; i >= 0 ; i--)
  {
    digitalWrite(pinVerdeResp, HIGH);
    digitalWrite(pinAmarilloResp, HIGH);
    digitalWrite(pinRojoResp, HIGH);
    delay(i * 100);
    digitalWrite(pinVerdeResp, LOW);
    digitalWrite(pinAmarilloResp, LOW);
    digitalWrite(pinRojoResp, LOW);
    delay(i * 100);
  }
  espera = false;
  ejecucionUsuario = true;
}

int EjecucionUsuario(int pin)
{
  int lecturaRojo = 0;
  int lecturaAmarillo = 0;
  int lecturaVerde = 0;
  do {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
    lecturaRojo = digitalRead(pulsadorRojo);
    lecturaAmarillo = digitalRead(pulsadorAmarillo);
    lecturaVerde = digitalRead(pulsadorVerde);
    delay(100);
    if (lecturaRojo == HIGH)
    {
      digitalWrite(pinRojoResp, HIGH);
      delay(300);
      digitalWrite(pinRojoResp, LOW);
      delay(100);
      return 50;
    }
    if (lecturaAmarillo == HIGH)
    {
      digitalWrite(pinAmarilloResp, HIGH);
      delay(300);
      digitalWrite(pinAmarilloResp, LOW);
      delay(100);
      return 30;
    }
    if (lecturaVerde == HIGH)
    {
      digitalWrite(pinVerdeResp, HIGH);
      delay(300);
      digitalWrite(pinVerdeResp, LOW);
      delay(100);
      return 10;
    }
  }
  while (true);
}

bool validarRespuestas()
{
  bool correcto;
  for (int i = 0; i < 3; i++)
  {
    correcto = false;
    if (orden[i] >= 0 && orden[i] < 20 && respuestas[i] >= 0 && respuestas[i] < 20)
      correcto = true;
    if (orden[i] >= 20 && orden[i] < 40 && respuestas[i] >= 20 && respuestas[i] < 40)
      correcto = true;
    if (orden[i] >= 40 && orden[i] <= 60 && respuestas[i] >= 40 && respuestas[i] <= 60)
      correcto = true;
    if (!correcto)
      return false;
  }
  return true;
}
/*
   El 7 Segmentos utilizado es de ANODO COMUN
   Si el que es usado es de Catodo comun cambiar HIGH por LOW(En la implementacion de las funciones abajo) y hacer el cambio en las conexiones necesarias
*/
void ImprimirVictorias()
{
  switch (victorias)
  {
    case 0:
      //Funcion para imprimir en un lcd de 7 segmentos el numero 6 0 9
      //Este numero requiere que se apaguen 1 LED (El ultimo (1) parametro)
      numSeis_Cero_Nueve(DerSuperiorVertical, SuperiorHorizontal, IzqSuperiorVertical, InferiorHorizontal, DerInferiorVertical, IzqInferiorVertical, MedioHorizontal); //
      break;
    case 1:
      //Funcion para imprimir en un lcd de 7 segmentos el numero 1
      //Este numero requiere que se apaguen 5 LEDS (Los ultimos 5 parametros)
      numUno(DerSuperiorVertical, DerInferiorVertical, SuperiorHorizontal, IzqSuperiorVertical, MedioHorizontal, InferiorHorizontal, IzqInferiorVertical); //
      break;
    case 2:
      //Funcion para imprimir en un lcd de 7 segmentos los numeros 2 3 5
      //Este numero requiere que se apaguen 2 LEDS (Los ultimos 2 parametros)
      numDos_Tres_Cinco(DerSuperiorVertical, SuperiorHorizontal, MedioHorizontal, InferiorHorizontal, IzqInferiorVertical, IzqSuperiorVertical, DerInferiorVertical); //
      break;
    case 3:
      //Funcion para imprimir en un lcd de 7 segmentos los numeros 2 3 5
      //Este numero requiere que se apaguen 2 LEDS (Los ultimos 2 parametros)
      numDos_Tres_Cinco(DerSuperiorVertical, SuperiorHorizontal, MedioHorizontal, InferiorHorizontal, DerInferiorVertical, IzqSuperiorVertical, IzqInferiorVertical); //
      break;
    case 4:
      //Funcion para imprimir en un lcd de 7 segmentos el numero 4
      //Este numero requiere que se apaguen 3 LEDS (Los ultimos 3 parametros)
      numCuatro(DerSuperiorVertical, IzqSuperiorVertical, MedioHorizontal, DerInferiorVertical, SuperiorHorizontal, InferiorHorizontal, IzqInferiorVertical); //
      break;
    case 5:
      //Funcion para imprimir en un lcd de 7 segmentos los numeros 2 3 5
      //Este numero requiere que se apaguen 2 LEDS (Los ultimos 2 parametros)
      numDos_Tres_Cinco(SuperiorHorizontal, IzqSuperiorVertical, MedioHorizontal, DerInferiorVertical, InferiorHorizontal, DerSuperiorVertical, IzqInferiorVertical); //
      break;
    case 6:
      //Funcion para imprimir en un lcd de 7 segmentos el numero 6 0 9
      //Este numero requiere que se apaguen 1 LED (El ultimo (1) parametro)
      numSeis_Cero_Nueve(SuperiorHorizontal, IzqSuperiorVertical, MedioHorizontal, InferiorHorizontal, DerInferiorVertical, IzqInferiorVertical, DerSuperiorVertical); //
      break;
    case 7:
      //Funcion para imprimir en un lcd de 7 segmentos el numero 7
      //Este numero requiere que se apaguen 4 LEDS (Los ultimos 4 parametros)
      numSiete(DerSuperiorVertical, SuperiorHorizontal, DerInferiorVertical, IzqSuperiorVertical, MedioHorizontal, InferiorHorizontal, IzqInferiorVertical); //
      break;
    case 8:
      //Funcion para imprimir en un lcd de 7 segmentos el numero 8
      //Este numero no requiere que se apaguen los LEDS
      numOcho(DerSuperiorVertical, SuperiorHorizontal, IzqSuperiorVertical, MedioHorizontal, InferiorHorizontal, DerInferiorVertical, IzqInferiorVertical); //
      break;
    case 9:
      //Funcion para imprimir en un lcd de 7 segmentos el numero 6 0 9
      //Este numero requiere que se apaguen 1 LED (El ultimo (1) parametro)
      numSeis_Cero_Nueve(DerSuperiorVertical, SuperiorHorizontal, IzqSuperiorVertical, MedioHorizontal, InferiorHorizontal, DerInferiorVertical, IzqInferiorVertical); //
      break;

  }
}
void loop() {
  if (seccionAleatorio)
  {
    ImprimirVictorias();
    SeccionAleatorio();
  }
  if (espera)
  {
    Espera();
  }
  if (ejecucionUsuario)
  {
    for (int i = pinVerdeAleatorio, j = 0 ; i <= pinRojoAleatorio ; i++, j++) {
      respuestas[j] = EjecucionUsuario(i);
    }
    ejecucionUsuario = false;
    validacionRespuestas = true;
  }
  if (validacionRespuestas)
  {
    if (validarRespuestas())
    {
      for (int i = 10; i > 0; i--)
      {
        digitalWrite(pinVerdeResp, HIGH);
        digitalWrite(pinAmarilloResp, HIGH);
        digitalWrite(pinRojoResp, HIGH);
        digitalWrite(pinVerdeAleatorio, HIGH);
        digitalWrite(pinAmarilloAleatorio, HIGH);
        digitalWrite(pinRojoAleatorio, HIGH);
        delay(300);
        digitalWrite(pinVerdeResp, LOW);
        digitalWrite(pinAmarilloResp, LOW);
        digitalWrite(pinRojoResp, LOW);
        digitalWrite(pinVerdeAleatorio, LOW);
        digitalWrite(pinAmarilloAleatorio, LOW);
        digitalWrite(pinRojoAleatorio, LOW);
        delay(200);
      }
      victorias++;
      if (victorias == 10)
      {
        victorias = 0;
      }
      ImprimirVictorias();
    }
    else
    {
      digitalWrite(pinVerdeResp, HIGH);
      digitalWrite(pinAmarilloResp, HIGH);
      digitalWrite(pinRojoResp, HIGH);
      digitalWrite(pinVerdeAleatorio, HIGH);
      digitalWrite(pinAmarilloAleatorio, HIGH);
      digitalWrite(pinRojoAleatorio, HIGH);
      delay(1000);
      digitalWrite(pinVerdeResp, LOW);
      digitalWrite(pinAmarilloResp, LOW);
      digitalWrite(pinRojoResp, LOW);
      digitalWrite(pinVerdeAleatorio, LOW);
      digitalWrite(pinAmarilloAleatorio, LOW);
      digitalWrite(pinRojoAleatorio, LOW);
      delay(500);
    }
    validacionRespuestas = false;
    seccionAleatorio = true;
  }
}
/*
   El 7 Segmentos utilizado es de ANODO COMUN
   Si el que es usado es de Catodo comun cambiar HIGH por LOW y hacer el cambio en las conexiones necesarias
*/
//Funcion para imprimir en un lcd de 7 segmentos el numero 1
//Este numero requiere que se apaguen 5 LEDS (Los ultimos 5 parametros)
void numUno(int p1, int p2, int a3, int a4, int a5, int a6, int a7)
{
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(a3, HIGH);
  digitalWrite(a4, HIGH);
  digitalWrite(a5, HIGH);
  digitalWrite(a6, HIGH);
  digitalWrite(a7, HIGH);
}
//Funcion para imprimir en un lcd de 7 segmentos los numeros 2 3 5
//Este numero requiere que se apaguen 2 LEDS (Los ultimos 2 parametros)
void numDos_Tres_Cinco(int p1, int p2, int p3, int p4, int p5, int a6, int a7)
{
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
  digitalWrite(p5, LOW);
  digitalWrite(a6, HIGH);
  digitalWrite(a7, HIGH);
}
//Funcion para imprimir en un lcd de 7 segmentos el numero 4
//Este numero requiere que se apaguen 3 LEDS (Los ultimos 3 parametros)
void numCuatro(int p1, int p2, int p3, int p4, int a5, int a6, int a7)
{
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
  digitalWrite(a5, HIGH);
  digitalWrite(a6, HIGH);
  digitalWrite(a7, HIGH);
}
//Funcion para imprimir en un lcd de 7 segmentos el numero 6 0 9
//Este numero requiere que se apaguen 1 LED (El ultimo (1) parametro)
void numSeis_Cero_Nueve(int p1, int p2, int p3, int p4, int p5, int p6, int a7)
{
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
  digitalWrite(p5, LOW);
  digitalWrite(p6, LOW);
  digitalWrite(a7, HIGH);
}
//Funcion para imprimir en un lcd de 7 segmentos el numero 7
//Este numero requiere que se apaguen 4 LEDS (Los ultimos 4 parametros)
void numSiete(int p1, int p2, int p3, int a4, int a5, int a6, int a7)
{
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(a4, HIGH);
  digitalWrite(a5, HIGH);
  digitalWrite(a6, HIGH);
  digitalWrite(a7, HIGH);
}
//Funcion para imprimir en un lcd de 7 segmentos el numero 8
//Este numero no requiere que se apaguen los LEDS
void numOcho(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
  digitalWrite(p5, LOW);
  digitalWrite(p6, LOW);
  digitalWrite(p7, LOW);
}
