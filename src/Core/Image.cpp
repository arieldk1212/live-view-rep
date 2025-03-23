#include "Core/Image/Image.h"

Image::Image(const std::filesystem::path &Path, const StringUnMap &Relation)
    : m_ImageFolderPath(Path), m_ImageRelation(Relation) {}