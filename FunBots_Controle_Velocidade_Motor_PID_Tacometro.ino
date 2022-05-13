/*
      Programa para controle de velocidade de motor via Sensor Infravermelho
      Setpoint de velocidade ajustado no programa
      Controle PID busca manter RPM constante conforme setpoint desejado

      Componentes:
        - Arduino Uno;
        - Sensor de Velocidade Infravermelho;
        - Shield L293D;
        - Motor com Redução e disco de encoder;

      Versão 1.0 - Versão inicial com controle de Velocidade via PWM, variáveis mostradas no Serial - 21/Mar/2021

      Programa referência para leitura do sensor: https://www.arduinoecia.com.br/sensor-de-velocidade-lm393-arduino/
      
 *    * Criado por Cleber Borges - FunBots - @cleber.funbots  *     *

      Instagram: https://www.instagram.com/cleber.funbots/
      Facebook: https://www.facebook.com/cleber.funbots
      YouTube: https://www.youtube.com/c/funbots
      Telegram: https://t.me/cleberfunbots

*/

// Bibliotecas
#include <AFMotor.h>
#include <PID_v1.h>

// Configuração do Motor
AF_DCMotor motor(1);

// Constantes do Controle PID
#define MIN_PWM 0
#define MAX_PWM 255
#define KP 0.2
#define KI 0.2
#define KD 0.005

// Variáveis do Sensor Infravermelho e PID
double rpm;
volatile byte pulsos;
unsigned long timeold;
int pinoSensor = 2;               //Pino do Arduino ligado ao pino D0 do sensor
unsigned int pulsosDisco = 20;    //Altere o valor conforme disco encoder
double velocidade = 0;
double velocidadeSetpoint = 200;  // Alterar conforme velocidade desejada

// Cria PID para controle
PID motorPID(&rpm, &velocidade, &velocidadeSetpoint, KP, KI, KD, DIRECT);

// Função executada a cada interrupção
void contador()
{
  pulsos++;  //Incrementa contador
}

/*
 *  SETUP
 */
void setup() {
  // Inicia Serial
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
}

/*
 * LOOP
 */
void loop() {
  // Calcula RPM a cada 1 Segundo
  if (millis() - timeold >= 1000)
  {
    detachInterrupt(0);    //Desabilita interrupção durante o cálculo para evitar sair do IF
    rpm = (60 * 1000 / pulsosDisco ) / (millis() - timeold) * pulsos;
    timeold = millis();
    pulsos = 0;
    
    // Exibe valores no serial monitor
    Serial.print("Vel: ");
    Serial.print(velocidade, 2);
    Serial.print("    ");
    Serial.print("RPM: ");
    Serial.println(rpm, 0);
    
    // Habilita novamente a interrupção
    attachInterrupt(0, contador, FALLING);
  }

  // Calcula o PWM do motor conforme Controle PID
  motorPID.Compute();

  // Ajusta PWM no motor
  motor.setSpeed(velocidade);   // Utiliza velocidade calculada
  motor.run(FORWARD);          // Movimenta motor
}
