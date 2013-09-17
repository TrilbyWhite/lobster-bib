Lobster-bib
===========
A CLI frontend to the btparse bibtex database parser

Usage
-----
```bash
lobster-bib <file.bib> [ -o ] [ <search-strings> ] [ : <output-types> ] 
```
- file.bib: required and must be a bibtex database
- -o: use "or" search rather than "and" search
- search-strings: any number of strings to match against any entry field, or key=value pairs to match against a specific field.  Multi-word strings must be quoted
- output-types: select the fields to display in the output, by default all fields are printed

Suggested use
-------------
For convenient use add an alias to your shell rc file with a name of your choice and specifying your reference database
```bash
alias bib='lobster-bib ~/refdb.bib'
```

