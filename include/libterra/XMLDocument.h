#ifndef _LIBTERRA_INCLUDE_XMLDOCUMENT_H_
#define _LIBTERRA_INCLUDE_XMLDOCUMENT_H_

#include <pugixml.hpp>

namespace LibTerra {
	class tfXMLAttribute;

	class tfXMLNode {
	public:
		tfXMLNode();
		tfXMLNode(pugi::xml_node _node);
		virtual ~tfXMLNode();

		const char*	Name() const;
		const char*	Value() const;
		bool		Valid() const;
		const char* 	ChildValue() const;

		tfXMLNode	Child(const char* _name) const;
		tfXMLAttribute	Attribute(const char* _name) const;

		tfXMLNode Parent() const;
		tfXMLNode FirstChild() const;
		tfXMLNode LastChild() const;
		tfXMLNode NextSibling() const;
		tfXMLNode PreviousSibling() const;

		tfXMLAttribute FirstAttribute() const;
		tfXMLAttribute LastAttribute() const;

	protected:
		pugi::xml_node m_xmlNode;
	};

	class tfXMLAttribute {
	public:
		tfXMLAttribute();
		tfXMLAttribute(pugi::xml_attribute _attribute);
		virtual ~tfXMLAttribute();

		const char* Name() const;
		const char* Value() const;

	private:
		pugi::xml_attribute m_xmlAttribute;
	};

	class tfXMLDocument : public tfXMLNode {
	public:
		tfXMLDocument();
		virtual ~tfXMLDocument();

		bool Parse(const char* _file);
		bool Write(const char* _file);
		const char* LastError() const;
	private:
		pugi::xml_document m_document;
		char m_lastError[256];
	};
}

#endif
