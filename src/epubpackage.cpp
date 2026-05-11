#include <iostream>

#include "pugixml.hpp"

#include "epubpackage.h"

EpubPackage::EpubPackage(libzippp::ZipArchive &zip, const std::string &path)
{
    std::cout << "Loading package file: " << path << std::endl;
    zip.getEntry(path).readContent(std::cout);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(zip.getEntry(path).readAsText().c_str());
    if (!result)
    {
        throw std::runtime_error("Failed to parse package file: " + std::string(result.description()));
    }

    std::string version = doc.child("package").attribute("version").value();
    std::string unique_id = doc.child("package").attribute("unique-identifier").value();
    m_metadata = new EpubMetadata(version, unique_id);
}

EpubPackage::~EpubPackage()
{
    delete m_metadata;
}

EpubMetadata *EpubPackage::metadata()
{
    return m_metadata;
}
