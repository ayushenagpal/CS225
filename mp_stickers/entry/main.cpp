#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image *background = new Image();
  background-> readFromFile("../background.png");

  Image* sticker = new Image();
  sticker-> readFromFile("../sticker.png");

  StickerSheet* ss = new StickerSheet(*background, 4);
  ss->addSticker(*sticker, 50, 50);
  ss->addSticker(*sticker, 200, 200);
  ss->addSticker(*sticker, 150, 150);
   
  Image result = ss->render();
  result.writeToFile("../myImage.png");
  return 0;
}
