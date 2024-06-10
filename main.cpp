#include "Renderer.hpp"
#include "Scene.hpp"
#include "Path.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 1;

	std::cout << "Loading scene...";

	Scene scene;
	scene.loadFromOBJ(argv[1]);

	std::cout << " | Done\n";

	Renderer renderer(480, 480);
	std::cout << "Rendering...";
	renderer.Render(scene, 5, 32);
	std::cout << " | Done\nSaving...";

	renderer.saveRender();
	std::cout << " | Done";
	while (true);
	//Path path;
	//path.create(scene, 5, glm::vec3(0), glm::vec3(0, 0, -1));
	//for(uint8_t i = 0; i < path.data.size(); i++)
	//	std::cout << path.data[i].X.x << ' ' 
	//			  << path.data[i].X.y << ' ' 
	//			  << path.data[i].X.z << std::endl;
	//while (true);
}