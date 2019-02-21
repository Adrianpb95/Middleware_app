
/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include "xml_Reader.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace x
{
	vector<string> xml_Reader::load_values_from_XML(int number_of_arguments, char *arguments_aux[], string file_path)
	{
		vector<string> arguments;

		for (size_t i = 0; i < number_of_arguments; i++)
		{
			arguments.push_back(arguments_aux[i]);
		}

		xml_document<> doc;
		xml_node<> * root_node;
		// Read the xml file into a vector
		ifstream theFile(file_path);

		if (theFile.good())
		{
			vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
			buffer.push_back('\0');
			// Parse the buffer using the xml file parsing library into doc 
			doc.parse<0>(&buffer[0]);
			// Find our root node
			root_node = doc.first_node("Atributes");
			//Leo cada valor de atrib, y los integro en orden
			int index_aux = 0;
			for (xml_node<> * atrib_node = root_node->first_node("Atrib"); atrib_node; atrib_node = atrib_node->next_sibling())
			{				
				string value = atrib_node->first_attribute("value")->value();

				arguments.at(index_aux) = value;
				index_aux++ ;
			}
		}
		//Retorno todos los valores leidos ordenados
		return arguments;
	}

	void xml_Reader::save_values_to_XML(vector<string> arguments)
	{
		//Recibo los argumentos de la malla en este instante y los guardo en un xml
		xml_document<> doc;
		xml_node<>* decl = doc.allocate_node(node_declaration);
		decl->append_attribute(doc.allocate_attribute("version", "1.0"));
		decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));

		doc.append_node(decl);

		xml_node<>* root = doc.allocate_node(node_element, "Atributes");
		doc.append_node(root);

		//Contador auxiliar para pasar los valores en orden
		vector<string> contador;
		for (size_t i = 0; i < 20; i++)
		{
			contador.push_back(to_string(i));
		}

		//Append de cada valor al xml
		for (int i = 0; i < arguments.size(); i++)
		{
			xml_node<>* child = doc.allocate_node(node_element, "Atrib");
			child->append_attribute(doc.allocate_attribute("name", contador.at(i).c_str()));
			child->append_attribute(doc.allocate_attribute("value", arguments.at(i).c_str()));
			child->append_attribute(doc.allocate_attribute("index", contador.at(i).c_str()));
			root->append_node(child);
		}
		
		// Convert doc to string if needed
		std::string xml_as_string;
		rapidxml::print(std::back_inserter(xml_as_string), doc);
		// Save to file
		std::ofstream file_stored("../../../../assets/UI_Values.xml");
		file_stored << doc;
		file_stored.close();
		doc.clear();
	}
	

	

}