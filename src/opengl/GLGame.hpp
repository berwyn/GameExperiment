#include "../main/Game.hpp"

class GLGame : IGame
{
public:
	virtual bool Init() override;
	virtual void Loop() override;
	virtual void Terminate() override;
	
private:
	GLFWwindow* window;
}