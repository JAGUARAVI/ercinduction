import processing.serial.*;
Serial myPort;

// Game State
boolean loading = true;
boolean gameOver = false;
int loadingStart;
int score = 0;
int highscore = 0;
int point = 1;

// Pipes
Pipe p1 = new Pipe();
Pipe p2 = new Pipe();
Pipe p3 = new Pipe();

// Bird variables
float birdy = 300;
float birdx = 56;
PImage birdSprite;

// Physics variables
float velocity = 0;
float gravity = 0.3;
float jumpForce = -5;

// Pipe variables
int speed;
float pipeSpacingX = 300;

void setup() {
  loadingStart = millis();
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
  
  size(400, 600);
  imageMode(CENTER);
  
  birdSprite = loadImage("bird_sprite.png");
  birdSprite.resize(50, 50);
  
  p1.resetHeight();
  p2.resetHeight();
  p3.resetHeight();
  
  p1.x = width;
  p2.x = width + pipeSpacingX;
  p3.x = width + 2 * pipeSpacingX;
}

void draw() {
  background(0);
  
  if(loading) {
    fill(0, 102, 153);
    textSize(24);
    text("Please wait...", width/2 - 60, height/2);
    if(millis() - loadingStart > 2000) loading = false;
    return;
  }

  if (!gameOver) {
    velocity += gravity;
    birdy += velocity;

    if (birdy < 0) {
      birdy = 0;
      velocity = 0;
    }

    if (birdy > height) {
      birdy = height;
      gameOver = true;
    }
  }

  p1.pipe();
  p2.pipe();
  p3.pipe();
  
  image(birdSprite, birdx, birdy);

  play();
  success(p1);
  success(p2);
  success(p3);
}

void serialEvent(Serial myPort) {
  String DataIn = myPort.readStringUntil('\n');
  if(DataIn != null) {
    DataIn = trim(DataIn);
    println(DataIn);
    if(DataIn.equals("1")) {
      if(!gameOver) {
        velocity = jumpForce;
      }
    }
  }
}

void play() {
  if (!gameOver) {
    speed = 2;
    p1.x -= speed;
    p2.x -= speed;
    p3.x -= speed;

    textSize(24);
    fill(255);
    textAlign(CENTER, TOP);
    text(score, width / 2, 10);
  } else {
    if (highscore < score) {
      highscore = score;
    }

    textSize(16);
    fill(0, 102, 153);
    textAlign(CENTER, CENTER);
    text("Click : Play Again", width / 2, height / 2);
    text("Score: " + score, width / 2, height / 2 - 20);
    text("High-Score: " + highscore, width / 2, height / 2 - 40);

    if (mousePressed) {
      delay(200);
      score = 0;
      gameOver = false;
      birdy = 300;
      velocity = 0;
      p1.resetHeight();
      p2.resetHeight();
      p3.resetHeight();
      p1.x = width;
      p2.x = width + pipeSpacingX;
      p3.x = width + 2 * pipeSpacingX;
    }
  }
}

void success(Pipe test) {
  float birdRadius = birdSprite.height / 2;
  if (birdx + birdRadius > test.x && birdx - birdRadius < test.x + test.w) {
    if (birdy - birdRadius < test.top || birdy + birdRadius > height - test.bottom) {
      gameOver = true;
    }
  }
}

class Pipe {
  float top;
  float bottom;
  float x = width;
  float w = 70;
  color pipeColor = color(0, 255, 0);
  
  void resetHeight() {
    float minGap = birdSprite.height + 80;
    float maxGap = birdSprite.height * 5.5;
    
    float pipeGap = random(minGap, maxGap);

    top = random(50, height - pipeGap - 50);
    bottom = height - (top + pipeGap);
  }

  void pipe() {
    fill(pipeColor);
    rect(x, 0, w, top);
    rect(x, height - bottom, w, bottom);

    if (x < -w) {
      score += point;
      x += 3 * pipeSpacingX;
      resetHeight();
    }
  }
}
