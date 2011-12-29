#include<libxml/parser.h>
#include<stdio.h>
#include<errno.h>
int main()
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile("a.xml");

	if(doc == NULL) {
		fprintf(stderr,"cannot properly parse the document\n");
		exit(errno);
	};

	cur = xmlDocGetRootElement(doc);

	if(cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return ;
	}

	printf("the root node is %s\n",cur->name);
	cur = cur->xmlChildrenNode;
	printf("the next node is %s\n",cur->name);

}
