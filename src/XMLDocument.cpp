#include <libterra/XMLDocument.h>

#include <cstdio>

namespace LibTerra {
	/* tfXMLDocument */
	tfXMLDocument::tfXMLDocument() {
		m_lastError = new char[256];
	}
	tfXMLDocument::~tfXMLDocument() {
		if (m_lastError != 0) {
			delete[] m_lastError;
		}
	}

	bool tfXMLDocument::Parse(const char* _file)
	{
		pugi::xml_parse_result result = m_document.load_file(_file);
		if (!result) {
			sprintf(m_lastError, "%s", result.description());
			return false;
		}
		return true;
	}

	const char* tfXMLDocument::LastError() const {
		return (const char*)m_lastError;
	}

	tfXMLNode tfXMLDocument::Child(const char* name) const {
		return m_document.child(name);
	}

	/* tfXMLNode */
	tfXMLNode::tfXMLNode() { }
	tfXMLNode::tfXMLNode(pugi::xml_node _node)
		: m_xmlNode(_node) { }
	tfXMLNode::~tfXMLNode() { }

	const char* tfXMLNode::Name() const {
		return m_xmlNode.name();
	}

	const char* tfXMLNode::Value() const {
		return m_xmlNode.value();
	}

	bool tfXMLNode::Valid() const {
		return !m_xmlNode.empty();
	}

	tfXMLNode tfXMLNode::Child(const char* _name) const {
		return m_xmlNode.child(_name);
	}

	tfXMLAttribute tfXMLNode::Attribute(const char* _name) const {
		return m_xmlNode.attribute(_name);
	}

	tfXMLNode tfXMLNode::Parent() const {
		return m_xmlNode.parent();
	}

	tfXMLNode tfXMLNode::FirstChild() const {
		return m_xmlNode.first_child();
	}

	tfXMLNode tfXMLNode::LastChild() const {
		return m_xmlNode.last_child();
	}

	tfXMLNode tfXMLNode::NextSibling() const {
		return m_xmlNode.next_sibling();
	}

	tfXMLNode tfXMLNode::PreviousSibling() const {
		return m_xmlNode.previous_sibling();
	}

	tfXMLAttribute tfXMLNode::FirstAttribute() const {
		return m_xmlNode.first_attribute();
	}

	tfXMLAttribute tfXMLNode::LastAttribute() const {
		return m_xmlNode.last_attribute();
	}

	/* tfXMLAttribute */
	tfXMLAttribute::tfXMLAttribute() {}
	tfXMLAttribute::tfXMLAttribute(pugi::xml_attribute _attribute)
		: m_xmlAttribute(_attribute) {}
	tfXMLAttribute::~tfXMLAttribute() { }

	const char* tfXMLAttribute::Name() const {
		return m_xmlAttribute.name();
	}

	const char* tfXMLAttribute::Value() const {
		return m_xmlAttribute.value();
	}
}
