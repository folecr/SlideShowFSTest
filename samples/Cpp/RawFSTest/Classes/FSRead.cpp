#include "FSRead.h"
#include "AppMacros.h"
#include "time.h"

USING_NS_CC;

FSRead::FSRead() : cocos2d::CCLayer() {
    time_start = 0;
    time_end = 0;
}

CCScene* FSRead::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FSRead *layer = FSRead::create();

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

// on "init" you need to initialize your instance
bool FSRead::init()
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
                                        menu_selector(FSRead::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "FSRead"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("FSRead", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    CCLog("Starting file system read test...");

    time_start = now_ms();

    bool bRet = false;

    for (std::vector<std::string>::iterator it = sourceimages.begin() ; it != sourceimages.end(); ++it) {
        unsigned long nSize = 0;
        std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename((*it).c_str());
        unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rb", &nSize);

        if (pBuffer != NULL && nSize > 0) {
            CCLog("Read file %s success!", fullPath.c_str());
        } else {
            CCLog("FILE READ FAILURE! INVALID TEST RESULT!");
            return false;
        }

        CC_SAFE_DELETE_ARRAY(pBuffer);
    }

    time_end = now_ms();

    CCLog("... done reading data.");
    CCLog("Time taken = %f millis", (double)(time_end - time_start));

    return true;
}

void FSRead::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
