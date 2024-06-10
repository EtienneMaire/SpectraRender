#include "Path.hpp"
#include "util.hpp"

namespace
{
	glm::vec3 randomDirection()
	{
		glm::vec3 v(0);
		while (v == glm::vec3(0) || dot(v, v) > 1)
		{
			v.x = random01(re) * 2 - 1;
			v.y = random01(re) * 2 - 1;
			v.z = random01(re) * 2 - 1;
		}
		v = normalize(v);
		return v;
	}

	glm::vec3 randomDirectionInHemisphere(glm::vec3 N)
	{
		glm::vec3 v = randomDirection();
		if (dot(v, N) < 0)
			v *= -1;
		return v;
	}

	bool V(Scene scene, glm::vec3 X0, glm::vec3 X1)
	{
		float dist = sqrt(dot(X1 - X0, X1 - X0));
		glm::vec3 dir = (X1 - X0) / dist;
		float t;
		PathNode node;
		scene.intersect(X0, dir, t, node);
		return t <= dist;
	}
}

void Path::create(Scene scene, uint8_t length, glm::vec3 pos, glm::vec3 dir)
{
	data.clear();

	PathNode node;
	node.mat = &defaultMat;
	node.N = glm::vec3(0);
	node.X = pos;
	data.push_back(node);

	for (uint8_t i = 0; i < length; i++)
	{
		float t;
		if (!scene.intersect(data[i].X, dir,
			t, node))
			return;
		node.X += node.N * 0.001f;
		data.push_back(node);
		dir = randomDirectionInHemisphere(node.N);
	}
}

Spectrum Path::evaluate()
{
	//return Spectrum((data[1].N + glm::vec3(1)) / 2.f, 32);
	Spectrum s(0.f, 32);
	Spectrum T(1.f, 32);
	for (uint8_t i = 1; i < data.size() - 1; i++)
	{
		PathNode nodei = data[i], nodei_1 = data[i + 1];
		glm::vec3 dir = normalize(nodei_1.X - nodei.X);
		Spectrum albedo(nodei.mat->albedo, 32);
		Spectrum emission(nodei.mat->emissionColor, 32);
		for (uint8_t i = 0; i < 32; i++) 
			s.setSample(i, s.getSample(i) + (T.getSample(i) * emission.getSample(i)));
		for (uint8_t i = 0; i < 32; i++)
			T.setSample(i, T.getSample(i) * abs(dot(nodei.N, dir)) * albedo.getSample(i));
	}
	return s;
}