#include "SlideShow.h"
#include "AppMacros.h"
#include "time.h"

USING_NS_CC;

SlideShow::SlideShow() : cocos2d::Layer() {
    Sprite* pSprite = NULL;
    time_start = 0;
    time_end = 0;
    sprite_index = 0;
    spriteposition_x = 0;
    spriteposition_y = 0;
}

Scene* SlideShow::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    SlideShow *layer = SlideShow::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

/* return current time in milliseconds */
static double
now_ms(void)
{
    struct timespec res;
    clock_gettime(CLOCK_MONOTONIC, &res);
    return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
}

// on "init" you need to initialize your instance
bool SlideShow::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Point origin = Director::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage *pCloseItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(SlideShow::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(PointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Slideshow"
    // create and initialize a label
    
    LabelTTF* pLabel = LabelTTF::create("Slideshow", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    spriteposition = ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    CCLog("Starting slideshow...");

    time_start = now_ms();

    // Schedule the nextSprite()
    sprite_index = 0;
    Director::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SlideShow::nextSprite),
                                                                   this, 0.0f,
                                                                   kRepeatForever,
                                                                   0.0f,
                                                                   false);

    return true;
}

static std::vector<std::string> sourceimages = 
    {"MagnoliaAlpha.png",
     "Official_portrait_of_Barack_Obama.png",
     "nasa-1.jpg",
     "nasa-2.jpg",
     "nasa-3.jpg",
     "nasa-4.jpg",
     "nasa-5.jpg",
     "nasa-6.jpg",
     "nasa-7.jpg",
     "nasa-8.jpg",
     "nasa-9.jpg",
     "nasa-10.jpg",
     "nasa-11.jpg",
     "nasa-12.jpg",
     "nasa-13.jpg",
     "nasa-14.jpg",
     "nasa-15.jpg",
     "nasa-16.jpg"};

void SlideShow::nextSprite(float dt) {
    // CCLog("nextSprite ...");

    if (sprite_index < sourceimages.size()) {
        if (NULL != pSprite) {
            this->removeChild(pSprite, true);
        }

        pSprite = Sprite::create(sourceimages[sprite_index].c_str());

        // position the sprite on the center of the screen
        pSprite->setPosition(spriteposition);

        // add the sprite as a child to this layer
        this->addChild(pSprite, 0);        

        // scheduler is set to repeat... so another nextSprite() will be scheduled
        sprite_index++;
    } else {
        // unschedule nextSprite()
        Director::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(SlideShow::nextSprite), this);

        double time_end = now_ms();

        CCLog("... done reading data, creating sprites and displaying them.");
        CCLog("Time taken = %f millis", (double)(time_end - time_start));
    }

    // CCLog("... nextSprite done.");
}

void SlideShow::menuCloseCallback(Object* pSender)
{
    Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
