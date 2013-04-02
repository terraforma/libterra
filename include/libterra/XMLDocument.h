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

		void SetName(const char* _name);
		void SetValue(const char* _value);

		tfXMLNode	Child(const char* _name) const;
		tfXMLAttribute	Attribute(const char* _name) const;

		tfXMLNode Parent() const;
		tfXMLNode FirstChild() const;
		tfXMLNode LastChild() const;
		tfXMLNode NextSibling() const;
		tfXMLNode PreviousSibling() const;

		tfXMLAttribute FirstAttribute() const;
		tfXMLAttribute LastAttribute() const;

		tfXMLNode AppendChild(const char* _name);
		tfXMLNode PrependChild(const char* _name);
		tfXMLNode InsertChildBefore(const char* _name, const tfXMLNode& _other);
		tfXMLNode InsertChildAfter(const char* _name, const tfXMLNode& _other);
		bool RemoveChild(const tfXMLNode& _node);

		tfXMLAttribute AppendAttribute(const char* _name);
		tfXMLAttribute PrependAttribute(const char* _name);
		tfXMLAttribute InsertAttributeBefore(const char* _name, const tfXMLAttribute& _other);
		tfXMLAttribute InsertAttributeAfter(const char* _name, const tfXMLAttribute& _other);
		bool RemoveAttribute(const tfXMLAttribute& _attribute);

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

		void SetName(const char* _name);
		void SetValue(const char* _value);

	private:
		friend class tfXMLNode;
		pugi::xml_attribute m_xmlAttribute;
	};

	class tfXMLDocument {
	public:
		tfXMLDocument();
		virtual ~tfXMLDocument();

		tfXMLNode CreateRoot(const char* name);
		tfXMLNode Root();

		bool Parse(const char* _file);
		bool Write(const char* _file);
		const char* LastError() const;
		
	private:
		pugi::xml_document m_document;
		pugi::xml_node m_root;
		char m_lastError[256];
	};
}

#endif
