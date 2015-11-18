#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

#include "Others/Global.h"
#include "Others/TextBase.h"
#include "Others/User.h"

class AchievementLayer : public cocos2d::LayerColor, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	AchievementLayer();
	~AchievementLayer();

public:
	CREATE_FUNC(AchievementLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent);


public:
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {}
	// 当tableview被放大或缩小时触发该方法  参数为当前tableview对象
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	// 当cell被点击时调用该方法 参数为当前的tableview对象与被点击的cell对象
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	// 设置tableview的Cell大小
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	// 获取编号为idx的cell
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	// 设置tableview中cell的个数
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);


private:
	virtual void onEnterTransitionDidFinish();

	cocos2d::Label* scoreLabel;
};
