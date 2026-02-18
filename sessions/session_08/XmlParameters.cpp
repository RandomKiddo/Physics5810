//  file: XmlParameters.cpp
// 
//  Implementation of access to XML parameters
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

// include files
#include <libxml/tree.h>
#include <libxml/parser.h>
#include "XmlParameters.h"

using namespace std;

XmlParameters::XmlParameters()  // constructor
{
  // just make sure document pointer is NULL
  xmlDocument = NULL;
  xpathContextForDocument = NULL;
}

XmlParameters::~XmlParameters() // destructor
{
  // if we read a document, we have to release its memory
  if (xpathContextForDocument != NULL) {
    xmlXPathFreeContext(xpathContextForDocument);
  }
  if (xmlDocument != NULL) xmlFreeDoc(xmlDocument);
}

int XmlParameters::read_xml_file(const char *filename)
{
  // get rid of any previously read information
  if (xpathContextForDocument != NULL) {
    xmlXPathFreeContext(xpathContextForDocument);
  }
  xpathContextForDocument = NULL;
  if (xmlDocument != NULL) xmlFreeDoc(xmlDocument);

  // read the new file
  xmlDocument = xmlReadFile(filename, NULL, 0);

  // if we could not, we report an error
  if (xmlDocument == NULL) return(0);

  // create a XPath context
  xpathContextForDocument = xmlXPathNewContext(xmlDocument);

  // if something went wrong here, we release the document and report an error
  if (xpathContextForDocument == NULL) {
    xmlFreeDoc(xmlDocument);
    xmlDocument = NULL;
    return(0);
  }
  
  // return success
  return(1);
}

int XmlParameters::tag_exists(const char *path_to_tag)
{
  // if nothing is there, it does not exist
  if (xpathContextForDocument == NULL) return(0);

  // evaluate the path to the object in question
  xmlXPathObjectPtr found_tags_ptr =
    xmlXPathEvalExpression(BAD_CAST path_to_tag,
			   xpathContextForDocument);

  // return not found if error
  if (found_tags_ptr == NULL) return(0);

  // if no nodes came back
  int found_tag = 0;
  if (found_tags_ptr->nodesetval && found_tags_ptr->nodesetval->nodeNr>0) {
    found_tag = 1;
  }

  // clean up nodes found
  xmlXPathFreeObject(found_tags_ptr);

  // return result
  return(found_tag);
}

int XmlParameters::tag_value_int(const char *path_to_tag, int def_value)
{
  // read the value of the tag as a string
  string value_as_string = tag_value_string(path_to_tag, "");

  // if there is nothing or the tag does not exist, return default value
  if (value_as_string.empty()) return(def_value);

  return(atoi(value_as_string.c_str()));
}

long XmlParameters::tag_value_long(const char *path_to_tag, long def_value)
{
  // read the value of the tag as a string
  string value_as_string = tag_value_string(path_to_tag, "");

  // if there is nothing or the tag does not exist, return default value
  if (value_as_string.empty()) return(def_value);

  return(atol(value_as_string.c_str()));
}

double XmlParameters::tag_value_double(const char *path_to_tag,
				       double def_value)
{
  // read the value of the tag as a string
  string value_as_string = tag_value_string(path_to_tag, "");

  // if there is nothing or the tag does not exist, return default value
  if (value_as_string.empty()) return(def_value);

  return(atof(value_as_string.c_str()));
}

string XmlParameters::tag_value_string(const char *path_to_tag,
				       string def_value)
{
  // if no XML document is loaded, we return the default value
  if (xpathContextForDocument == NULL) return(def_value);

  // evaluate the path to the object in question
  xmlXPathObjectPtr found_tags_ptr =
    xmlXPathEvalExpression(BAD_CAST path_to_tag,
			   xpathContextForDocument);

  // return default if error in path
  if (found_tags_ptr == NULL) return(def_value);

  // if no nodes came back, we also clean up and return the default
  if (found_tags_ptr->nodesetval == NULL) {
    xmlXPathFreeObject(found_tags_ptr);
    return(def_value);
  }

  xmlNodePtr current_node = found_tags_ptr->nodesetval->nodeTab[0];

  // if it does not have a child (which is where the value should be) just
  // clean up and return the default value
  if (!current_node->xmlChildrenNode) {
    xmlXPathFreeObject(found_tags_ptr);
    return(def_value);
  }

  // get the actual text
  xmlChar *value = xmlNodeListGetString(xmlDocument,
					current_node->xmlChildrenNode,
					1);

  /* store result in a string */
  string value_as_string((char*)value);

  /* clean up resources */
  xmlFree(value);
  xmlXPathFreeObject(found_tags_ptr);

  return(value_as_string);
}

