/************************************************\
* NAME - a simple frontent to btparse
*
* Author: Jesse McClure, copyright 2013
* License: GPLv2
\************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <btparse.h>

#define ANY		1
#define ALL		2

int main(int argc, const char **argv) {
	if (argc < 2) exit(1);
	bt_initialize();

	int match_mode = ALL, match;
	int i, ms, me, ps, pe;
	for (i = 2; i < argc && argv[i][0] == '-'; i++) {
		if (argv[i][1] == 'o') match_mode = ANY;
	}
	ms = i;
	for (i = ms; i < argc && argv[i][0] != ':'; i++);
	me = i;
	if (i < argc && argv[i][0] == ':') i++;
	if (me < argc - 1) { ps = i; pe = argc; }
	else { ps = 0; pe = 1; }

	boolean ret;
	AST *tree = bt_parse_file((char *)argv[1],0,&ret);
	if (!ret) { bt_cleanup(); exit(1); }
	
	/* loop through entries */
	AST *entry = NULL, *field; char *str = NULL, *name = NULL;
	char *mts, *mte, *mcs;
	while ( (entry=bt_next_entry(tree,entry)) ) {
		/* check entry type */
		if (bt_entry_metatype(entry) != BTE_REGULAR) continue;
		/* test for match criteria */
		match = 0;
		for (i = ms; i < me; i++) {
			mts = mte = mcs = NULL;
			if ( (mcs=strchr(argv[i],'=')) ) {
				mcs++; /* char to right of "=" */
				mts = (char *) argv[i];
				mte = strchr(mts,'=');
			}
			field = NULL;
			while ( (field=bt_next_field(entry,field,&name)) ) { 
				str = bt_get_text(field);
				if ( (!mts && strcasestr(str,argv[i])) ||
						(mts && strncasecmp(name,mts,mte-mts)==0 &&
								strcasestr(str,mcs)) ) {
					match++;
					break;
				}
			}
		}
		/* if no match, move on to next entry */
		if ( !((match && match_mode == ANY) ||
				(match == me-ms && match_mode == ALL)) )
			continue;
		/* print selected fields, or all fields */
		field = NULL;
		if (!ps || pe - ps > 1) printf("\n");
		while ( (field=bt_next_field(entry,field,&name)) ) { 
			for (i = ps; i < pe; i++) {
				str = bt_get_text(field);
				if (str && (!ps || strcasestr(name,argv[i])) ) {
					if (!ps || pe - ps > 1)
						printf("%s:%*s%s\n",name,10-strlen(name),"",str);
					else 
						printf("%s\n",str);
				}
			}
		}
	} /* end loop through entries */
	bt_cleanup();
	return 0;
}
