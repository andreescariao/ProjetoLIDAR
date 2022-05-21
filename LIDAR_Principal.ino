// Código Principal Controlador PID com 2 motores DC, 2 Encoders Ópticos e 1 Ponte H


// Bibliotecas
#include <PID_v1.h>


// Constantes pra utilizar no controlador PID
#define MIN_PWM 0
#define MAX_PWM 255
#define KP 0.2
#define KI 0.2
#define KD 0.005


// Variáveis auxiliares pro Encoder e Controlador PID
double rpm;
volatile byte pulsos;
unsigned long timeold;
int pinoSensor = 2;               //Pino do Arduino ligado ao pino D0 do sensor
unsigned int pulsosDisco = 20;    //Altere o valor conforme disco encoder
double velocidade = 0;
double velocidadeSetpoint = 200;  // Alterar conforme velocidade desejada

// Motor A
int MA1 = 2;
int MA2 = 4;

// Motor B
int MB1 = 7;
int MB2 = 8;

// Variáveis pwm para os motores 1 e 2
int pwmA = 3;
int pwmB = 5;


// Cria Objeto PID para controle
PID motorPID(&rpm, &velocidade, &velocidadeSetpoint, KP, KI, KD, DIRECT);

// Função executada a cada interrupção
void contador()
{
  pulsos++;  //Incrementa contador
}





void setup() {

 //Faz conexão serial com o Arduino
 Serial.begin(9600);

  // Configura Interrupção
  pinMode(pinoSensor, INPUT);
  attachInterrupt(0, contador, FALLING);
  pulsos = 0;
  rpm = 0;
  timeold = 0;

  // Configura controle PID
  motorPID.SetOutputLimits(MIN_PWM, MAX_PWM);
  motorPID.SetMode(AUTOMATIC);
  
 //Define portas de saída do Arduino para o motor A, B e pwms
 pinMode(MA1, OUTPUT);
 pinMode(MA2, OUTPUT);
 pinMode(MB1, OUTPUT);
 pinMode(MB2, OUTPUT);
 pinMode(pwmA, OUTPUT);
 pinMode(pwmB, OUTPUT);
  
}

void loop() {


  // Calcula RPM a cada 1 Segundo
  if (millis() - timeold >= 1000)
  {
    detachInterrupt(0);    //Desabilita interrupção durante o cálculo
    rpm = (60 * 1000 / pulsosDisco ) / (millis() - timeold) * pulsos;
    timeold = millis();
    pulsos = 0;
    
    // Exibe valores no serial monitor
    Serial.print("Velocidade-1: ");
    Serial.print(velocidade, 2);
    // Serial.print("Velocidade-2: ");
    // Serial.print(velocidade2, 2);
    Serial.print("    ");
    Serial.print("RPM: ");
    Serial.println(rpm, 0);
    //Serial.print("RPM-2: ");
    // Serial.println(rpm2, 0);
    
    // Habilita novamente a interrupção
    attachInterrupt(0, contador, FALLING);
  }

  // Calcula o PWM do motor conforme Controle PID
  motorPID.Compute();


  //Liga os motores
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
 
  // Ajusta PWM no motor
  analogWrite(pwmA, velocidade);
  analogWrite(pwmB, velocidade);

  /* OBS: (Fazer testes)
  //Velocidade de 0 a 255
  while (velocidade > 0){
    analogWrite(pwmA, velocidade);
    analogWrite(pwmB, velocidade);
    velocidade = velocidade -1;
    delay(20);
    }
*/


  
}
