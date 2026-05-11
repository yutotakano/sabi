#include <iostream>

#include "epubmetadata.h"

EpubMetadata::EpubMetadata(const std::string &version, const std::string &unique_id, const std::string &dc_title, const std::string &dc_identifier, const std::string &dc_language, const std::vector<std::string> &dc_creators)
    : version(version), unique_id(unique_id), dc_title(dc_title), dc_identifier(dc_identifier), dc_language(dc_language), dc_creators(dc_creators)
{
    std::cout << "Package version: " << version << std::endl;
    std::cout << "Package unique identifier: " << unique_id << std::endl;
    std::cout << "DC title: " << dc_title << std::endl;
    std::cout << "DC identifier: " << dc_identifier << std::endl;
    std::cout << "DC language: " << dc_language << std::endl;
    std::cout << "DC creators: " << std::endl;
    for (const std::string &creator : dc_creators)
    {
        std::cout << "  " << creator << std::endl;
    }
}

EpubMetadata::~EpubMetadata()
{
}
