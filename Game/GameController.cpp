#include "GameController.hpp"
#include <cstdio>


//static unsigned int timeCount = 0;
static SpriteAnimated* SpriteTest[625];
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
		void DummyFunction()
		{
			DEBUG->Write(LOG_FILE, "Line: %u - DummyClass | dummy test called!", __LINE__);
		}
};

template <typename ClassT>
class ReporterClass
{
		typedef void (ClassT::*PtrMember)();

	public:
		ReporterClass() {}
		void ShowInfoAndCall(ClassT* object, PtrMember member)
		{
			char text[50];
			sprintf(text, "%p %p", (void*)object, (void*)member);
			DEBUG->Write(LOG_FILE, "Line: %u - TEST1 | %s", __LINE__, text);
			sprintf(text, "%p", (void*)this);
			DEBUG->Write(LOG_FILE, "Line: %u - TEST2 | %s", __LINE__, text);
			(object->*member)();
		}
		void DummyFunction()
		{
			DEBUG->Write(LOG_FILE, "Line: %u - ReporterClass | dummy test called!", __LINE__);
		}
};

// -----------------------------------------


void GameController::Init()
{
	DEBUG->Write(LOG_FILE, "Line: %u - MainLoop | MainLoop Started", __LINE__);

	fuente.loadFromFile("resources/Arial.ttf");

	this->Reset();

	for(int x = 0; x < 625; x++)
	{
		SpriteTest[x] = new SpriteAnimated("resources/square.png", 2, 0);

		SpriteTest[x]->setPosition(
			SpriteTest[x]->get_frame_width() * (x - (25 * ((int)x / 25))),
			SpriteTest[x]->getTexture()->getSize().y * ((int)x / 25));
	}

	for(int x = 0; x < 430; x++)
	{
		speedHistory[x] = 0.0;
		zoomHistory[x] = motionZoom->get_value();
	}

	// Definir funciones para gestionar el array ( ->add(new algo()) ->delete(algo) )
	// Convertir en vector STL ?
	gameData = new GameData();
	focusIElement = NULL;
	arrayIElement[0] = new GameMap(IntRect(0, 0, 0, 0), gameData);
	arrayIElement[1] = new IRegion(IntRect(0, 0, 0, 0), gameData);
	arrayIElement[0]->OnTick();
	arrayIElement[1]->OnTick();

	// -------------

	DummyClass* dummy_1 = new DummyClass();
	ReporterClass<DummyClass>* reporter = new ReporterClass<DummyClass>();
	reporter->ShowInfoAndCall(dummy_1, &DummyClass::DummyFunction);
}


void GameController::OnTick()
{
	/*if ((this->get_time_running() - timeCount) > 1000)
	{
		DEBUG->Write(LOG_FILE, "Line: %u - MainLoop | FPS: %s", __LINE__, this->get_fps());
		DEBUG->Write(LOG_FILE, "Line: %u - MainLoop | MS_LF: %s", __LINE__, this->get_milliseconds_last_frame());
		timeCount = this->get_time_running();
	}*/
}


void GameController::OnRender()
{
	sf::RenderWindow* window = VIDEO->get_window();

	sf::View view;
	window->clear(sf::Color(30, 30, 30));

	view.reset(sf::FloatRect(VIDEO->get_camera_position()->x, VIDEO->get_camera_position()->y, VIDEO->get_size().x, VIDEO->get_size().y));
	view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	motionZoom->OnTick(this->get_time_running());
	view.zoom(motionZoom->get_value());
	window->setView(view);

	// -------------------------------------------

	for(int x = 0; x < 625; x++)
	{
		SpriteTest[x]->set_current_frame(0);
	}

	signed int mousePosX = window->mapPixelToCoords(sf::Vector2i(INPUT->get_mouse()->x, INPUT->get_mouse()->y)).x; // convertCoords => mapPixelToCoords
	signed int mousePosY = window->mapPixelToCoords(sf::Vector2i(INPUT->get_mouse()->x, INPUT->get_mouse()->y)).y;

	if(mousePosX > 0 && mousePosX < (32 * 25) && mousePosY > 0 && mousePosY < (32 * 25))
	{
		SpriteTest[((mousePosY / 32) * 25 + (mousePosX / 32))]->set_current_frame(1);
	}

	for(int x = 0; x < 625; x++)
	{
		//SpriteTest[x]->update(this->msLastFrame);
		window->draw(*SpriteTest[x]);
	}

	// -------------------------------------------

	view.reset(sf::FloatRect(0, 0, VIDEO->get_size().x, VIDEO->get_size().y));
	view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	window->setView(view);

	for(int x = 0; x < 430; x++)
	{
		if(x != 429)
		{
			speedHistory[x] = speedHistory[x + 1];
			zoomHistory[x] = zoomHistory[x + 1];
		}
		else
		{
			speedHistory[x] = motionZoom->get_speed();
			zoomHistory[x] = motionZoom->get_value();
		}
	}

	VIDEO->DrawRectangle(Vector2f(10,  12), Vector2f(250, 275), sf::Color::Black);
	VIDEO->DrawRectangle(Vector2f(270, 12), Vector2f(450, 100), sf::Color::Black);
	VIDEO->DrawRectangle(Vector2f(280, 22), Vector2f(430,  80), sf::Color(100, 100, 100));

	for(int x = 0; x < 430; x++)
	{
		VIDEO->DrawPoint(280 + x, 80 - ((int)(speedHistory[429 - x] * 80) / motionZoom->get_max_velocity()) + 22, sf::Color::Red);
		VIDEO->DrawPoint(280 + x, 80 - ((int)((zoomHistory[429 - x] - 0.25) * 80) / (2.0 - 0.25)) + 22, sf::Color::Blue);
	}

	VIDEO->DrawPoint(275, 80 - ((int)((motionZoom->get_desired_value() - 0.25) * 80) / (2.0 - 0.25)) + 22, sf::Color::Green);

	sf::Text text;
	text.setFont(fuente);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Regular);
	text.setColor(sf::Color::Red);
	char posicion[50];

	std::sprintf(posicion, "mouseX: %d\nmouseY: %d\ncameraX: %d\ncameraY: %d\nmousePosX: %d\nmousePosY: %d\nfps: %d\nms lastframe: %d",
				 INPUT->get_mouse()->x, INPUT->get_mouse()->y,
				 (int)VIDEO->get_camera_position()->x, (int)VIDEO->get_camera_position()->y,
				 mousePosX, mousePosY,
				 this->get_fps(), this->get_milliseconds_last_frame());
	text.setString(posicion);
	text.setPosition(20, 20);
	window->draw(text);

	sprintf(posicion, "speed: %f\nzoom: %f\ndesiredZoom: %f", motionZoom->get_speed(), motionZoom->get_value(), motionZoom->get_desired_value());
	text.setString(posicion);
	text.setPosition(20, 200);
	window->draw(text);

	VIDEO->SwapBuffers();
}


void GameController::OnEvent(const int event_type, const int param_1, const int param_2)
{
	this->event_handler_.Trigger(event_type);

	switch(event_type)
	{
		case EVENT_MOUSEDOWN:

			// TODO UI
		case EVENT_MOUSEUP:

			// TODO UI
		case EVENT_MOUSEMOTION:
			if(INPUT->get_mouse()->held.left)
			{
				// FORMA CUTRE DE DESPLAZAMIENTO POR ARRASTRE
				VIDEO->get_camera_position()->x -= (INPUT->get_mouse()->x_rel * motionZoom->get_value());
				VIDEO->get_camera_position()->y -= (INPUT->get_mouse()->y_rel * motionZoom->get_value());
			}

		case EVENT_KEYDOWN:
			switch(param_1)
			{
				case KEY::Escape:
					DEBUG->Write(LOG_FILE, "Line: %u - Input | Escape Pressed", __LINE__);
					this->Stop();
					break;

				case KEY::F1:
					DEBUG->Write(LOG_FILE, "Line: %u - Input | F1 Pressed", __LINE__);
					this->Reset();
					break;

				case KEY::Num1:
					motionZoom->NewValue(0.25, this->get_time_running());
					break;

				case KEY::Num2:
					motionZoom->NewValue(0.50, this->get_time_running());
					break;

				case KEY::Num3:
					motionZoom->NewValue(0.75, this->get_time_running());
					break;

				case KEY::Num4:
					motionZoom->NewValue(1.00, this->get_time_running());
					break;

				case KEY::Num5:
					motionZoom->NewValue(1.25, this->get_time_running());
					break;

				case KEY::Num6:
					motionZoom->NewValue(1.50, this->get_time_running());
					break;

				case KEY::Num7:
					motionZoom->NewValue(1.75, this->get_time_running());
					break;

				case KEY::Num8:
					motionZoom->NewValue(2.00, this->get_time_running());
					break;

				default:
					break;
			}

			break;

		case EVENT_MOUSEWHEEL:
			if(INPUT->get_mouse()->press.wheel_down)
			{
				motionZoom->NewValue(motionZoom->get_desired_value() + 0.1, this->get_time_running());
			}
			else if(INPUT->get_mouse()->press.wheel_up)
			{
				motionZoom->NewValue(motionZoom->get_desired_value() - 0.1, this->get_time_running());
			}

			break;

		case EVENT_VIDEORESIZE:
			DEBUG->Write(LOG_FILE, "Line: %u - Input | Window Resize Width: %u", __LINE__, param_1);
			DEBUG->Write(LOG_FILE, "Line: %u - Input | Window Resize Height: %u", __LINE__, param_2);
			break;

		case EVENT_QUIT:
			DEBUG->Write(LOG_FILE, "Line: %u - Input | Window Closed", __LINE__);
			this->Stop();

		default:
			break;
	}
}


void GameController::Reset()
{
	motionZoom->Reset();

	DEBUG->Write(LOG_FILE, "Line: %u - MainLoop | Game Reset", __LINE__);
}


void GameController::End()
{
	DEBUG->Write(LOG_FILE, "Line: %u - MainLoop | MainLoop Finished", __LINE__);
}
