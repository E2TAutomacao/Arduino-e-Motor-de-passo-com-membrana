// responsável por gerenciar os pulsos do motor.


ISR (TIMER2_OVF_vect)
{
  TCNT2 = 0xffa0;
  //PORTD ^= (1 << PD3);

  if (contA > del and AuxAcel == 0)
  {
    if (vel <= QntDiv)
    {
      Divisor = VetMaster[vel];
      vel = vel + 1;
    }
    contA = 0;
  }

  if (AuxDesacel == 0 and vel >= QntDiv)
  {
    AuxDesacel = 5;
  }

  if (pos > desacel and AuxDesacel == 5)
  {
    AuxDesacel = 1;
    desacelSP = 29;
    contD = pos + TaxaDesacel;
  }

  if (AuxDesacel == 1 and desacelSP >= 4 and contA >= del)
  {
    Divisor = VetMaster[desacelSP];
    desacelSP = desacelSP - 1;
    contD = pos;
    contA = 0;
  }


  if (count1 >= Divisor and Enable_S[0])
  {
    if (curso >= pos)
    {
      PORTB ^= (1 << PB4);// PD3
      pos++;
    }
    count1 = 0;
  }

  count1++;
  contA++;

}
