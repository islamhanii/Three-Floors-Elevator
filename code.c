int begin = 1;

int floorNum = 0;

int U1 = 0;

int U2 = 0;

int U3 = 0;

int D1 = 0;

int D2 = 0;

int D3 = 0;

int O1 = 0;

int O2 = 0;

int O3 = 0;

int F1 = 0;

int F2 = 0;

int F3 = 0;

/*------------------------------------------------------------------------------------------------------*/

void setup()
{
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(13, INPUT);
    pinMode(12, INPUT);
    pinMode(9, INPUT);
    pinMode(8, INPUT);
    pinMode(7, INPUT);
    pinMode(6, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
}

/*-----------------------------------------------------------------------------------------------------*/

void delaycheck(int left, int right)
{
    for(int i=0; i<15; i++)
    {
        O1 = analogRead(A3);
        O2 = analogRead(A4);
        O3 = analogRead(A5);
        if(O1 > 0 || O2 > 0 || O3 > 0)
        {
            analogWrite(11, 0);
            analogWrite(10, 0);
            while(true)
            {
                O1 = analogRead(A3);
                O2 = analogRead(A4);
                O3 = analogRead(A5);
                if(O1<1 && O2<1 && O3<1)
                {
                    analogWrite(11,right);
                    analogWrite(10,left);
                    break;
                }
            }
        }
        delay(100);
    }
}

/*-----------------------------------------------------------------------------------------------------*/

void loop()
{
    if(begin == 1)
    {
        digitalWrite(0, HIGH);
        begin = 0;
        floorNum = 1;
    }

    U1 = digitalRead(13);
    D1 = digitalRead(12);
    U2 = digitalRead(9);
    D2 = digitalRead(8);
    U3 = digitalRead(7);
    D3 = digitalRead(6);
    
    O1 = analogRead(A3);
    O2 = analogRead(A4);
    O3 = analogRead(A5);
    
    F1 = digitalRead(3);
    F2 = digitalRead(4);
    F3 = digitalRead(5);

    if(O1 > 0 || O2 > 0 || O3 > 0)
    {
        analogWrite(11, 0);
        analogWrite(10, 0);
    }
    
    else
    {
        if((U1 == HIGH || D1 == HIGH || F1 == HIGH) && floorNum != 1)
        {
            analogWrite(11,255);
            analogWrite(10,0);
            
            if(floorNum == 3)
            {
                delaycheck(0, 255);
                
                digitalWrite(1,HIGH);
                digitalWrite(2,LOW);
            }
            
            delaycheck(0, 255);
            digitalWrite(0,HIGH);
            digitalWrite(1,LOW);
            floorNum = 1;
        }
        
        else if((U2 == HIGH || D2 == HIGH || F2 == HIGH) && floorNum != 2)
        {
            if(floorNum == 3)
            {
                analogWrite(11,255);
                analogWrite(10,0);
                delaycheck(0, 255);;
                digitalWrite(1,HIGH);
                digitalWrite(2,LOW);
            }
            
            else
            {
                analogWrite(11,0);
                analogWrite(10,255);
                delaycheck(255, 0);
                digitalWrite(1,HIGH);
                digitalWrite(0,LOW);
            }
            floorNum = 2;
        }
        
        else if((U3 == HIGH || D3 == HIGH || F3 == HIGH) && floorNum != 3)
        {
            analogWrite(11,0);
            analogWrite(10,255);
            
            if(floorNum == 1)
            {
                delaycheck(255, 0);
                digitalWrite(1,HIGH);
                digitalWrite(0,LOW);
            }
            
            delaycheck(255, 0);
            digitalWrite(2,HIGH);
            digitalWrite(1,LOW);
            floorNum = 3;
        }
            
        analogWrite(11,0);
        analogWrite(10,0);
    }
    
    delay(10);
}
