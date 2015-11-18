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
	// ��tableview���Ŵ����Сʱ�����÷���  ����Ϊ��ǰtableview����
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	// ��cell�����ʱ���ø÷��� ����Ϊ��ǰ��tableview�����뱻�����cell����
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	// ����tableview��Cell��С
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	// ��ȡ���Ϊidx��cell
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	// ����tableview��cell�ĸ���
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);


private:
	virtual void onEnterTransitionDidFinish();

	cocos2d::Label* scoreLabel;
};
