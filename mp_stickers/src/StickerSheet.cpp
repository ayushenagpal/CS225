#include "StickerSheet.h"

//Initializes this StickerSheet with a deep copy of the base picture and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    max_stickers = max;
    base = Image(picture);
}
//Frees all space that was dynamically allocated by this StickerSheet.
StickerSheet::~StickerSheet() {

}
//The copy constructor makes this StickerSheet an independent copy of the source.
StickerSheet::StickerSheet(const StickerSheet &other) {
    base = Image(other.base);
    max_stickers = other.max_stickers;
    sticker_location = other.sticker_location;
    // for (unsigned int i = 0; i < sticker_location.size(); i++) {
    //     //std::vector<std::pair<Image*, pair<int, int>>> sticker_location = other.sticker_location.at(i);
    //     Image* image = other.sticker_location.at(i).first;
    //     pair<unsigned, unsigned> coordinates = other.sticker_location.at(i).second;
    //     pair<Image*, pair<unsigned, unsigned>> temp = (image, coordinates).
    //     sticker_location.push_back(temp);
    // }
    // sticker_location.push_back(other.sticker_location)
    // for (unsigned int i = 0; i < sticker_location.size(); i++) {
    //     sticker_location.at(i)push_back(other.sticker_location.at(i));
    // }
}
//The assignment operator for the StickerSheet class.
const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    max_stickers = other.max_stickers;
    sticker_location = other.sticker_location;
    return *this;
}
//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
//If the new maximum number of stickers is smaller than the current number number of stickers, the stickers with indices above max - 1 will be lost.
void StickerSheet::changeMaxStickers(unsigned max) {
    if(max > max_stickers) {
        max_stickers = max;
    }
    if(max < max_stickers && max < sticker_location.size()) {
        sticker_location.resize(max);
        max_stickers = max;
    }
}
//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
//The sticker must be added to the lowest possible layer available.
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if(max_stickers <= sticker_location.size()) {
        return -1;
    }
    pair<unsigned, unsigned> coordinates;
    coordinates.first = x;
    coordinates.second = y;
    pair<Image*, pair<unsigned, unsigned>> temp;
    temp.first = &sticker;
    temp.second = coordinates;
    sticker_location.push_back(temp);

    // sticker_location.at().first() = sticker
    // sticker_location.at(i).second().first() = x;
    // sticker_location.at(i).second().second() = y;
    int layer = sticker_location.size() - 1;
    return layer;
}
//Changes the x and y coordinates of the Image in the specified layer.
//If the layer is invalid or does not contain a sticker, this function must return false. Otherwise, this function returns true.
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if(index >= 0 && index < sticker_location.size()) {
        sticker_location.at(index).second.first = x;
        sticker_location.at(index).second.second = y;
        return true;
    }
    return false;
}
//Removes the sticker at the given zero-based layer index.
void StickerSheet::removeSticker(unsigned index) {
    // if(index >= 0 && index < sticker_location.size()) {
    //     delete sticker_location.at(index).first();
    //     sticker_location.erase(sticker_location.begin() + index)
    // }
    sticker_location.erase(sticker_location.begin() + index);
}
//Returns a pointer to the sticker at the specified index, not a copy of it. That way, the user can modify the Image.
//If the index is invalid, return NULL.
Image* StickerSheet::getSticker(unsigned index) {
    if(index >= 0 && index < sticker_location.size()) {
        return sticker_location.at(index).first;
    }
    return NULL;
}

Image StickerSheet::render() const {
    Image sticker_sheet = base;
    for(unsigned int i = 0; i < sticker_location.size(); i++) {
        unsigned w = sticker_sheet.width();
        unsigned h = sticker_sheet.height();

        if(w < sticker_location.at(i).second.first + sticker_location.at(i).first->width()) {
            w = sticker_location.at(i).second.first + sticker_location.at(i).first->width();
        }
        if (h < sticker_location.at(i).second.second + sticker_location.at(i).first->height()) {
            h = sticker_location.at(i).second.second + sticker_location.at(i).first->height();
        }
        sticker_sheet.resize(w, h);
        for(unsigned int j = sticker_location.at(i).second.first; j < sticker_location.at(i).second.first + sticker_location.at(i).first->width(); j++) {
            for(unsigned int k = sticker_location.at(i).second.second; k < sticker_location.at(i).second.second + sticker_location.at(i).first->height(); k++) {
                if((sticker_location.at(i).first->getPixel((j - sticker_location.at(i).second.first), k - sticker_location.at(i).second.second)).a != 0) {
                    sticker_sheet.getPixel(j, k) = sticker_location.at(i).first->getPixel((j - sticker_location.at(i).second.first), k - sticker_location.at(i).second.second);
                }
            }
        }
    }
    return sticker_sheet;
}