#include <iostream>

#include "epubpackage.h"

EpubPackage::EpubPackage(libzippp::ZipArchive &zip, const std::string &path)
{
    std::cout << "Loading package file: " << path << std::endl;
    zip.getEntry(path).readContent(std::cout);
}

EpubPackage::~EpubPackage()
{
}
