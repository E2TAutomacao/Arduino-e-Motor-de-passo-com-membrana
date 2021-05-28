#include <Crescer.h>

Tempora temp1;
Tempora temp2;

static int QntDiv = 30;

byte pulso = 12;
byte dir = 13;
byte ene = 11;
byte LedIndi = 8;
int Velocidade = 1000;
int Aceleracao;
long curso = 10000;
byte comando;
byte subComando;
byte hab_Mov = 0;
int Taxa_Incr = 0;

int SP_Vel;
int SP_Acel;

int Divisor = 0;
long pos = 0;
long posAtual = 0;
int Enable_S[2];
int vel = 10;
long contA;
unsigned int count1 = 0;

byte PinAvanc = A0;
byte PinRec   = A1;
byte Set      = A2;

byte Avanca;
byte Recua;
byte SetaPos;
byte etapa = 0;
byte HabAvanca = 0;
byte HabRecua = 0;
byte HabSetaPos;
byte contClick;

long Ttotal;
int Tinc;
long del;
long FreqBase = 40500;
int VetMaster [30];
long DivAprox;
float Multiplicador;
unsigned int desacel;
long next;
byte HabAcel;

byte AuxDesacel = 0;
byte AuxAcel = 0;
long posDesacel = 100000000;
int TaxaDesacel;
int desacelSP = 30;
int contD;

byte SentidoGiro = 0;
int Dado = 0;
int blinkLed;
byte habZera = 0;
byte Cicla = 0;

// 1, 5000,2000,2000
// 2, 5000,2000,2000

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println("E2T");
  pinMode(PinAvanc, INPUT_PULLUP);
  pinMode(PinRec, INPUT_PULLUP);
  pinMode(Set, INPUT_PULLUP);

  pinMode (pulso, OUTPUT);
  pinMode (dir, OUTPUT);
  pinMode (ene, OUTPUT);
  pinMode (LedIndi, OUTPUT);

  digitalWrite (pulso, 0);
  digitalWrite (dir, 1);
  digitalWrite (ene, 1);
  digitalWrite (LedIndi, 0);
  pinMode (3, OUTPUT);
  blinkLed = 1000;
  temp1.defiSP(blinkLed);
  temp2.defiSP(3000);
  // Configuração do controle de pulsos para o motor de passo.
  // Configura para Normal port mode com Output Compare disconnected
  TCCR2A = 0;
  // Clk com preescaler de 1/1024
  TCCR2B = 1;
  // Habilita a interrupção (OVF e CMPA)
  TIMSK2 = 0;
}

void loop() {

  ComandoSerial();
  LedPos1();

  Avanca = digitalRead(PinAvanc);
  Recua  = digitalRead(PinRec);
  SetaPos = digitalRead(Set);

  if (etapa == 0 and Avanca == HabAvanca)
  {
    SentidoGiro = 0;
    HabAvanca = 1;
    etapa = 1;
    StarMan();
  }

  if (etapa == 0 and Recua == HabRecua)
  {
    SentidoGiro = 1;
    HabRecua = 1;
    etapa = 2;
    StarMan();
  }
  if ((HabAvanca == 1 and etapa == 1) or (HabRecua == 1 and etapa == 2))
  {
    curso = curso + 10;
  }
  if ((Avanca == 1 and etapa == 1) or (Recua == 1 and etapa == 2))
  {
    digitalWrite(ene, HIGH);
    etapa = 0;
    Enable_S[0] = 0;
    TIMSK2 = 0;
    HabAvanca = 0;
    HabRecua = 0;
    posAtual = (posAtual + pos) / 2;
    Serial.println(posAtual);
    if (habZera == 2)
    {
      temp1.defiSP(1000);
      contClick = 0;
      habZera = 0;
    }
  }



  if (SetaPos == 0 and SetaPos == HabSetaPos)
  {
    delay(200);
    contClick++;
    HabSetaPos = 1;
    Serial.print("contClick: ");
    Serial.println(contClick);
    temp2.Saida(0);
  }
  else if (SetaPos) HabSetaPos = 0;

  if (SetaPos == 0 and temp2.Saida(1))
  {
    Cicla = 10;
    temp1.defiSP(50);
  }

  if (contClick == 1 and !habZera)
  {
    Serial.println("Zerou");
    pos = 0;
    posAtual = 0;
    habZera = 1;
    temp1.defiSP(100);
    resetMotor();
  }

  if (contClick > 1)
  {
    temp1.defiSP(3000);
    Serial.println("Libera 2");
    digitalWrite (LedIndi, 0);
    SentidoGiro = 1 - SentidoGiro;
    TIMSK2 = 0;
    comando = 1;
    subComando = Cicla;
    curso = pos;
    Velocidade = 2000;
    Aceleracao = 2000;
    contClick = 1;
    habZera = 2;
  }
}
