#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "CommonFunc.h"
class BaseObject
{
	public:
		//Initializes variables
		BaseObject();

		//Deallocates memory
		~BaseObject();
		void SetRect(const int &x,const int &y) {rect_.x=x;rect_.y=y;}
		SDL_Rect GetRect() {return rect_;}
		SDL_Texture* GetObject() {return p_object_;}
		virtual bool LoadImg(std::string path,SDL_Renderer* screen);
	    void Render(SDL_Renderer* des);
	    void free();
         int toa_do_x() {return rect_.x;}
         int toa_do_y() {return rect_.y;}
         int do_dai_w() {return rect_.w;}
         int do_dai_h() {return rect_.h;}
    protected:
        SDL_Texture* p_object_;
        SDL_Rect rect_;
};
#endif // BASE_OBJECT_H_
