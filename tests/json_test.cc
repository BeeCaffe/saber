#include"../saber/json/json.h"
using namespace saber;
int main(){
	////test 1
		/*JsonNode::ptr json_node1(new JsonNode(nullptr,nullptr,nullptr,DataType::jsonInt,"node1","",0,0,0));
		JsonNode::ptr json_node2(new JsonNode(nullptr,nullptr,nullptr,DataType::jsonInt,"node2","",0,0,0));
		JsonNode::ptr json_node3(new JsonNode(nullptr,nullptr,nullptr,DataType::jsonInt,"nod3","",0,0,0));

		json_node1->pushBack(json_node2);
		json_node1->pushFront(json_node3);
		json_node1->popBack();
		json_node1->popFront();*/
		JsonNode<int>::ptr node1=new JsonInt<int>("age",100);
		JsonNode<int>::ptr node2=new JsonString<int>("say","hello world");
		std::vector<int> array={1,2,3,4,5};
		JsonNode<int>::ptr node3= new JsonArray<int>("array",array);
		JsonNode<int>::ptr root=new JsonObject<int>("root",node1);
		JsonNode<int>::ptr node4=new JsonObject<int>("root2",node1);
		node1->setNext(node2);
		node2->setNext(node3);
		node3->setNext(node4);
		std::cout<<dynamic_cast<JsonObject<int>::ptr>(root)->toSString().str();
		delete node1;
		delete node2;
		delete node3;
		delete root;
	return 0;
}
