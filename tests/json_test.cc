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
		JsonNode<int>::ptr node1=new JsonInt("node1",100);
		JsonNode<int>::ptr node2=new JsonString("node2","hello world");
		std::vector<double> array={1,2,3,4,5};
		JsonNode<double>::ptr node3= new JsonArray<double>("node3",array);
		JsonNode<int>::ptr node4= new JsonInt("node4",100);
		JsonNode<int>::ptr node5= new JsonInt("node5",100);
		JsonNode<int>::ptr root1=new JsonObject("root1",node1);
		JsonNode<int>::ptr root2=new JsonObject("root2",node4);
		node1->setNext(node2);
		node2->setNext(node3);
		node3->setNext(node4);
		node3->setChild(root2);
		node4->setNext(node5);
		std::cout<<dynamic_cast<JsonObject::ptr>(root1)->toSString().str();
		delete node1;
		delete node2;
		delete node3;
		delete node4;
		delete node5;
		delete root1;
		delete root2;
	return 0;
}
