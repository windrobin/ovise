#ifndef OVISE_SCENE_PROTOTYPE_H_
#define OVISE_SCENE_PROTOTYPE_H_

// Solutuion's inludes
#ifndef OVISE_SCENE_PROTOTYPE_DATA_USED
#define OVISE_SCENE_PROTOTYPE_DATA_USED
#include "./OViSEScenePrototypeData.h"
#endif

// Include Xerces
#ifndef XERCESC_UTIL_XMLSTRING_USED
#define XERCESC_UTIL_XMLSTRING_USED
#include <xercesc/util/XMLString.hpp>
#endif

#ifndef XERCESC_SAX_HANDLERBASE_USED
#define XERCESC_SAX_HANDLERBASE_USED
#include <xercesc/sax/HandlerBase.hpp>
#endif

#ifndef XERCES_PARSERS_XERCESDOMPARSER_USED
#define XERCES_PARSERS_XERCESDOMPARSER_USED
#include <xercesc/parsers/XercesDOMParser.hpp>
#endif

#ifndef XERCES_DOM_DOM_USED
#define XERCES_DOM_DOM_USED
#include <xercesc/dom/DOM.hpp>
#endif

#ifndef XERCES_CPP_NAMESPACE_USE_USED
#define XERCES_CPP_NAMESPACE_USE_USED
XERCES_CPP_NAMESPACE_USE
#endif

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

#ifndef WX_FILENAME_USED
#define WX_FILENAME_USED
#include <wx/filename.h>
#endif

#ifndef WX_LIST_USED
#define WX_LIST_USED
#include <wx/list.h>
#endif

// TODO: not fully implemented
class OViSEScenePrototype
{
private:
	wxString UniqueName;
	xercesc::DOMDocument* DOMRepresentation;
	

	void SetUniqueName(wxString UniqueName);
	void SetDOMRepresentation(xercesc::DOMDocument* DOMRepresentation);
public:
	OViSEScenePrototypeData Data;

	wxString				GetUniqueName();
	xercesc::DOMDocument*	GetDOMRepresentation();

	OViSEScenePrototype(wxString UniqueName,
						xercesc::DOMDocument* DOMRepresentation);
	~OViSEScenePrototype(void);
};

#endif /*OVISE_SCENE_PROTOTYPE_H_*/