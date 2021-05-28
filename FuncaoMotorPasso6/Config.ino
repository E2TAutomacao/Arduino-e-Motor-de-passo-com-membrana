void SP_Motores(int SP_Vel, int SP_Acel, byte SPDir)
{
  Ttotal = 1000 * (float (SP_Vel) / float (SP_Acel));
  Tinc = (Ttotal / QntDiv) + 1;

  Taxa_Incr = SP_Vel / Tinc;
  DivAprox = FreqBase / SP_Vel;
  Multiplicador = float (Tinc) / QntDiv;

  float mat1 =  float (Tinc) / 1000.00;
  del = (mat1 * float (FreqBase)) * 2;

  float mat2 = (float (curso) / 2) / float (SP_Vel); // tempo total do percurso
  float mat3 = float (Ttotal) / 1000.00;  // Tempo para acelerar em segundos
  float mat4 = (float (SP_Acel) * (mat3 * mat3)) / 2; // calcula o fim da aceleração
  float mat5 = curso - (mat4 * 2.00);

  desacel = mat5;
  if (desacel < 0)AuxDesacel = 10;
  else
  {
    AuxDesacel = 0;
    AuxAcel = 0;
  }

  next = 0;
  HabAcel = 1;

  TaxaDesacel = Taxa_Incr;
  for (int i = 1; i < QntDiv; i++)
  {
    VetMaster[i] = FreqBase / ((Multiplicador * i) * Taxa_Incr);
  }

  VetMaster[QntDiv] = DivAprox;
  Divisor = VetMaster[1];
  vel = 1;
  hab_Mov = 1;
  Enable_S[0] = 1;
  delay (500);
  digitalWrite (ene, 0);
  digitalWrite (dir, SPDir);
  digitalWrite (pulso, 0);

}

void MonitoraMov()
{
  if (comando == 2)
  {
  //  Serial.println("--");
    pos = 0;
    count1 = 0;
    contA = 0;
    comando = 3;
    TIMSK2 = 1;
  }

  if (comando == 3 and pos >= curso)
  {
    if (subComando == 10)
    {
      digitalWrite (ene, 1);
      delay (2000);
      digitalWrite (ene, 0);
      Enable_S[0] = 0;
      comando = 0;
      TIMSK2 = 0;
      hab_Mov = 0;
      vel = 0;
      Divisor = 0;
      contA = 0;
      count1 = 0;
      SentidoGiro = 1 - SentidoGiro;
      comando = 1;
    }
    else resetMotor();
  }
}


void resetMotor()
{
  digitalWrite (ene, 1);
  digitalWrite (pulso, 0);
  Serial.println ("Fim do ciclo");

  Enable_S[0] = 0;
  comando = 0;
  TIMSK2 = 0;
  hab_Mov = 0;
  vel = 0;
  Divisor = 0;
  curso = 0;
  contA = 0;
  count1 = 0;
  AuxDesacel = 10;
  Cicla = 0;
}
