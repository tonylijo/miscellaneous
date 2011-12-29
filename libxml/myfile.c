#include<parser.h>
void parse_file(char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	if(doc == NULL) {
		fprintf(stderr,"Document not parsed successfully.\n");
		return 0;
	}

	cur = xmlDocGetRootElement(doc);
	printf("root node is %s",cur->name);
}
int main()
{
	parse_file(argv[1]);
}
