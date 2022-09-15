#include "Image.h"

//Lighten an Image by increasing the luminance of every pixel by 0.1
void Image::lighten() {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).l = getPixel(i, j).l + 0.1;
            if(getPixel(i, j).l < 0) {
                getPixel(i, j).l = 0;
            }
            if(getPixel(i, j).l > 1) {
                getPixel(i, j).l = 1;
            }
        }
    }
}
//Lighten an Image by increasing the luminance of every pixel by amount
void Image::lighten (double amount) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).l = getPixel(i, j).l + amount;
            if(getPixel(i, j).l < 0) {
                getPixel(i, j).l = 0;
            }
            if(getPixel(i, j).l > 1) {
                getPixel(i, j).l = 1;
            } 
        }
    }
}
//Darken an Image by decreasing the luminance of every pixel by 0.1
void Image::darken() {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).l = getPixel(i, j).l - 0.1;
            if(getPixel(i, j).l < 0) {
                getPixel(i, j).l = 0;
            }
            if(getPixel(i, j).l > 1) {
                getPixel(i, j).l = 1;
            }
        }
    }
}
//Darkens an Image by decreasing the luminance of every pixel by amount.
void Image::darken(double amount) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).l = getPixel(i, j).l - amount;
            if(getPixel(i, j).l < 0) {
                getPixel(i, j).l = 0;
            }
            if(getPixel(i, j).l > 1) {
                getPixel(i, j).l = 1;
            }
        }
    }
}
//Saturates an Image by increasing the saturation of every pixel by 0.1.
void Image::saturate() {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).s = getPixel(i, j).s + 0.1;
            if(getPixel(i, j).s < 0) {
                getPixel(i, j).s = 0;
            }
            if(getPixel(i, j).s > 1) {
                getPixel(i, j).s = 1;
            } 
        }
    }
}
//Saturates an Image by increasing the saturation of every pixel by amount. 
void Image::saturate(double amount) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).s = getPixel(i, j).s + amount;
            if(getPixel(i, j).s < 0) {
                getPixel(i, j).s = 0;
            }
            if(getPixel(i, j).s > 1) {
                getPixel(i, j).s = 1;
            }
        }
    }
}
//Desaturates an Image by decreasing the saturation of every pixel by 0.1.
void Image::desaturate() {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).s = getPixel(i, j).s - 0.1;
            if(getPixel(i, j).s < 0) {
                getPixel(i, j).s = 0;
            }
            if(getPixel(i, j).s > 1) {
                getPixel(i, j).s = 1;
            }
        }
    }
}
//Desaturates an Image by decreasing the saturation of every pixel by amount
void Image::desaturate(double amount) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).s = getPixel(i, j).s - amount;
            if(getPixel(i, j).s < 0) {
                getPixel(i, j).s = 0;
            }
            if(getPixel(i, j).s > 1) {
                getPixel(i, j).s = 1;
            }
        }
    }
}
//Turns the image grayscale.
void Image::grayscale() {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j).s = 0;
        }
    }
}
//Rotates the color wheel by degrees.
//Rotating in a positive direction increases the degree of the hue. This function ensures that the hue remains in the range [0, 360].
void Image::rotateColor(double degrees) {
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            if((getPixel(i, j).h + degrees) > 360) {
                getPixel(i, j).h = getPixel(i, j).h - 360;
            } 
            if((getPixel(i, j).h + degrees) < 0) {
                getPixel(i, j).h = getPixel(i, j).h + 360;
            }
            getPixel(i, j).h = getPixel(i, j).h + degrees;
        }
    }
}
//Illinify the image
void Image::illinify() {
    //Illini Orange hue 11
    //Illini Blue hue 216
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            if(getPixel(i, j).h > 113.5) {
                getPixel(i, j).h = 216;
            } else {
                getPixel(i, j).h = 11;
            }
        }
    }
}
//Scale the Image by a given factor.
void Image::scale(double factor) {
    Image* temp = new Image(*this);
    resize(width() * factor, height() * factor);
    for(unsigned int i = 0; i < width(); i++) {
        for(unsigned int j = 0; j < height(); j++) {
            getPixel(i, j) = temp->getPixel((i/factor), (j/factor));
            if(j == height() - 1) {
                break;
            }
        }
        if(i == width() - 1) {
            break;
        }
    }
    delete temp; 
}
//Scales the image to fit within the size (w x h). 
void Image::scale(unsigned w, unsigned h) {
   double width_factor = (double)w/(double)width();
   double height_factor = (double)h/(double)height();

   double min = std::min(width_factor, height_factor);
//    double min = 0.0;
//    if(h > w) {
//     min = w;
//    } else {
//     min = h;
//    }
   scale(min);
}