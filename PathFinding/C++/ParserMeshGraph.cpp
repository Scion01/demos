
#include "ParserMeshGraph.h"
#include <sstream>
#include <fstream>

std::string ParserMeshGraph::LoadTextContents(std::string filename)
{
	std::ifstream file(filename, std::ifstream::in);
	std::string contents;

	bool open = file.is_open();

	file.seekg(0, std::ios::end);
	contents.reserve((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);

	contents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return contents;
}

std::vector<std::string> ParserMeshGraph::SplitString(const std::string& str, char delimiter)
{
	std::stringstream ss(str);
	std::vector<std::string> stringElements;
	std::string item;
	while(std::getline(ss, item, delimiter)) 
		stringElements.push_back(item);

	return stringElements;
}

void ParserMeshGraph::LoadUnreachableNodesFromFile(MeshGraph* meshGraph, std::string filename)
{
	std::vector<std::string> nodeList = SplitString(LoadTextContents(filename), ',');
	for(unsigned int i = 0; i < nodeList.size(); i++)
		meshGraph->SetUnreachableNode(atoi(nodeList[i].c_str()));
}
