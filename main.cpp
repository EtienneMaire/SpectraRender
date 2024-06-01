#include "Renderer.hpp"
#include "Scene.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;

	Scene scene;
	scene.loadFromOBJ(argv[1]);

	//std::cout << scene.objects.size();

	//while (true);

	Renderer renderer(480, 480);
	renderer.Render(scene);

	renderer.saveRender();
}