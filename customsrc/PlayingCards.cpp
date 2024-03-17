#include "PlayingCards.h"


PlayingCards::PlayingCards()
{
	back_imageHandler = LoadGraph("data/pic/cardback.png");
}

void PlayingCards::Update()
{
	size_.x_ = static_cast <int>(65 * 0.8f);
	size_.y_ = static_cast<int>(size_.x_ * 1.4f);
	pos_ = { (pointPos_.x_ - size_.x_), (pointPos_.y_ - size_.y_) };
	pos2_ = { (pointPos_.x_ + size_.x_), (pointPos_.y_ + size_.y_) };
}

void PlayingCards::Render()
{
	//Card Size Ratio = 1.4 or 0.714

	if (isDragged)
	{
		RenderShadow(pos_, pos2_);
	}
	RenderCards(pos_, pos2_);
}

Pos PlayingCards::GetPos1() const
{
	return pos_;
}
Pos PlayingCards::GetPos2() const
{
	return pos2_;
}

Pos PlayingCards::GetPointPos() const
{
	return pointPos_;
}

void PlayingCards::SetPointPos(Pos& _pointPos)
{
	pointPos_ = _pointPos;
}

void PlayingCards::UpdateCards()
{

}


void PlayingCards::SetRank(ERank _rankType)
{
	rankType = _rankType;
}
void PlayingCards::SetSuit(ESuit _suitType)
{
	suitType = _suitType;
}

void PlayingCards::SetFaceUp()
{
	isFaceUp = true;
	std::string filePath = "data/pic/cardface/";
	std::string suitPath = "";

	switch (suitType)
	{
	case Spades:
		filePath += "spades/";
		suitPath += "spades";
		break;
	case Clubs:
		filePath += "clubs/";
		suitPath += "clubs";
		break;
	case Diamonds:
		filePath += "diamonds/";
		suitPath += "diamonds";
		break;
	case Hearts:
		filePath += "hearts/";
		suitPath += "hearts";
		break;
	default:
		filePath += "spades/";
		suitPath += "spades";
		break;
	}

	switch (rankType)
	{
	case ERank::Ace:
		filePath += "ace_of_";
		break;
	case ERank::Two:
		filePath += "2_of_";
		break;
	case ERank::Three:
		filePath += "3_of_";
		break;
	case ERank::Four:
		filePath += "4_of_";
		break;
	case ERank::Five:
		filePath += "5_of_";
		break;
	case ERank::Six:
		filePath += "6_of_";
		break;
	case ERank::Seven:
		filePath += "7_of_";
		break;
	case ERank::Eight:
		filePath += "8_of_";
		break;
	case ERank::Nine:
		filePath += "9_of_";
		break;
	case ERank::Ten:
		filePath += "10_of_";
		break;
	case ERank::Jack:
		filePath += "jack_of_";
		break;
	case ERank::Queen:
		filePath += "queen_of_";
		break;
	case ERank::King:
		filePath += "king_of_";
		break;
	default:
		filePath += "2_of_";
		break;
	}

	std::string fileFormat = ".png";
	std::string fullPath = filePath + suitPath + fileFormat;
	face_imageHandler = LoadGraph(fullPath.c_str());

}

void PlayingCards::RenderFace(Pos& _pos, Pos& _pos2)
{
	if (face_imageHandler == -1) { DrawBox(_pos.x_, _pos.y_, _pos2.x_, _pos2.y_, WHITE, 1); }
	DrawExtendGraph(_pos.x_, _pos.y_, _pos2.x_, _pos2.y_, face_imageHandler, 0);
}
void PlayingCards::RenderBack(Pos& _pos, Pos& _pos2)
{
	DrawExtendGraph(_pos.x_, _pos.y_, _pos2.x_, _pos2.y_, back_imageHandler, 0);
}
void PlayingCards::RenderCards(Pos& _pos, Pos& _pos2)
{
	if (isFaceUp)
	{
		RenderFace(_pos, _pos2);
	}
	else
	{
		RenderBack(_pos, _pos2);
	}
}

void PlayingCards::RenderShadow(Pos& _pos, Pos& _pos2)
{
	//Shadow
	int shadowOffset = 5;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(_pos.x_ - shadowOffset, _pos.y_, _pos2.x_, _pos2.y_ + shadowOffset, BLACK, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GenerateAllCards()
{
	// fill
}