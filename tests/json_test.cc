#include"../saber/json/json.h"
using namespace saber;
int main(){
		/*JsonInt::ptr node1=new JsonInt("node1",10);
		JsonString::ptr node2=new JsonString("node2","hello world");
		JsonDouble::ptr node3=new JsonDouble("node3",3.14);

		JsonNode::ptr node4=new JsonIntArray("node4",std::vector<int>({1,2,3,4,5,6,7,8}));
		JsonDoubleArray::ptr node5=new JsonDoubleArray("node5",std::vector<double>({1.0,2.3232,2.006}));
		JsonNode::ptr node6=new JsonStringArray("node6",std::vector<std::string>({"hello","world","this","is","my","json"}));

		JsonObject* root=new JsonObject("root");
		JsonObject* object=new JsonObject("object");
		root->pushBack(node1);
		root->pushBack(node2);
		root->pushBack(node3);

		object->pushBack(node4);
		object->pushBack(node5);
		object->pushBack(node6);
		root->pushBack(object);

		JsonObjectArray* objects=new JsonObjectArray("objects");
		objects->add(object);
		root->pushBack(objects);

		JsonTree::ptr tree=new JsonTree(root);
		std::cout<<"test1 :"<<std::endl;
		std::cout<<tree->toString()<<std::endl;
		tree->delNode("object");
		std::cout<<"test delNode :\n"<<tree->toString()<<std::endl;
		tree->release();*/
		JsonTree* tree=new JsonTree();
		std::string str="{\"node1\"       :            10,\"node2\":\"hello world\",\"node3\":3.14,\"object\":{\"node4\":[1,2,3,4,5,6,7,8],\"node5\":[1,2.3232,2.006],\"node6\":[\"hello\",\"world\",\"this\",\"is\",\"my\",\"json\"]},\"objects\":[{\"object\":{\"node4\":[1,2,3,4,5,6,7,8],\"node5\":[1,2.3232,2.006],\"node6\":[\"hello\",\"world\",\"this\",\"is\",\"my\",\"json\"]}}]}";
		tree->fromString(str);
		std::cout<<tree->toString()<<std::endl;
		std::string name="objecs";
		try{
			JsonNode* node=tree->getNode(name);
			std::cout<<node->toString()<<std::endl;
		}catch(const char * msg){
				std::cerr<<msg;
		}
		tree->release();
		return 0;
}
