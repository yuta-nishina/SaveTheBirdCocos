//
//  TitleScene.h
//  SaveTheBird
//
//  Created by giginet on 2014/8/1.
//
//

#ifndef __SaveTheBird__TitleScene__
#define __SaveTheBird__TitleScene__

#include "cocos2d.h"

class TitleScene :public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    TitleScene();
    virtual ~TitleScene();
    
    bool init() override;
    void onEnterTransitionDidFinish() override;
    void toStage(int stageNum);
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__SaveTheBird__TitleScene__) */
