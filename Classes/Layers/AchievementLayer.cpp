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



	//����һ��talbleview ��datasource����Ϊ��ǰ����Ķ��� tableview����ʾ�����СΪ 300 * 300
	TableView* tableView = TableView::create(this, CCSizeMake(300, 800));
	//����tableviewΪˮƽ����  ScrollView::Direction::VERTICAL Ϊ��ֱ,ScrollView::Direction::HORIZONTAL Ϊˮƽ
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//����λ��
	tableView->setPosition(Vec2(Global::getWinSize().width / 2, Global::getWinSize().height / 3));
	//���ô������
	tableView->setDelegate(this);
	// ���˳��
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//���tableview����ǰlayer
	this->addChild(tableView);
	//����tableview
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

//��cell�����ʱ����  cell->getIdx()��ȡ��ǰ���cell�ı��
void AchievementLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	// ��������ڴ�ӡ������ǰcell�ı��
	log("cell touched at index: %i", cell->getIdx());
}

//���ñ��Ϊ idx ��cell�Ĵ�С  �˴���Ϊ100*100
Size AchievementLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return CCSizeMake(100, 100);
}

//����tableview�Ƕ�̬��ȡ���ݵģ��÷����ڳ�ʼ��ʱ�ᱻ����һ�Σ�֮����ÿ�����ص�cell��ʾ������ʱ�򶼻����
TableViewCell* AchievementLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	char string[5];
	sprintf(string, "%u", idx);

	// �����ö����л�ȡһ��cell Ȼ���ж�cell�Ƿ�Ϊ�� ��Ϊ���򴴽�һ���µ�
	TableViewCell *cell = table->dequeueCell();

	if (!cell) {
		//����һ���µ�cell
		cell = TableViewCell::create();
		//cell = new TableViewCell();
		//���뵽�Զ��ͷų���
		//cell->autorelease();
		//����һ��ͼƬ����
		Sprite *sprite = Sprite::createWithSpriteFrameName("Drop1.png");
		//���þ���ê��Ϊ���½�
		sprite->setAnchorPoint(Vec2::ZERO);
		//���þ���λ�� �൱����cell�е����λ��
		sprite->setPosition(Vec2(0, 0));
		//��������뵽cell��
		cell->addChild(sprite);
		//����һ����ǩ
		Label *label = Label::createWithTTF(string, "fonts/arial.ttf", 40.0f);
		//���ñ�ǩ���cell��λ��
		label->setPosition(Vec2::ZERO);
		//���ñ�ǩê��Ϊ���½�
		label->setAnchorPoint(Vec2::ZERO);
		//Ϊ��ǩ��һ�����,�Ա�����cell�����ö����б�ȡ����ʱ���ܹ���ȡ�ĸ�label������label��Ϣ
		label->setTag(123);
		//����ǩ���뵽cell��
		cell->addChild(label);
	}
	else
	{
		// ���cell��Ϊ��,�����tag��ȡ��֮ǰcell�д�ŵ�Ԫ��,����Ԫ����Ϣ����
		//��ȡ��ǰcell�е�label
		Label *label = (Label*)cell->getChildByTag(123);
		//����label�������Ϣ
		label->setString(string);
	}
	return cell;
}

//����cell�ĸ��� ��һ��tableview�а�����20��cell
ssize_t AchievementLayer::numberOfCellsInTableView(TableView *table)
{
	return 20;
}