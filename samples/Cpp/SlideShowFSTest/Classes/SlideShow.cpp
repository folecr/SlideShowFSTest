#include "SlideShow.h"
#include "AppMacros.h"
USING_NS_CC;


CCScene* SlideShow::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SlideShow *layer = SlideShow::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SlideShow::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(SlideShow::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Slideshow"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Slideshow", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    std::vector<std::string> sourceimages = 
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

    CCSprite* pSprite = NULL;
    for(int i=0; i < sourceimages.size(); i++) {
        if (NULL != pSprite) {
            this->removeChild(pSprite, true);
        }

        pSprite = CCSprite::create(sourceimages[i].c_str());

        // position the sprite on the center of the screen
        pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(pSprite, 0);        
    }

    return true;
}


void SlideShow::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
