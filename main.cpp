#include "Renderer.hpp"

int main()
{
	Renderer renderer(480, 360);
	renderer.Render();
	renderer.saveRender();
}