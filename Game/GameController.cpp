#include "GameController.hpp"
#include <cstdio>


//static unsigned int timeCount = 0;
static SpriteAnimated* spriteTest[625];
static sf::Font fuente = sf::Font();

static Motion* motionZoom = new Motion(1.0f, 2.0f, 1.0f); // maxVelocity, acceleration
static float speedHistory[430];
static float zoomHistory[430];

static IElement* focusIElement; // Input, Button, Map, Drag...
static IElement* arrayIElement[3];
static GameData* gameData;


// -----------------------------------------

class DummyClass
{
	public:
		DummyClass() {}
		void dummyFunction()
		{
			DEBUG->write(LOG_FILE, "Line: %u - DummyClass | dummy test called!", __LINE__);
		}
};

template <typename ClassT>
class ReporterClass
{
		typedef void (ClassT::*MemberPtr)();

	public:
		ReporterClass() {}
		void showInfoAndCall(ClassT* object, MemberPtr member)
		{
			char text[50];
			sprintf(text, "%p %p", (void*)object, (void*)member);
			DEBUG->write(LOG_FILE, "Line: %u - TEST1 | %s", __LINE__, text);
			sprintf(text, "%p", (void*)this);
			DEBUG->write(LOG_FILE, "Line: %u - TEST2 | %s", __LINE__, text);
			(object->*member)();
		}
		void dummyFunction()
		{
			DEBUG->write(LOG_FILE, "Line: %u - ReporterClass | dummy test called!", __LINE__);
		}
};

// -----------------------------------------


void GameController::init()
{
	DEBUG->write(LOG_FILE, "Line: %u - MainLoop | MainLoop Started", __LINE__);

	fuente.loadFromFile("resources/Arial.ttf");

	reset();

	for (int x = 0; x < 625; x++)
	{
		spriteTest[x] = new SpriteAnimated("resources/square.png", 2, 0);

		spriteTest[x]->setPosition(
			spriteTest[x]->getFrameWidth() * (x - (25 * ((int)x / 25))),
			spriteTest[x]->getTexture()->getSize().y * ((int)x / 25));
	}

	for (int x = 0; x < 430; x++)
	{
		speedHistory[x] = 0.0;
		zoomHistory[x] = motionZoom->getValue();
	}

	// Definir funciones para gestionar el array ( ->add(new algo()) ->delete(algo) )
	// Convertir en vector STL ?
	gameData = new GameData();
	focusIElement = nullptr;
	arrayIElement[0] = new GameMap(sf::IntRect(0, 0, 0, 0), gameData);
	arrayIElement[1] = new IRegion(sf::IntRect(0, 0, 0, 0), gameData);
	arrayIElement[0]->onTick();
	arrayIElement[1]->onTick();

	// -------------

	DummyClass* dummy_1 = new DummyClass();
	ReporterClass<DummyClass>* reporter = new ReporterClass<DummyClass>();
	reporter->showInfoAndCall(dummy_1, &DummyClass::dummyFunction);
}


void GameController::onTick()
{
	/*if ((getTimeRunning() - timeCount) > 1000)
	{
		DEBUG->Write(LOG_FILE, "Line: %u - MainLoop | FPS: %s", __LINE__, getFps());
		DEBUG->Write(LOG_FILE, "Line: %u - MainLoop | MS_LF: %s", __LINE__, getMsLastFrame());
		timeCount = getTimeRunning();
	}*/
}


void GameController::onRender()
{
	sf::RenderWindow* window = VIDEO->getWindow();

	sf::View view;
	window->clear(sf::Color(30, 30, 30));

	view.reset(sf::FloatRect(VIDEO->getCameraPosition()->x, VIDEO->getCameraPosition()->y, VIDEO->getSize().x, VIDEO->getSize().y));
	view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	motionZoom->onTick(getTimeRunning());
	view.zoom(motionZoom->getValue());
	window->setView(view);

	// -------------------------------------------

	for (int x = 0; x < 625; x++)
	{
		spriteTest[x]->setCurrentFrame(0);
	}

	signed int mousePosX = window->mapPixelToCoords(sf::Vector2i(INPUT->getMouse()->x, INPUT->getMouse()->y)).x; // convertCoords => mapPixelToCoords
	signed int mousePosY = window->mapPixelToCoords(sf::Vector2i(INPUT->getMouse()->x, INPUT->getMouse()->y)).y;

	if (mousePosX > 0 && mousePosX < (32 * 25) && mousePosY > 0 && mousePosY < (32 * 25))
	{
		spriteTest[((mousePosY / 32) * 25 + (mousePosX / 32))]->setCurrentFrame(1);
	}

	for (int x = 0; x < 625; x++)
	{
		//SpriteTest[x]->update(getMsLastFrame());
		window->draw(*spriteTest[x]);
	}

	// -------------------------------------------

	view.reset(sf::FloatRect(0, 0, VIDEO->getSize().x, VIDEO->getSize().y));
	view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	window->setView(view);

	for (int x = 0; x < 430; x++)
	{
		if (x != 429)
		{
			speedHistory[x] = speedHistory[x + 1];
			zoomHistory[x] = zoomHistory[x + 1];
		}
		else
		{
			speedHistory[x] = motionZoom->getSpeed();
			zoomHistory[x] = motionZoom->getValue();
		}
	}

	VIDEO->drawRectangle(sf::Vector2f(10,  12), sf::Vector2f(250, 275), sf::Color::Black);
	VIDEO->drawRectangle(sf::Vector2f(270, 12), sf::Vector2f(450, 100), sf::Color::Black);
	VIDEO->drawRectangle(sf::Vector2f(280, 22), sf::Vector2f(430,  80), sf::Color(100, 100, 100));

	for (int x = 0; x < 430; x++)
	{
		VIDEO->drawPoint(280 + x, 80 - ((int)(speedHistory[429 - x] * 80) / motionZoom->getMaxVelocity()) + 22, sf::Color::Red);
		VIDEO->drawPoint(280 + x, 80 - ((int)((zoomHistory[429 - x] - 0.25) * 80) / (2.0 - 0.25)) + 22, sf::Color::Blue);
	}

	VIDEO->drawPoint(275, 80 - ((int)((motionZoom->getDesiredValue() - 0.25) * 80) / (2.0 - 0.25)) + 22, sf::Color::Green);

	sf::Text text;
	text.setFont(fuente);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Regular);
	text.setColor(sf::Color::Red);
	char posicion[50];

	std::sprintf(posicion, "mouseX: %d\nmouseY: %d\ncameraX: %d\ncameraY: %d\nmousePosX: %d\nmousePosY: %d\nfps: %d\nms lastframe: %d",
				 INPUT->getMouse()->x, INPUT->getMouse()->y,
				 (int)VIDEO->getCameraPosition()->x, (int)VIDEO->getCameraPosition()->y,
				 mousePosX, mousePosY,
				 getFps(), getMsLastFrame());
	text.setString(posicion);
	text.setPosition(20, 20);
	window->draw(text);

	sprintf(posicion, "speed: %f\nzoom: %f\ndesiredZoom: %f", motionZoom->getSpeed(), motionZoom->getValue(), motionZoom->getDesiredValue());
	text.setString(posicion);
	text.setPosition(20, 200);
	window->draw(text);

	VIDEO->swapBuffers();
}


void GameController::onEvent(const int eventType, const int param1, const int param2)
{
	m_eventHandler.trigger(eventType);

	switch (eventType)
	{
		case EVENT_MOUSEDOWN:

			// TODO UI
		case EVENT_MOUSEUP:

			// TODO UI
		case EVENT_MOUSEMOTION:
			if (INPUT->getMouse()->held.left)
			{
				// FORMA CUTRE DE DESPLAZAMIENTO POR ARRASTRE
				VIDEO->getCameraPosition()->x -= (INPUT->getMouse()->xRel * motionZoom->getValue());
				VIDEO->getCameraPosition()->y -= (INPUT->getMouse()->yRel * motionZoom->getValue());
			}

		case EVENT_KEYDOWN:
			switch (param1)
			{
				case KEY::Escape:
					DEBUG->write(LOG_FILE, "Line: %u - Input | Escape Pressed", __LINE__);
					stop();
					break;

				case KEY::F1:
					DEBUG->write(LOG_FILE, "Line: %u - Input | F1 Pressed", __LINE__);
					reset();
					break;

				case KEY::Num1:
					motionZoom->newValue(0.25, getTimeRunning());
					break;

				case KEY::Num2:
					motionZoom->newValue(0.50, getTimeRunning());
					break;

				case KEY::Num3:
					motionZoom->newValue(0.75, getTimeRunning());
					break;

				case KEY::Num4:
					motionZoom->newValue(1.00, getTimeRunning());
					break;

				case KEY::Num5:
					motionZoom->newValue(1.25, getTimeRunning());
					break;

				case KEY::Num6:
					motionZoom->newValue(1.50, getTimeRunning());
					break;

				case KEY::Num7:
					motionZoom->newValue(1.75, getTimeRunning());
					break;

				case KEY::Num8:
					motionZoom->newValue(2.00, getTimeRunning());
					break;

				default:
					break;
			}

			break;

		case EVENT_MOUSEWHEEL:
			if (INPUT->getMouse()->press.wheelDown)
			{
				motionZoom->newValue(motionZoom->getDesiredValue() + 0.1, getTimeRunning());
			}
			else if (INPUT->getMouse()->press.wheelUp)
			{
				motionZoom->newValue(motionZoom->getDesiredValue() - 0.1, getTimeRunning());
			}

			break;

		case EVENT_VIDEORESIZE:
			DEBUG->write(LOG_FILE, "Line: %u - Input | Window Resize Width: %u", __LINE__, param1);
			DEBUG->write(LOG_FILE, "Line: %u - Input | Window Resize Height: %u", __LINE__, param2);
			break;

		case EVENT_QUIT:
			DEBUG->write(LOG_FILE, "Line: %u - Input | Window Closed", __LINE__);
			stop();

		default:
			break;
	}
}


void GameController::reset()
{
	motionZoom->reset();

	DEBUG->write(LOG_FILE, "Line: %u - MainLoop | Game Reset", __LINE__);
}


void GameController::end()
{
	DEBUG->write(LOG_FILE, "Line: %u - MainLoop | MainLoop Finished", __LINE__);
}
