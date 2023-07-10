#include <D:/Dev/Libs/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <memory>

#ifndef FLAPPY_HXX_
#define FLAPPY_HXX_

namespace FLAPPY {
	class FlappyBird {
	private:
		std::shared_ptr<sf::RenderWindow> window;
		
		float m_gravity;
		float m_frame;
		float m_space;

		int m_count;

		sf::Texture bg;
		sf::Texture flappy;
		sf::Texture pipe;
		std::shared_ptr<sf::Sprite> background;
		std::shared_ptr<sf::Sprite> bird;
		std::shared_ptr<sf::Sprite> pipeBottom;
		std::shared_ptr<sf::Sprite> pipeTop;

		std::vector<sf::Sprite> pipes;

		sf::Font font;
		sf::Text score_label;
		sf::Text gameover_label;

		bool m_gameover;
		bool m_add;
		int  m_score;

	protected:
		void Events(void);
		void Draw(void) const;
		void Game(void);
		void MovePipes(void);
		void SetBirdAnimation(void);
		void MoveBird(void);

	public:
		FlappyBird();
		
		void Run(void);

		~FlappyBird(void) {}
	};
};

#endif // FLAPPY_HXX_