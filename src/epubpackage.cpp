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

    // Metadata *can* be in dc-metadata for Epub 2.0.1
    pugi::xml_node metadataNode = doc.child("package").child("metadata").child("dc-metadata");
    if (metadataNode.empty())
    {
        metadataNode = doc.child("package").child("metadata");
    }

    m_metadata = new EpubMetadata(metadataNode);

    pugi::xml_node manifestNode = doc.child("package").child("manifest");
    m_manifest = new EpubManifest(manifestNode);

    pugi::xml_node spineNode = doc.child("package").child("spine");
    m_spine = new EpubSpine(spineNode, m_manifest);
}

EpubPackage::~EpubPackage()
{
    delete m_metadata;
    delete m_manifest;
    delete m_spine;
}
