#include "PongController.hpp"


Pong::Pong() : GameBase(1024, 768)
{
	fuente_.loadFromFile("resources/Arial.ttf");
	marcador_.setFont(fuente_);
	marcador_.setCharacterSize(50);
	marcador_.setStyle(sf::Text::Regular);
	marcador_.setColor(sf::Color::White);

	this->Reset();
}


Pong::~Pong()
{

}


void Pong::Init()
{

}


void Pong::OnTick()
{
	// Movimiento Jugador
	if(INPUT->get_key_held()->Up.value)
	{
		if(player_pos_.y > 0)
		{
			player_pos_.y -= 4;
		}
	}

	if(INPUT->get_key_held()->Down.value)
	{
		if(player_pos_.y <= 668)
		{
			player_pos_.y += 4;
		}
	}

	// Movimiento CPU
	if(ball_pos_.y + 10 < cpu_pos_.y + 50)
	{
		if(cpu_pos_.y > 0)
		{
			cpu_pos_.y -= 4 + (0.5 * (signed int)(player_score_ - cpu_score_));
		}
	}
	else
	{
		if(cpu_pos_.y <= 668)
		{
			cpu_pos_.y += 4 + (0.5 * (signed int)(player_score_ - cpu_score_));
		}
	}

	// Colisiones Palas-Pelota
	if(ball_pos_.x <= player_pos_.x + 20 && ball_pos_.x + 20 >= player_pos_.x)
	{
		if(ball_pos_.y + 20 >= player_pos_.y && ball_pos_.y <= player_pos_.y + 100)
		{
			ball_mov_.x = 1;
		}
	}

	if(ball_pos_.x <= cpu_pos_.x + 20 && ball_pos_.x + 20 >= cpu_pos_.x)
	{
		if(ball_pos_.y + 20 >= cpu_pos_.y && ball_pos_.y <= cpu_pos_.y + 100)
		{
			ball_mov_.x = 0;
		}
	}

	// Colisiones Bordes Pelota
	if(ball_pos_.x - 5 < 0)
	{
		cpu_score_++;
		player_pos_.y = 334;
		cpu_pos_.y = 334;
		ball_mov_.x = 1;
		ball_pos_.x = 502;
		ball_pos_.y = 374;
	}

	if(ball_pos_.x + 5 > 1004)
	{
		player_score_++;
		player_pos_.y = 334;
		cpu_pos_.y = 334;
		ball_mov_.x = 0;
		ball_pos_.x = 502;
		ball_pos_.y = 374;
	}

	if(ball_pos_.y - 5 < 0)
	{
		ball_mov_.y = 1;
	}

	if(ball_pos_.y + 5 > 748)
	{
		ball_mov_.y = 0;
	}

	// Movimiento Pelota
	if(ball_mov_.x)
	{
		ball_pos_.x += 5 + (0.5 * (signed int)(player_score_ - cpu_score_));
	}
	else
	{
		ball_pos_.x -= 5 + (0.5 * (signed int)(player_score_ - cpu_score_));
	}

	if(ball_mov_.y)
	{
		ball_pos_.y += 5 + (0.5 * (signed int)(player_score_ - cpu_score_));
	}
	else
	{
		ball_pos_.y -= 5 + (0.5 * (signed int)(player_score_ - cpu_score_));
	}
}


void Pong::OnRender()
{
	sf::RenderWindow* window = VIDEO->get_window();
	window->clear(sf::Color::Black);

	char message[50];
	std::sprintf(message, "%02d | %02d", player_score_, cpu_score_);
	marcador_.setString(message);
	marcador_.setPosition(450, 20);
	window->draw(marcador_);

	VIDEO->DrawRectangle(Vector2f(ball_pos_.x, ball_pos_.y), Vector2f(20, 20), sf::Color::White);
	VIDEO->DrawRectangle(Vector2f(player_pos_.x, player_pos_.y), Vector2f(20, 100), sf::Color::White);
	VIDEO->DrawRectangle(Vector2f(cpu_pos_.x, cpu_pos_.y), Vector2f(20, 100), sf::Color::White);

	VIDEO->SwapBuffers();
}


void Pong::OnEvent(const int event_type, const int param_1, const int param_2)
{
	this->event_handler_.Trigger(event_type);

	switch(event_type)
	{
		case EVENT_KEYDOWN:
			switch(param_1)
			{
				case KEY::Escape:
					this->Stop();
					break;

				case KEY::F1:
					this->Reset();
					break;
			}

			break;

		case EVENT_QUIT:
			this->Stop();
	}
}


void Pong::Reset()
{
	ball_pos_.x = 502;
	ball_pos_.y = 374;
	ball_mov_.x = 1;
	ball_mov_.y = 1;
	player_pos_.x = 10;
	player_pos_.y = 334;
	cpu_pos_.x = 1024 - 30;
	cpu_pos_.y = 334;
	player_score_ = 0;
	cpu_score_ = 0;
}


void Pong::End()
{

}
