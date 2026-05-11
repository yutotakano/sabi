#include <iostream>

#include "epubmetadata.h"

EpubMetadata::EpubMetadata(const std::string &version, const std::string &unique_id)
    : version(version), unique_id(unique_id)
{
    std::cout << "Package version: " << version << std::endl;
    std::cout << "Package unique identifier: " << unique_id << std::endl;
}

EpubMetadata::~EpubMetadata()
{
}
