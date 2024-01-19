#include "model.h"


unsigned int TextureFromFile(const char* _path, const string& _directory, bool _gamma = false);


Model::Model(string const& _path, bool _gamma) 
    : gammaCorrection(_gamma)
{
    LoadModel(_path);
}


void Model::Draw(Shader& _shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(_shader);
}

void Model::LoadModel(string const& _path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = _path.substr(0, _path.find_last_of('/'));

    // process ASSIMP's root node recursively
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* _node, const aiScene* _scene)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < _node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, _scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < _node->mNumChildren; i++)
    {
        ProcessNode(_node->mChildren[i], _scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* _mesh, const aiScene* _scene)
{
    // data to fill
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<m_Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = _mesh->mVertices[i].x;
        vector.y = _mesh->mVertices[i].y;
        vector.z = _mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (_mesh->HasNormals())
        {
            vector.x = _mesh->mNormals[i].x;
            vector.y = _mesh->mNormals[i].y;
            vector.z = _mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = _mesh->mTextureCoords[0][i].x;
            vec.y = _mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = _mesh->mTangents[i].x;
            vector.y = _mesh->mTangents[i].y;
            vector.z = _mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = _mesh->mBitangents[i].x;
            vector.y = _mesh->mBitangents[i].y;
            vector.z = _mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
    {
        aiFace face = _mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];

    // 1. diffuse maps
    vector<m_Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<m_Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<m_Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<m_Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

vector<m_Texture> Model::LoadMaterialTextures(aiMaterial* _mat, aiTextureType _type, string _typeName)
{
    vector<m_Texture> textures;
    for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++)
    {
        aiString str;
        _mat->GetTexture(_type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            m_Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = _typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char* _path, const string& _directory, bool _gamma)
{
    string filename = string(_path);
    filename = _directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << _path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}