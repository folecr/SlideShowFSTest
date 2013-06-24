#ifndef __SLIDESHOW_H__
#define __SLIDESHOW_H__

#include "cocos2d.h"

class SlideShow : public cocos2d::Layer
{
public:
    SlideShow();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);

    // another selector callback that displays the next sprite in the list

    // implement the "static node()" method manually
    CREATE_FUNC(SlideShow);

    void nextSprite(float dt);

private:
    cocos2d::Sprite* pSprite;
    int spriteposition_x;
    int spriteposition_y;
    cocos2d::Point spriteposition;
    double time_start;
    double time_end;
    size_t sprite_index;
};

#endif // __SLIDESHOW_H__
