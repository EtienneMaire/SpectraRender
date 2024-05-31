#include "Renderer.hpp"
#include "SpectrumDefs.hpp"

int main()
{
	initSpectrums();
	Renderer renderer(480, 360);
	renderer.Render();
	renderer.saveRender();
}