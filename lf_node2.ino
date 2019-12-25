
//-------------------------------------------------------lf_node--------------------------------------------------------------------------

void lf_node2()
{
  while (paths < 2)
  {
    l = 0; s = 0; r = 0; x = 0; y = 0; u = 0; timer1 = 0; paths = 0;

    while ((analogRead(4) < SValue[4][2]) && (analogRead(1) > SValue[1][2]) && (analogRead(6) > SValue[6][2]))
    {
      line_follow();
    }

    while ((timer1 < limit) && (analogRead(1) > SValue[1][2]) && (analogRead(6) > SValue[6][2]))
    {
      motor1.drive(80);
      motor2.drive(80);
      timer1++;
    }
    //    Cbrake();//--------------------------------------------------------<<<<<<<<<<<<<<<<<<<<<

    if (timer1 == limit) //---------u turn detected-----------
    {
      u = 1;
      Cbrake();
    }

    for (int k = 0; k < 10; k++)
    {
      if (analogRead(1) < SValue[1][2] && analogRead(3) < SValue[3][2])
      {
        l = 1;
      }

      if (analogRead(6) < SValue[6][2] && analogRead(3) < SValue[3][2])
      {
        r = 1;
      }

      if (analogRead(1) < SValue[1][2] && analogRead(3) > SValue[3][2])
      {
        x = 1;
      }

      if (analogRead(6) < SValue[6][2] && analogRead(3) > SValue[3][2])
      {
        y = 1;
      }
      if (analogRead(4) < SValue[4][2])
      {
        s = 1;
      }
    }
    if (x == 1 || y == 1) s = 0; //cancelling out straights when x/y are triggered

    if (l == 1)
    {
      while (analogRead(0) > SValue[0][2])
      {
        motor1.drive(80);
        motor2.drive(80);
      }
      for (int k = 0; k < 20; k++)
      {
        if (analogRead(6) < SValue[6][2])
        {
          y = 1;
        }
      }
    }

    if (r == 1)
    {
      while (analogRead(7) > SValue[7][2])
      {
        motor1.drive(80);
        motor2.drive(80);
      }

      for (int k = 0; k < 20; k++)
      {
        if (analogRead(1) < SValue[1][2])
        {
          x = 1;
          digitalWrite(Rled, HIGH);
        }
      }
    }
    Cbrake();

    if (l == 1) paths++;
    if (r == 1) paths++;
    if (x == 1) paths++;
    if (y == 1) paths++;
    if (s == 1) paths++;
    if (u == 1) paths = 2;

    if (paths == 1)
    {
      if (l == 1) go_left();
      if (x == 1) go_x();
      if (s == 1) go_straight();
      if (r == 1) go_right();
      if (y == 1) go_y();

      paths = 0;
    }
  }

}
