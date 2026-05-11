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

    // Required elements (Epub 3 = 5.5.1, Epub 2 = 2.2)
    std::string dc_title = doc.child("package").child("metadata").child("dc:title").child_value();
    std::string dc_identifier = doc.select_node(("/package/metadata/dc:identifier[@id='" + unique_id + "']").c_str()).node().child_value();
    std::string dc_language = doc.child("package").child("metadata").child("dc:language").child_value();

    // doesn't distinguish roles (optional) for now
    std::vector<std::string> dc_creators;
    for (pugi::xml_node creatorNode : metadataNode.children("dc:creator"))
    {
        dc_creators.push_back(creatorNode.child_value());
    }
    m_metadata = new EpubMetadata(version, unique_id, dc_title, dc_identifier, dc_language, dc_creators);
}

EpubPackage::~EpubPackage()
{
    delete m_metadata;
}

EpubMetadata *EpubPackage::metadata()
{
    return m_metadata;
}
