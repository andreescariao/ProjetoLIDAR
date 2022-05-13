//Código Ponte H com 2 Motores DC Tinkercad

//Motor A
int MA1 = 2;
int MA2 = 4;

//Motor B
int MB1 = 7;
int MB2 = 8;

//Variáveis pwm para os motores 1 e 2
int pwmA = 3;
int pwmB = 5;

//Variável auxiliar
int velocidade = 255;

void setup() {
 //Define portas de saída do Arduino para o motor A, B e pwms
 pinMode(MA1, OUTPUT);
 pinMode(MA2, OUTPUT);
 pinMode(MB1, OUTPUT);
 pinMode(MB2, OUTPUT);
 pinMode(pwmA, OUTPUT);
 pinMode(pwmB, OUTPUT);
  
}

void loop() {

  //Liga os motores
 digitalWrite(MA1, LOW);
 digitalWrite(MA2, HIGH);
 digitalWrite(MB1, LOW);
 digitalWrite(MB2, HIGH);
 
  //Velocidade de 0 a 255
  while (velocidade > 0){
    analogWrite(pwmA, velocidade);
    analogWrite(pwmB, velocidade);
    velocidade = velocidade -1;
    delay(20);
    }

   //Velocidade de 255 a 0
  while (velocidade < 255){
    analogWrite(pwmA, velocidade);
    analogWrite(pwmB, velocidade);
    velocidade = velocidade +1;
    delay(10);
    }
  
}
