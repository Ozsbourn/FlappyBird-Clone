#include "Flappy.hxx"

int main(int argc, char* argv[]) {
	std::srand(time(0));

	auto flappy = std::make_shared<FLAPPY::FlappyBird>();
	flappy->Run();
	// auto flappy = FLAPPY::FlappyBird();
	// flappy.Run();

	return 0;
}
