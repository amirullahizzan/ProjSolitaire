#include "Scene.h"

Pos mousePos;
Scene* currentScene_p = nullptr;


void Scene::InitOnceFlag()
{
	if (isInit)
	{
		return;
	}
	else
	{
		Init();
		isInit = true;
	}
}

void Scene::Init()
{
}

void Scene::Update()
{

}
void Scene::Render()
{
}

//#MAINMENUSCENE
MainMenuScene::MainMenuScene()
{
	SetFontSize(50);
}

void MainMenuScene::Update()
{
	PlayerControl();
}
void MainMenuScene::Render()
{
	DisplayAnimatedTitle();
	DisplayAnimatedMenuText();
}

void MainMenuScene::PlayerControl()
{
	GetMousePoint(&mousePos.x_, &mousePos.y_);

	if (IsMouseOn(MOUSE_INPUT_LEFT))
	{
		ResetTimedCharacter(textTickBuffer, charIndexBuffer);
		currentScene_p = new GameScene();
		delete this;
	}
}

void MainMenuScene::DisplayAnimatedTitle()
{
	int originalFontSize = GetFontSize();
	SetFontSize(120);
	std::string gameTitle = "SOLITAIRE";
	const int perCharTimer = 5;
	int textLength = GetTextSize(gameTitle);
	DrawString(WINDOW_W_HALF - textLength, WINDOW_H_HALF - 200,
		GetTimedCharacter(gameTitle, perCharTimer, textTickBuffer, charIndexBuffer).c_str(),
		YELLOW);

	SetFontSize(30);
	std::string credit = "by アミルラ イザン";
	textLength = GetTextSize(credit);
	DrawString(WINDOW_W_HALF - textLength, WINDOW_H - 100,
		GetTimedCharacter(credit, perCharTimer, textTickBuffer, charIndexBuffer).c_str(),
		YELLOW);

	SetFontSize(originalFontSize);
}
void MainMenuScene::DisplayAnimatedMenuText()
{
	std::array<Pos, 2> buttons;
	std::string text[buttons.size()] = { "Start" , "Exit" };

	int fontSize = GetFontSize();
	const int buttonUIOffset = 40 + fontSize;
	//for (int i = 0; i < buttons.size(); i++)
	int i = 0;
	for (auto& buttons_i : buttons)
	{
		const int perCharTimer = 50;
		int textLength = GetTextSize((text[i]));
		DrawString(WINDOW_W_HALF - textLength,
			WINDOW_H_HALF + buttonUIOffset * i,
			GetTimedCharacter(text[i], perCharTimer, textTickBuffer, charIndexBuffer).c_str(),
			YELLOW);
		i++;
	}

}
//#GAMESCENE
GameScene::GameScene()
{
	back_imageHandler = LoadGraph("data/pic/cardback.png");
	playingCards_p.fill(nullptr); // Initialize playingCards_p with nullptr
	for (auto& cardsIndex : playingCards_p)
	{
		cardsIndex = new PlayingCards();
		cardsIndex->SetSuit(PlayingCards::ESuit::Spades);
	}
	InitSet(playingCards_p);
	InitShuffle(playingCards_p);
	InitRows();
	FaceUpLastRow();
	SetDeck();

}
void GameScene::InitSet(std::array<PlayingCards*, MAX_CARDS_INGAME>& _playingCards_p)
{
	if (onePairMode)
	{
		const int cardsPerGroup = 13; // Number of cards per group

		// Loop through each group
		for (int group = 0; group < numCompleteGroups; ++group)
		{
			// Calculate the starting index for this group
			int startIndex = group * cardsPerGroup;

			// Assign the same suit to all cards in this group
			for (int i = 0; i < cardsPerGroup; ++i)
			{
				// Calculate the index for this card based on the group
				int cardIndex = startIndex + i;

				// Assign the suit and rank to the card at the calculated index
				_playingCards_p[cardIndex]->SetSuit(PlayingCards::ESuit::Spades);
				// Assign ranks Ace to King to each group of cards, repeating for each group
				_playingCards_p[cardIndex]->SetRank(static_cast<PlayingCards::ERank>((group * cardsPerGroup + i) % 13 + 1));
			}
		}
	}
	else if (multiPairMode)
	{
		const int numSuits = 4;
		const int numRanks = 4;
		const int cardsPerSuit = MAX_CARDS_INGAME / (PlayingCards::ESuit::Spades - PlayingCards::ESuit::Hearts + 1);
		for (int suit = PlayingCards::ESuit::Hearts; suit <= PlayingCards::ESuit::Spades; ++suit)
		{
			// Loop through each rank
			for (int rank = PlayingCards::ERank::Ace; rank <= PlayingCards::ERank::King; ++rank)
			{
				// Calculate the index for this card based on the suit and rank
				int cardIndex = (suit - PlayingCards::ESuit::Hearts) * cardsPerSuit + (rank - PlayingCards::ERank::Ace);

				// Assign the suit and rank to the card at the calculated index
				_playingCards_p[cardIndex]->SetSuit(static_cast<PlayingCards::ESuit>(suit));
				_playingCards_p[cardIndex]->SetRank(static_cast<PlayingCards::ERank>(rank));
			}
		}
	}

}

void GameScene::InitShuffle(std::array<PlayingCards*, MAX_CARDS_INGAME>& _playingCards_p)
{
	std::random_device rd;
	std::mt19937 rng(rd());

	for (int i = 0; i < MAX_CARDS_INGAME; i++)
	{
		std::uniform_int_distribution<int> dist(i, MAX_CARDS_INGAME - 1);
		int j = dist(rng);
		std::swap(_playingCards_p[i], _playingCards_p[j]);
		//_playingCards_p[i].SetSuit();
	}
}

void GameScene::Update()
{
	GetMousePoint(&mousePos.x_, &mousePos.y_);

	for (auto& cardsIndex : playingCards_p)
	{
		cardsIndex->Update();
		if (cardsIndex->isDragged)
		{
			DragCard(cardsIndex);
			if (IsMouseRelease(INPUT_MOUSE_LEFT))
			{
				DropCard(cardsIndex);
			}
			continue;
		}
	}

	for (auto& cardsIndex : playingCards_p)
	{
		if (isDraggingCard)
		{
			break;
		}
		if (IsMouseOn(INPUT_MOUSE_LEFT))
		{
			if (IsMouseHitCard(cardsIndex->GetPos1(), cardsIndex->GetPos2()))
			{
				if (cardsIndex->isDrawn && cardsIndex->isFaceUp)
				{
					SetDragCard(cardsIndex);
					draggedCard = cardsIndex;
				}

			}
		}
	}

	if (IsMouseOn(INPUT_MOUSE_LEFT))
	{
		if (HitboxBoxCircle(deckButtonPos, deckButtonPos2, mousePos))
		{
			DrawCards();
		}
	}
}
void GameScene::RenderDrawCardButton()
{
	if (deckLeft <= 0) return;
	deckButtonSize.x_ = static_cast <int>(65 * 0.8f);
	deckButtonSize.y_ = static_cast<int>(deckButtonSize.x_ * 1.4f);
	deckButtonPos = { (deckPointPos.x_ - deckButtonSize.x_), (deckPointPos.y_ - deckButtonSize.y_) };
	deckButtonPos2 = { (deckPointPos.x_ + deckButtonSize.x_), (deckPointPos.y_ + deckButtonSize.y_) };

	DrawExtendGraph(deckButtonPos.x_, deckButtonPos.y_, deckButtonPos2.x_, deckButtonPos2.y_, back_imageHandler, 0);
}
void GameScene::SetDragCard(PlayingCards* cardsIndex)
{
	isDraggingCard = true;
	cardsIndex->isDragged = true;
	initialPos = mousePos;
}
void GameScene::DragCard(PlayingCards* cardsIndex)
{
	Pos newPos = { cardsIndex->pointPos_.x_ + mousePos.x_ - initialPos.x_, cardsIndex->pointPos_.y_ + mousePos.y_ - initialPos.y_ };
	cardsIndex->SetPointPos(newPos);
	initialPos = mousePos;
}
bool GameScene::CardHitCard(const Pos& pos1, const Pos& pos2, const Pos& otherPos1, const Pos& otherPos2)
{
	if (
		pos1.x_ <= otherPos2.x_ && pos2.x_ >= otherPos1.x_ &&
		pos1.y_ <= otherPos2.y_ && pos2.y_ >= otherPos1.y_
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void GameScene::SetCardChild(PlayingCards*& _draggedCard, PlayingCards*& _otherCard)
{
	int nextRow = 0;
	// Find the row index of the hit card (assuming _otherCard is the hit card)
	int hitRowIndex = -1;
	int hitColumnIndex = -1;

	int draggedCardRow = -1;
	int draggedCardColumn = -1;

	// Find the row and column index of the dragged card (_draggedCard)
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			if (Row[i][j] == _draggedCard)
			{
				draggedCardRow = i;
				draggedCardColumn = j;
				break;
			}
		}
		if (draggedCardRow != -1 && draggedCardColumn != -1)
			break;
	}

	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			if (Row[i][j] == _otherCard)
			{
				hitRowIndex = i;
				hitColumnIndex = j;
				break;
			}
		}
		if (hitRowIndex != -1)
			break;
	}
	// Find the next available column following the hit card's column
	int nextColumn = hitColumnIndex + 1;

	// Check if the next column is within the bounds
	if (nextColumn < MAX_COLUMN)
	{
		// Add _draggedCard to the next column
		//if(Row[hitRowIndex][hitColumnIndex]->isFaceUp) {return;}
		Row[draggedCardRow][draggedCardColumn] = nullptr;
		Row[hitRowIndex][nextColumn] = _draggedCard;
		Row[hitRowIndex][nextColumn]->pointPos_.x_ = 120 * hitRowIndex + UPPER_BORDER.x_ + BORDER_OFFSET.x_;
		Row[hitRowIndex][nextColumn]->pointPos_.y_ = 40 * nextColumn + UPPER_BORDER.y_ + BORDER_OFFSET.y_;
		Row[hitRowIndex][nextColumn]->SetPointPos(Row[hitRowIndex][nextColumn]->pointPos_);
	}
	else
	{
		// Create a new row and add _draggedCard to its first column
		int newRow = hitRowIndex + 1;

		// Check if the new row is within the bounds
		if (newRow < MAX_ROW)
		{
			Row[newRow][0] = _draggedCard;
			Row[newRow][0]->pointPos_.x_ = 120 * newRow + UPPER_BORDER.x_ + BORDER_OFFSET.x_;
			Row[newRow][0]->pointPos_.y_ = UPPER_BORDER.y_ + BORDER_OFFSET.y_;
			Row[newRow][0]->SetPointPos(Row[newRow][0]->pointPos_);
		}
		else
		{
			// Handle case where there is no more space for a new row
			// For example, you could ignore adding cards or handle it as needed
			// Here you might want to display a message or perform some other action
		}
	}

}

void GameScene::DropCard(PlayingCards*& draggedCard)
{

	for (size_t t = 0; t < playingCards_p.size(); t++)
	{
		if (playingCards_p[t] == draggedCard) continue;
		if (playingCards_p[t]->isFaceUp)
		{
			if (CardHitCard(draggedCard->GetPos1(), draggedCard->GetPos2(), playingCards_p[t]->GetPos1(), playingCards_p[t]->GetPos2()))
			{
				SetCardChild(draggedCard, playingCards_p[t]);
				break;
			}
		}
	}
	FaceUpLastRow();
	isDraggingCard = false;
	draggedCard->isDragged = false;
}

void GameScene::InitRows()
{
	int cardIndex = 0;
	for (int j = 0; j < MAX_COLUMN; j++)
	{
		for (int i = 0; i < MAX_ROW; i++)
		{
			if (cardIndex >= INITIAL_CARDS_ON_TABLE) // Check if all cards are placed
			{
				break;
			}

			Row[i][j] = playingCards_p[cardIndex];
			Row[i][j]->pointPos_.x_ = 120 * i + UPPER_BORDER.x_ + BORDER_OFFSET.x_;
			Row[i][j]->pointPos_.y_ = 40 * j + UPPER_BORDER.y_ + BORDER_OFFSET.y_;
			Row[i][j]->isDrawn = true;
			cardIndex++;
		}

	}
	deckLeft = MAX_CARDS_INGAME - INITIAL_CARDS_ON_TABLE - cardDrawnCounter;
}


void GameScene::FaceUpLastRow()
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COLUMN; j++)
		{
			if (Row[i][j + 1] == nullptr)
			{
				if (Row[i][j])Row[i][j]->SetFaceUp();
			}
		}
	}
}
void GameScene::SetDeck()
{
	for (int deckCardsIndex = INITIAL_CARDS_ON_TABLE; deckCardsIndex < MAX_CARDS_INGAME; deckCardsIndex++)
	{
		Deck = playingCards_p[deckCardsIndex];
		Pos deckPos = { 0,0 };
		Deck->SetPointPos(deckPos);
	}
}

void GameScene::Render()
{
	RenderDrawCardButton();
	DrawBorderLine();
	printfDx("CARDS :%d\n", playingCards_p.size());
	printfDx("%d,%d\n", debugPos.x_, debugPos.y_);
	for (size_t t = 0; t < playingCards_p.size(); t++)
	{
		if (playingCards_p[t]->isFaceUp)
		{
			//printfDx("%d,%d,%d,%d\n", playingCards_p[t]->pos_.x_, playingCards_p[t]->pos_.y_, playingCards_p[t]->pos2_.x_, playingCards_p[t]->pos2_.y_);
			//DrawBox(playingCards_p[t]->pos_.x_ - 50, playingCards_p[t]->pos_.y_ - 50, playingCards_p[t]->pos2_.x_, playingCards_p[t]->pos2_.y_, RED, 1);
		}
	}

	for (auto& cardsIndex : playingCards_p)
	{
		//printfDx("cardpos %d,%d \n", cardsIndex->pointPos_.x_, cardsIndex->pointPos_.y_);
		cardsIndex->Render();
	}
	if (draggedCard)draggedCard->Render();
}

void GameScene::DrawBorderLine()
{
	constexpr int LineWidth = 1200;
	DrawLine(UPPER_BORDER.x_, UPPER_BORDER.y_, UPPER_BORDER.x_ + LineWidth, UPPER_BORDER.y_, WHITE, 3);
}

bool GameScene::IsMouseHitCard(Pos _cardPos1, Pos _cardPos2)
{
	if (HitboxBoxCircle(_cardPos1, _cardPos2, mousePos))
	{
		return true;
	}
	return false;
}
void GameScene::DrawCards()
{
	int cardRowIndex = 0;
	for (int j = 0; j < MAX_COLUMN; j++)
	{
		for (int i = 0; i < MAX_ROW; i++)
		{
			if (Row[i][j + 1] == nullptr)
			{
				for (int k = INITIAL_CARDS_ON_TABLE; k < MAX_CARDS_INGAME; k++)
				{
					if (!playingCards_p[k]->isDrawn)
					{
						Row[i][j + 1] = playingCards_p[k];
						Row[i][j + 1]->pointPos_.x_ = 120 * i + UPPER_BORDER.x_ + BORDER_OFFSET.x_;
						Row[i][j + 1]->pointPos_.y_ = 40 * (j + 1) + UPPER_BORDER.y_ + BORDER_OFFSET.y_;
						Row[i][j + 1]->isDrawn = true;
						Row[i][j + 1]->SetFaceUp();
						cardDrawnCounter++;
						cardRowIndex++;
						deckLeft = MAX_CARDS_INGAME - INITIAL_CARDS_ON_TABLE - cardDrawnCounter;
						if (cardRowIndex >= 10) return;
						break;
					}
				}
			}
		}
	}

}

//#ENDGAMESCENE
void EndGameScene::Update()
{
}

void EndGameScene::Render()
{

}



