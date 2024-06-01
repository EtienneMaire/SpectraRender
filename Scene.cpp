#include "Scene.hpp"

#define TINYOBJLOADER_IMPLEMENTATION 
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "OBJ_loader/tiny_obj_loader.h"

void Scene::loadFromOBJ(std::string path)
{
    objects.clear();
    materials.clear();

    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = ""; // Search from the same directory as the OBJ file

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config))
    {
        if (!reader.Error().empty())
            std::cerr << "TinyObjReader: " << reader.Error();
        return;
    }

    if (!reader.Warning().empty())
        std::cout << "TinyObjReader: " << reader.Warning();


    tinyobj::attrib_t attrib = reader.GetAttrib();
    std::vector<tinyobj::shape_t> shapes = reader.GetShapes();
    std::vector<tinyobj::material_t> _materials = reader.GetMaterials();

    for (uint32_t i = 0; i < _materials.size(); i++)
    {
        Material mat;
        mat.albedo.x = _materials[i].diffuse[0];
        mat.albedo.y = _materials[i].diffuse[1];
        mat.albedo.z = _materials[i].diffuse[2];
        mat.metallic = _materials[i].metallic;
        mat.roughness = _materials[i].roughness;
        materials.push_back(mat);
    }

    for (size_t s = 0; s < shapes.size(); s++) 
    {
        size_t index_offset = 0;
        Mesh mesh;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
            if (fv == 3)
            {
                Triangle tri;
                for (size_t v = 0; v < fv; v++)
                {
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                    switch (v)
                    {
                    case 0:
                        tri.a = glm::vec3(vx, vy, vz);
                        break;
                    case 1:
                        tri.b = glm::vec3(vx, vy, vz);
                        break;
                    case 2:
                        tri.c = glm::vec3(vx, vy, vz);
                    }
                    /*if (idx.normal_index >= 0) {
                        tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    }

                    if (idx.texcoord_index >= 0) {
                        tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    }*/
                }

                tri.mat = &materials[shapes[s].mesh.material_ids[f]];
                mesh.addTriangle(tri);
            }
            index_offset += fv;
        }
        objects.push_back(mesh);
    }
}