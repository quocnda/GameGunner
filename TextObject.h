#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"

class TextObject:public BaseObject
{
public:
    TextObject();
    ~TextObject();
    enum TextColor{
       RED_TEXT=0,
       WHITE_TEXT=1,
       BLACK_TEXT=2,
    };

    bool LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen);
    void Free();
    void SetColor(Uint8 red,Uint8 green,Uint8 blue);
    void SetColor(int type);

    void RenderText(SDL_Renderer* screen,int xp,int yp,SDL_Rect* clip=NULL, double angle=0.0,SDL_Point* center=NULL,SDL_RendererFlip=SDL_FLIP_NONE);
    int GetWidth() {return width;}
    int GetHeight() {return height;}


    void SetText(const std::string & text) {str_val_=text;}
    std::string GetText() {return str_val_;}





private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture;
    int width;
    int height;


};
#endif // TEXT_OBJECT_H_
