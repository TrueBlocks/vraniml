#ifndef _CONVERT_H
#define _CONVERT_H

inline void error(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

inline void lower(char *s)
{
	while (*s)
	{
		*s = tolower(*s);
		s++;
	}
}

inline char *Skip(char *s)
{
	if (!s) return s;
	
	// skip to next white space
	while (*s && (*s != ' ' && *s != '\t'))
		s++;
	// skip over white space
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return s;
}

inline SFBool getnextline(FILE *fp, char *s)
{
	if (!fgets(s, 1000, fp)) return FALSE;

	// skip over white space
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	
	while (1)
	{
		// Look for a non-blank line starting with a numeral or EOF
		if (isdigit(s[0]) || s[0] == '-')
		{
			return TRUE;
		}
		if (!fgets(s, 1000, fp)) return FALSE;
	}
	ASSERT(0); // never happens
	return FALSE;
}

#endif