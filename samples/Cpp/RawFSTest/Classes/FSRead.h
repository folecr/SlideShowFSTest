#ifndef __FSREAD_H__
#define __FSREAD_H__

#include "cocos2d.h"

class FSRead : public cocos2d::CCLayer
{
public:
    FSRead();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // another selector callback that displays the next sprite in the list

    // implement the "static node()" method manually
    CREATE_FUNC(FSRead);

private:
    double time_start;
    double time_end;
};

#endif // __FSREAD_H__
