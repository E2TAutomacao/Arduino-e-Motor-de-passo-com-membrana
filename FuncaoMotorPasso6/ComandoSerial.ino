void ComandoSerial()
{
  if (Serial.available () > 0)
  {
    Dado = Serial.parseInt ();
    curso = Serial.parseInt ();
    Velocidade = Serial.parseInt ();
    Aceleracao = Serial.parseInt ();

    Serial.print("curso: ");
    Serial.println (curso);
    Serial.print("Velocidade: ");
    Serial.println (Velocidade);
    Serial.print("Aceleracao: ");
    Serial.println (Aceleracao);
    curso = curso * 2;
    if (curso > 0)SentidoGiro = 1;
    else
    {
      SentidoGiro = 0;
      curso = curso * (-1);
    }

    if (Dado == 1)
    {
      comando = 1;
      subComando = 0;
    }

    if (Dado == 2)
    {
      comando = 1;
      subComando = 10;
    }
    if (Dado == 3)
    {
       resetMotor();
    }
  }

  if (comando == 1)
  {
    SP_Motores(Velocidade, Aceleracao, SentidoGiro);
    comando = 2;
  }

  MonitoraMov ();

}
