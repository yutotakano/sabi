#include <iostream>

#include "pugixml.hpp"

#include "epubtoc.h"

EpubToc::EpubToc(libzippp::ZipArchive &zip, const std::string &path)
{
    zip.getEntry(path).readContent(std::cout);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(zip.getEntry(path).readAsText().c_str());
    if (!result)
    {
        throw std::runtime_error("Failed to parse TOC file: " + std::string(result.description()));
    }
}

EpubToc::~EpubToc()
{
}
