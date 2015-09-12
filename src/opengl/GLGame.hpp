#include "../main/Game.hpp"

class GLGame : public IGame
{
public:
	virtual bool Init() override;
	virtual void Loop() override;
	virtual void Terminate() override;
	
private:
	GLFWwindow* window;
};