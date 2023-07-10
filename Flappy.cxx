#include "Flappy.hxx"

namespace FLAPPY {

	FlappyBird::FlappyBird() {
		window = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(800, 600),
			"FlappyBird_Clone",
			sf::Style::Titlebar | sf::Style::Close
		);

		window->setFramerateLimit(60);
		window->setPosition(sf::Vector2i(0, 0));



		m_gravity = 0;
		m_frame = 0;
		m_space = 160.0f;
		m_count = 0;



		bg.loadFromFile("./res/background.png");
		flappy.loadFromFile("./res/flappy.png");
		pipe.loadFromFile("./res/pipe.png");



		background = std::make_shared<sf::Sprite>();
		bird       = std::make_shared<sf::Sprite>();
		pipeBottom = std::make_shared<sf::Sprite>();
		pipeTop    = std::make_shared<sf::Sprite>();

		background->setTexture(bg);
		bird->setTexture(flappy);
		pipeBottom->setTexture(pipe);
		pipeTop->setTexture(pipe);



		bird->setPosition(
			400.0f - flappy.getSize().x / 2.0f,
			400.0f - flappy.getSize().y / 2.0f
		);
		bird->setScale(2.0f, 2.0f);
		bird->setTextureRect(sf::IntRect(0, 0, 34, 24));

		pipeBottom->setScale(1.5f, 1.0f);
		pipeTop->setScale(1.5f, -1.0f);



		m_gameover = false;
		m_score    = 0;



		font.loadFromFile("./res/FlappyBirdRegular.ttf");
		gameover_label.setFont(font);
		gameover_label.setString("Press SPACE button to restart!");
		gameover_label.setPosition(160, 300); // (1/5 by width, centerY)
		gameover_label.setCharacterSize(50);
		gameover_label.setOutlineThickness(3);

		score_label.setFont(font);
		score_label.setString(std::to_string(m_score));
		score_label.setPosition(10, 10); 
		score_label.setCharacterSize(50);
		score_label.setOutlineThickness(3);
	}

	void FlappyBird::Events(void) {
		auto e = std::make_shared<sf::Event>();

		while (window->pollEvent(*e)) {
			if (e->type == sf::Event::Closed) {
				window->close();
			}
		}

		if(m_gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		  m_score = 0;
		  pipes.clear();

		  bird->setPosition(
		      400.0f - flappy.getSize().x / 2.0f, 
		      400.0f - flappy.getSize().y / 2.0f 
		  );
		  m_gameover = false;
		}
	}

	void FlappyBird::Draw(void) const {
		window->clear(sf::Color::Black);
		
		window->draw(*background);
		for (auto &i : pipes) {
			window->draw(i);
		}
		window->draw(*bird);
		window->draw(score_label);

		if (m_gameover) {
			window->draw(gameover_label);
		}

		window->display();
	}

	void FlappyBird::Run(void) {
		while (window->isOpen()) {
			this->Events();
			this->Game();
			this->Draw();

			m_count++;
			if (m_count == 300) {
				m_count = 0;
			}
		}
	}

	void FlappyBird::Game(void) {
		if (!m_gameover) {
			this->SetBirdAnimation();
			this->MoveBird();
			this->MovePipes();
		}
	}

	void FlappyBird::MovePipes(void) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			m_gravity = -7.0f;
			bird->setRotation(-m_frame - 10.0f); // set animate bird like she shaking by jumping
		} else {
			bird->setRotation(m_frame  - 10.0f); // set animate bird like her shaking by jumping
		}

		if (m_count % 150 == 0) {
			int pos = std::rand() % 275 + 175;
			int space_shifting = std::rand() % 20;

			pipeBottom->setPosition(900, pos + m_space);
			pipeTop->setPosition(900, pos - space_shifting);

			pipes.push_back(*pipeBottom);
			pipes.push_back(*pipeTop);
		}

		for (std::size_t i{}; i < pipes.size(); i++) {
			if (pipes[i].getGlobalBounds().intersects(bird->getGlobalBounds())) {
				m_gameover = true;
			}

			if (pipes[i].getPosition().x < -100) {
				pipes.erase(pipes.begin() + i);
			}

			pipes[i].move(-3, 0);

			if(pipes[i].getPosition().x == 298 && !m_add){
				score_label.setString(std::to_string(++m_score));
				m_add = true;
			} else {
				m_add = false;
			}
		}
	}

	void FlappyBird::SetBirdAnimation(void) {
		m_frame += 0.15f;

		if (m_frame > 3.0f) {
			m_frame -= 3.0f;
		}

		this->bird->setTextureRect(sf::IntRect(34 * (int)m_frame, 0, 34, 24));
	}

	void FlappyBird::MoveBird(void) {
		bird->move(0, m_gravity);
		m_gravity += 0.35f;
		
		if (bird->getPosition().y >= 600) {
			bird->setPosition(bird->getPosition().x, 566); // 600 is width and 34 is height of bird => 566 is bottom border
			m_gravity = 0.0f; 
		}
		if (bird->getPosition().y <= 34) {
			bird->setPosition(bird->getPosition().x, 34); 
		}
	}

};
