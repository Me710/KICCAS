#define led_1 9
#define led_2 8

#define boutton_right 2
#define boutton_left 3
#define boutton_jump 4
#define boutton_attack 5

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(led_1, OUTPUT); //led pour signaler que les touches de directions sont activer
  pinMode(led_2, OUTPUT); //led uniquement pour signaler l'appuye sur le boutton attaques

  pinMode(boutton_right, INPUT); //direction droite
  pinMode(boutton_left, INPUT); //direction gauche
  pinMode(boutton_jump, INPUT); //direction saut
  pinMode(boutton_attack, INPUT); // attaque
}

void loop() {
  // put your main code here, to run repeatedly:
char data;
  //initialise les led chaque fois.
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);

  if (Serial.available() > 0)
  {
     data = (char)Serial.read();
    delay(5);
  }

  if (data == '1')//l'un des bouttons de direction activer 
  {
    digitalWrite(led_1, HIGH);
  }

  else if (data == '2')//boutton d'attaque activer
  {
    digitalWrite(led_2, HIGH);
  }
  else if (data == '0') //aucun boutton activer
  {
    digitalWrite(led_2, LOW);
    digitalWrite(led_1, LOW);
  }

  if (digitalRead(boutton_right) == HIGH) //boutton droite activer
  {
    Serial.println(0); //envoi de la valeur 0;
  }
  else if (digitalRead(boutton_left) == HIGH)//boutton gauche activer
  {
    Serial.println(1); //envoi de la valeur 1;
  }
   else if (digitalRead(boutton_jump) == HIGH)//boutton de saut activer
  {
    Serial.println(2);//envoi de la valeur 2;
  }
  else //aucun boutton activer
  {
    Serial.println(-1); //envoi de la valeur -1;
  }
  if(digitalRead(boutton_attack) == HIGH)
  {
    Serial.println(3);
  }
}
