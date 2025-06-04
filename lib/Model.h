#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Model
{
    private:

        static inline std::size_t currentID{ 0 };
        std::size_t ID{ 0 };

        //static inline unsigned int vboCounter{ 0 }; //hmm learn about inline
        //unsigned int vbo{0};

        std::size_t numVertices  { 0 };
        std::size_t numTriangles { 0 };
        std::size_t numTextures  { 0 };
        std::size_t numNormals   { 0 };

        //im changing to pointer but if i want remorph object with math, i want recover it
        std::vector<float> vertices{};
        std::vector<float> textures{};
        std::vector<float> normals{};

        float position [3] {0,0,0};
        float rotation [3] {0,0,0};
        float scale    [3] {0,0,0};

        unsigned int texture{ 0 }; // this id of texture

        void getModel(const char* filePath);
          
    public:

        Model(const char * filePath) : ID{ currentID }//, vbo{ vboCounter++ }
        {
            getModel(filePath);
            numVertices  = vertices.size() * 4 ;
            numTriangles = vertices.size() / 3;
            numTextures  = textures.size() * 4 ;
            numNormals   = normals.size() * 4 ;
        }

        Model(const std::vector<float>& v, const std::vector<float>& vt, const std::vector<float>& vn)
            :numVertices { v.size() * 4 },
            numTriangles { v.size() / 3 },
            numTextures  { vt.size() * 4 },
            numNormals   { vn.size() * 4 },
            vertices     { v },
            textures     { vt },
            normals      { vn },
            ID           { currentID }
        {
        }

        //default copy constructor
        Model(const Model& copy) = default;

        std::size_t  getID()           const  { return ID; }
        //unsigned int getVBO()          const  { return vbo; }
        std::size_t  getNumVertices()  const  { return numVertices; }
        std::size_t  getNumTriangles() const  { return numTriangles; }
        std::size_t  getNumTextures()  const  { return numTextures; }
        std::size_t  getNumNormals()   const  { return numNormals; }

        float * getVertices() { return vertices.data(); }
        float * getTextures() { return textures.data(); }
        float * getNormals()  { return normals.data(); }

        unsigned int getTexture() const          { return texture; }
        void setTexture(unsigned int textureLoc) { texture = textureLoc; }


    };

    //Model getModels(const std::vector<std::string>& filePath);
    
    void test_getModel(Model& model);


#endif