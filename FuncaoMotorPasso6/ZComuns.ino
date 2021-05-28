void StarMan()
{
  Divisor = 30;
  Enable_S[0] = 1;
  pos = 0;
  digitalWrite (LedIndi, 0);
  AuxAcel = 10;
  curso = curso + 100;
  digitalWrite(dir, SentidoGiro);
  digitalWrite(ene, LOW);
  delay(100);
  TIMSK2 = 1;

}
byte statusLed = 1;
void LedPos1()
{
  if (temp1.Saida(1))
  {
    statusLed = 1 - statusLed;
    digitalWrite (LedIndi, statusLed);
    temp1.Saida(0);
  }
}
