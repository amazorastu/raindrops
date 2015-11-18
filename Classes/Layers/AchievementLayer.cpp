#include "AchievementLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

AchievementLayer::AchievementLayer()
{

}
AchievementLayer::~AchievementLayer()
{

}

bool AchievementLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 225, 200, 255)))
	{
		return false;
	}

	char scoreString[10];
	for (int i = 0; i < 5; i++)
	{
		scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 100.0f);
		scoreLabel->setTextColor(Color4B(0, 0, 0, 255));
		scoreLabel->setPosition(Global::getWinSizeHalfX()*0.5f, Global::getWinSizeY() - 400.0f - 200.0f*i);
		this->addChild(scoreLabel);
		sprintf(scoreString, "%d", *(User::getInstance()->getHighScoreListForChallengeMode() + i));
		scoreLabel->setString(scoreString);
	}
	for (int i = 0; i < 5; i++)
	{
		scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 100.0f);
		scoreLabel->setTextColor(Color4B(0, 0, 0, 255));
		scoreLabel->setPosition(Global::getWinSizeX()*0.75f, Global::getWinSizeY() - 400.0f - 200.0f*i);
		this->addChild(scoreLabel);
		sprintf(scoreString, "%d", *(User::getInstance()->getHighScoreListForRelaxMode() + i));
		scoreLabel->setString(scoreString);
	}

	auto label = TextBase::createText(textTypeChallengeMode);
	label->setPosition(Global::getWinSizeHalfX()*0.5f, Global::getWinSizeY() - 200.0f);
	this->addChild(label);

	label = TextBase::createText(textTypeRelaxMode);
	label->setPosition(Global::getWinSizeX()*0.75f, Global::getWinSizeY() - 200.0f);
	this->addChild(label);



	//创建一个talbleview 将datasource设置为当前的类的对象 tableview的显示区域大小为 300 * 300
	TableView* tableView = TableView::create(this, CCSizeMake(300, 800));
	//设置tableview为水平方向  ScrollView::Direction::VERTICAL 为垂直,ScrollView::Direction::HORIZONTAL 为水平
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//设置位置
	tableView->setPosition(Vec2(Global::getWinSize().width / 2, Global::getWinSize().height / 3));
	//设置代理对象
	tableView->setDelegate(this);
	// 填充顺序
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//添加tableview到当前layer
	this->addChild(tableView);
	//加载tableview
	tableView->reloadData();


	return true;
}

void AchievementLayer::onEnterTransitionDidFinish()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(AchievementLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

Scene* AchievementLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = AchievementLayer::create();
	sc->addChild(ly);
	return sc;
}

void AchievementLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->popScene();
	}
}


//=======Table View=======

//当cell被点击时调用  cell->getIdx()获取当前点击cell的编号
void AchievementLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	// 在输出窗口打印出，当前cell的编号
	log("cell touched at index: %i", cell->getIdx());
}

//设置编号为 idx 的cell的大小  此处都为100*100
Size AchievementLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return CCSizeMake(100, 100);
}

//由于tableview是动态获取数据的，该方法在初始化时会被调用一次，之后在每个隐藏的cell显示出来的时候都会调用
TableViewCell* AchievementLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	char string[5];
	sprintf(string, "%u", idx);

	// 在重用队列中获取一个cell 然后判断cell是否为空 不为空则创建一个新的
	TableViewCell *cell = table->dequeueCell();

	if (!cell) {
		//创建一个新的cell
		cell = TableViewCell::create();
		//cell = new TableViewCell();
		//加入到自动释放池中
		//cell->autorelease();
		//创建一个图片精灵
		Sprite *sprite = Sprite::createWithSpriteFrameName("Drop1.png");
		//设置精灵锚点为左下角
		sprite->setAnchorPoint(Vec2::ZERO);
		//设置精灵位置 相当于在cell中的相对位置
		sprite->setPosition(Vec2(0, 0));
		//将精灵加入到cell中
		cell->addChild(sprite);
		//创建一个标签
		Label *label = Label::createWithTTF(string, "fonts/arial.ttf", 40.0f);
		//设置标签相对cell的位置
		label->setPosition(Vec2::ZERO);
		//设置标签锚点为左下角
		label->setAnchorPoint(Vec2::ZERO);
		//为标签做一个标记,以便于在cell在重用队列中被取出来时，能够获取的该label并重置label信息
		label->setTag(123);
		//将标签加入到cell中
		cell->addChild(label);
	}
	else
	{
		// 如果cell不为空,则根据tag获取到之前cell中存放的元素,并将元素信息重置
		//获取当前cell中的label
		Label *label = (Label*)cell->getChildByTag(123);
		//重置label的相关信息
		label->setString(string);
	}
	return cell;
}

//设置cell的个数 即一个tableview中包含了20个cell
ssize_t AchievementLayer::numberOfCellsInTableView(TableView *table)
{
	return 20;
}