//  file: XmlParameters.h
// 
//  Class definition to encapsulate reading of XML parameter files
//
//  Programmer:  Ralf Bundschuh  bundschuh.2@osu.edu
//
//  Revision history:
//      02/19/18  original version
//
//  Notes:
//     * provides basic functionality for reading parameters from XML files
//
//******************************************************************

// The ifndef/define macro ensures that the header is only included once
#ifndef XMLPARAMETERS_H
#define XMLPARAMETERS_H

// include files
#include <string>
#include <libxml/parser.h>
#include <libxml/xpath.h>

class XmlParameters
{
  public:
    XmlParameters();  // constructor
    ~XmlParameters(); // destructor

    int read_xml_file(const char *filename);     // read in the XML file
    int tag_exists(const char *path_to_tag);     // check if tag exists
    int tag_value_int(const char *path_to_tag, int def_value);// read an integer
    long tag_value_long(const char *path_to_tag, long def_value); // long
    double tag_value_double(const char *path_to_tag, double def_value); // dbl
    std::string tag_value_string(const char *path_to_tag, // read a string
				 std::string def_value);

  private:
    xmlDocPtr xmlDocument;  // the actual parsed XML
    xmlXPathContextPtr xpathContextForDocument; // some internal stuff
}; // end of class XmlParameters

#endif  // ndef XMLPARAMETERS_H
