#include <EncoderInterfaceSimple.h>


EncoderInterfaceSimple dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
