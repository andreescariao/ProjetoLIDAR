//Código Motor DC com Encoder Magnético Tinkercad

#define deltaPulso 1000
int motor1 = 6;
int motor2 = 4;
int pwm = 3;
int encoder = 2;

volatile unsigned long pulso = 0;
unsigned long verificaPulso, dT, ultimaVerificacao;
float velocidade;

void ContaPulso(){
  pulso++;
}

void setup(){
   Serial.begin(9600);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(pwm,OUTPUT);
  pinMode(encoder, INPUT);
  digitalWrite(encoder, HIGH);
  attachInterrupt (digitalPinToInterrupt(encoder), ContaPulso, FALLING);
  pulso = 0L;
  verificaPulso = millis();
  ultimaVerificacao = millis();
  Frente();
  analogWrite(pwm,255);
}


void loop(){
  
 //função para determinar os pulsos no tempo
  if( millis() >= verificaPulso){
    dT = millis() - ultimaVerificacao; 
    noInterrupts();
    //Calcular Velocidade em RPM
    //572 RPM = 0.57 * k
    // k = 10003.5088
    velocidade = 1003.508772 * pulso /dT;
    Serial.println(velocidade);
    pulso = 0L;
    interrupts(); 
    ultimaVerificacao = millis();
    verificaPulso = millis() + deltaPulso;
    
  }
}

void Frente(){
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
}

void Tras(){
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,HIGH);
}
