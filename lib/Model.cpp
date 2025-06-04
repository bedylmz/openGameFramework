#include "Model.h"


//Load multipole object in std::string path

//void LoadModel(std::string filePath, std::vector<float>& vertices, std::vector<float>& textures, std::vector<float>& normals)
//{
//    // ifstream is used for reading files
//    // We'll read from a file called Sample.txt
//    std::ifstream file{ filePath };
//
//    // If we couldn't open the input file stream for reading
//    if (!file) // i must handle cannot opening file
//    {
//        std::cerr << "Uh oh, File could not be opened for reading!\n";
//        //break;//return Model{};// i should use break condition i guess
//    }
//
//    std::vector<float> T_vertices{};
//    std::vector<float> T_normals{};
//    std::vector<float> T_textures{};
//
//    bool vn{ false };
//    bool vt{ false };
//    std::string strInput{};
//    while (file)
//    {
//        if (strInput == "v")         //for T_vertices
//        {
//            for (int i{ 0 }; i < 3; i++)
//            {
//                file >> strInput;
//                T_vertices.emplace_back(std::stof(strInput));
//            }
//        }
//        else if (strInput == "vn")   //for T_normals
//        {
//            if (!vn) vn = true; //validating its existence
//            for (int i{ 0 }; i < 3; i++)
//            {
//                file >> strInput;
//                T_normals.emplace_back(std::stof(strInput));
//            }
//        }
//        else if (strInput == "vt")   //for T_textures
//        {
//            if (!vt) vt = true; //validating its existence
//            for (int i{ 0 }; i < 2; i++)
//            {
//                file >> strInput;
//                T_textures.emplace_back(std::stof(strInput));
//            }
//        }
//        else if (strInput == "f")    //for faces
//        {
//            std::string tempIndex{};
//
//            if (vn && vt)       //normals and texture coordinates have
//            {
//                for (int k{ 0 }; k < 3; k++)
//                {
//                    file >> strInput;
//                    int i{ 0 };
//                    int type{ 0 };
//
//                    while (strInput[i])
//                    {
//                        if (strInput[i] != '/')
//                        {
//                            tempIndex.push_back(strInput[i]); //using stack type because of 1/100*/20 *like these indices
//                        }
//                        else
//                        {
//                            type++;           //for seperating vertices, textures and normals
//                            if (type == 1)     // using face indices to push correct textures to std::vector<float> textures
//                            {
//                                int index = (std::stoi(tempIndex) - 1) * 3; //"-1" because of obj file indexing start 1
//                                /*                                   ^- "*3" because stacking one stack and vertices have 3 component (x,y,z)*/
//                                for (int j{ 0 }; j < 3; j++)
//                                    vertices.emplace_back(T_vertices[index + j]);
//                            }
//                            else              // using face indices to push correct textures to std::vector<float> textures
//                            {
//                                int index = (std::stoi(tempIndex) - 1) * 2; //"-1" because of obj file indexing start 1
//                                /*                                   ^- "*2" because stacking one stack and texture have 2 component (x,y)*/
//                                for (int i{ 0 }; i < 2; i++)
//                                    textures.emplace_back(T_textures[index + i]);
//                            }
//                            tempIndex = {};   //resetting temp index after used
//                        }
//                        i++;
//                    }
//                    {                         // using face indices to push correct normals to std::vector<float> normals
//                        int index = (std::stoi(tempIndex) - 1) * 3; //"-1" because of obj file indexing start 1
//                        /*                                   ^- "*3" because stacking one stack and normals have 3 component (x,y,z)*/
//                        for (int i{ 0 }; i < 3; i++)
//                            normals.emplace_back(T_normals[index + i]);
//                    }
//                    tempIndex = {};           //resetting temp index after used
//                }
//            }
//            /*
//            if(!vn && vt)      //texture coordinates have but doesnt have normals
//            {
//
//            }
//            if(vn && !vt)      //normals have but doesnt have texture coordinates
//            {
//
//            }
//            if(!vn && !vt)     //neither texture coordinates nor normals doesnt have
//            {
//
//            }*/
//        }
//        file >> strInput;
//    }
//    file.close();
//}
//
//Model getModels(const std::vector<std::string>& filePaths)
//{
//    std::vector<float> vertices{};
//    std::vector<float> normals{};
//    std::vector<float> textures{};
//
//    const std::size_t counts{ filePaths.size() };
//
//    if (counts <= 1)
//    {
//        LoadModel(filePaths[0], vertices, textures, normals);
//    }
//    else
//    {
//        for (int i{ 0 }; i < counts; i++)
//        {
//            LoadModel(filePaths[i], vertices, textures, normals);
//        }
//    }
//
//    return Model{ vertices, textures, normals };
//}

void Model::getModel(const char* filePath)
{

    // ifstream is used for reading files
    // We'll read from a file called Sample.txt
    std::ifstream file{ filePath };

    // If we couldn't open the input file stream for reading
    if (!file) // i must handle cannot opening file
    {
        std::cerr << "Uh oh, File could not be opened for reading!\n";
        //break;//return Model{};
    }
    //std::vector<float> vertices{};
    //std::vector<float> normals{};
    //std::vector<float> textures{};

    std::vector<float> temp_vertices{};
    std::vector<float> temp_normals{};
    std::vector<float> temp_textures{};

    bool vn{ false };
    bool vt{ false };
    std::string strInput{};

    while (file)
    {
        if (strInput == "v")         //for T_vertices
        {
            for (int i{ 0 }; i < 3; i++)
            {
                file >> strInput;
                temp_vertices.emplace_back(std::stof(strInput));
            }
        }
        else if (strInput == "vn")   //for T_normals
        {
            if (!vn) vn = true; //validating its existence
            for (int i{ 0 }; i < 3; i++)
            {
                file >> strInput;
                temp_normals.emplace_back(std::stof(strInput));
            }
        }
        else if (strInput == "vt")   //for T_textures
        {
            if (!vt) vt = true; //validating its existence
            for (int i{ 0 }; i < 2; i++)
            {
                file >> strInput;
                temp_textures.emplace_back(std::stof(strInput));
            }
        }
        else if (strInput == "f")    //for faces
        {
            std::string tempIndex{};

            if (vn && vt)       //normals and texture coordinates have
            {
                for (int k{ 0 }; k < 3; k++)
                {
                    file >> strInput;
                    int i{ 0 };
                    int type{ 0 };

                    while (strInput[i])
                    {
                        if (strInput[i] != '/')
                        {
                            tempIndex.push_back(strInput[i]); //using stack type because of 1/100*/20 *like these indices
                        }
                        else
                        {
                            type++;           //for seperating vertices, textures and normals
                            if (type == 1)     // using face indices to push correct textures to std::vector<float> textures
                            {
                                int index = (std::stoi(tempIndex) - 1) * 3; //"-1" because of obj file indexing start 1
                                /*                                   ^- "*3" because stacking one stack and vertices have 3 component (x,y,z)*/
                                for (int j{ 0 }; j < 3; j++)
                                    vertices.emplace_back(temp_vertices[index + j]);
                            }
                            else              // using face indices to push correct textures to std::vector<float> textures
                            {
                                int index = (std::stoi(tempIndex) - 1) * 2; //"-1" because of obj file indexing start 1
                                /*                                   ^- "*2" because stacking one stack and texture have 2 component (x,y)*/
                                for (int i{ 0 }; i < 2; i++)
                                    textures.emplace_back(temp_textures[index + i]);
                            }
                            tempIndex = {};   //resetting temp index after used
                        }
                        i++;
                    }
                    {                         // using face indices to push correct normals to std::vector<float> normals
                        int index = (std::stoi(tempIndex) - 1) * 3; //"-1" because of obj file indexing start 1
                        /*                                   ^- "*3" because stacking one stack and normals have 3 component (x,y,z)*/
                        for (int i{ 0 }; i < 3; i++)
                            normals.emplace_back(temp_normals[index + i]);
                    }
                    tempIndex = {};           //resetting temp index after used
                }
            }
            /*
            if(!vn && vt)      //texture coordinates have but doesnt have normals
            {

            }
            if(vn && !vt)      //normals have but doesnt have texture coordinates
            {

            }
            if(!vn && !vt)     //neither texture coordinates nor normals doesnt have
            {

            }*/
        }
        file >> strInput;
    }
    file.close();

    temp_vertices.clear(); temp_textures.clear(); temp_normals.clear();

    //return Model{ vertices, textures, normals };
}


void test_getModel(Model& model)
{
    std::cout << "Vertices Count : " << model.getNumVertices() << "\n";
    std::cout << "Triangles Count: " << model.getNumTriangles() << "\n";
    std::cout << "Vertices       : " << model.getNumVertices() << "\n";
    for (int i{ 0 }; i < model.getNumVertices() * 2; i += 3)
    {
        std::cout << model.getVertices()[i] << ", " << model.getVertices()[i + 1] << ", " << model.getVertices()[i + 2] << ", " << "\n";
    }
    std::cout << "Textures       : " << model.getNumTextures() << "\n";
    for (int i{ 0 }; i < model.getNumTextures(); i += 2)
    {
        std::cout << model.getTextures()[i] << ", " << model.getTextures()[i + 1] << ", " << "\n";
    }
    std::cout << "Normals        : " << model.getNumNormals() << "\n";
    for (int i{ 0 }; i < model.getNumNormals(); i += 3)
    {
        std::cout << model.getNormals()[i] << ", " << model.getNormals()[i + 1] << ", " << model.getNormals()[i + 2] << ", " << "\n";
    }

}