
int numObjects = 100;
MyObject[] obj = new MyObject[numObjects];

void setup()
{
  background(30);
  size(500, 500);
  
  for(int i=0; i<numObjects; i++)
  {
    obj[i] = new MyObject();
    obj[i].w = random(100);
    obj[i].h = random(100);
    obj[i].x = random(width);
    obj[i].y = random(height);
    obj[i].col = random(255);
  }
}

void draw()
{
  
  for(int i=0; i<numObjects; i++)
  {
    obj[i].draw();
  } 
}
