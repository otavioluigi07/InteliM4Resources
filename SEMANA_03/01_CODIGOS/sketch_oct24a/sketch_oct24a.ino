#include <Arduino.h>

const int botaoPins[] = {17, 5, 15, 19}; //botões
const int ledPins[] = {33, 32, 14, 27};    //LEDs
const int botaoReset = 4; // Pino do botão de reset
const int numeroBotoes = 4;

int sequence[100];    // Sequência 
int tamanhoSequencia = 1; // Comprimento inicial 
int setp = 0;    // Passo atual da sequência

void setup() {
  for (int i = 0; i < numeroBotoes; i++) {
    pinMode(botaoPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(botaoReset, INPUT_PULLUP);

  randomSeed(analogRead(0)); // gerador de números aleatórios

  // Inicia a sequência
  for (int i = 0; i < 100; i++) {
    sequence[i] = random(0, numeroBotoes);
  }

  delay(1000);       // Aguarda um segundo antes de começar o jogo
  playSequence();     // Inicia o jogo
}

void loop() {
  if (digitalRead(botaoReset) == LOW) {
    // Botão de reset pressionado
    while (digitalRead(botaoReset) == LOW) {} // Espera o botão ser solto

    // Piscar LEDs para indicar reset
    flashLeds(4, 100);

    // Reinicia o jogo
    tamanhoSequencia = 1;
    setp = 0;
    for (int i = 0; i < 100; i++) {
      sequence[i] = random(0, numeroBotoes);
    }

    delay(1000); // Aguarda um segundo antes de começar o jogo novamente
    playSequence();
  }

  for (int i = 0; i < numeroBotoes; i++) {
    if (digitalRead(botaoPins[i]) == LOW) {
      while (digitalRead(botaoPins[i]) == LOW) {} // Espera o botão ser solto
      if (i == sequence[setp]) {
        setp++;
        if (setp == tamanhoSequencia) {
          // O jogador completou a sequência
          tamanhoSequencia++;
          setp = 0;
          playSequence();
        }
      } else {
        // O jogador errou a sequência
        gameOver();
      }
    }
  }
}

void playSequence() {
  for (int i = 0; i < tamanhoSequencia; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);
    delay(500); // Mantém a luz acesa por 0.5 segundo
    digitalWrite(ledPins[sequence[i]], LOW);
    delay(100); // Aguarda 0.1 segundo antes de passar para o próximo
  }
}

void gameOver() {
  flashLeds(5, 100);

  // Reinicia o jogo
  tamanhoSequencia = 1;
  setp = 0;
  for (int i = 0; i < 100; i++) {
    sequence[i] = random(0, numeroBotoes);
  }

  delay(1000); // Aguarda um segundo antes de começar o jogo novamente
  playSequence();
}

void flashLeds(int numFlashes, int delayTime) {
  for (int k = 0; k < numFlashes; k++) {
    for (int j = 0; j < numeroBotoes; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(delayTime);
    for (int j = 0; j < numeroBotoes; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(delayTime);
  }
}
