
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* count of compare */
int		count;

int		DEBUG;

int		get_next_version;


void get_next_1(const char *pattern, int next[]);
void get_next_2(const char *pattern, int next[]);

int first_index_KMP(const char *targe, const char *pattern);
int all_index_KMP(const char *targe, const char *pattern, 
					int index_array[]);

int first_index_native(const char *targe, const char *pattern);
int all_index_native(const char *targe, const char *pattern, 
					int index_array[]);

int main(int argc, char *argv[])
{
	int		len = 0;
	int		*index_array = NULL;

	if (argc < 3) {
		fprintf(stderr, "arguments must be less 3\n");
		exit(1);
	}

	DEBUG = 1;
	//get_next_version = 1;

	len = strlen(argv[1]);
	index_array = (int *)calloc(len, sizeof(int));

	all_index_KMP(argv[1], argv[2], index_array);

	if (index_array)
		free(index_array);

	return 0;
}

void get_next_1(const char *pattern, int next[])
{
	int		len = 0;
	int		i = 0;
	int		j = 0;

	fprintf(stdout, "This is get_next_1 to get next array "
						"of string: %s\n"
						"MKP, version 1\n", pattern);

	len = strlen(pattern);

	i = 0; j = 0; next[i++] = -1;
	if (pattern[1] == pattern[0])
		next[1] = 1;
	else
		next[1] = 0;
	while (i < len - 1) {
		if (j == -1 || pattern[i] == pattern[j]) {
			++i; ++j;
			next[i] = j;
		}else {
			j = next[j];
		}
	}

	return;
}

void get_next_2(const char *pattern, int next[])
{
	int		len = 0;
	int		i = 0;
	int		j = 0;

	fprintf(stdout, "This is get_next_2 to get next array "
						"of string: %s\n"
						"MKP, version 2\n", pattern);

	len = strlen(pattern);
	i = 0; j = 0; next[i++] = -1;
	if (pattern[1] == pattern[0])
		next[1] = 1;
	else
		next[1] = 0;
	while (i < len - 1) {
		if (j == -1 || pattern[i] == pattern[j]) {
			++i; ++j;
			if (pattern[i] != pattern[j])
				next[i] = j;
#if 0
			else if (next[j] == -1)
				next[i] = 0;
#endif
			else
				next[i] = next[j];
		}else {
			j = next[j];
		}
	}

	return;
}

int first_index_KMP(const char *targe, const char *pattern)
{
	int		index = -1;
	int		len = 0;
	int		*next = NULL;
	int		i = 0;

	fprintf(stdout, "This is first_index_KMP\n");

	len = strlen(pattern);
	next = (int *)calloc(len, sizeof(int));

	if (get_next_version == 1) {
		get_next_1(pattern, next);
		if (DEBUG) {
			fprintf(stdout, "next[]:\n");
			for (i = 0; i < len; ++i) {
				fprintf(stdout, "%d: %d, ", i, next[i]);
			}
			fprintf(stdout, "\n");
		}
	}else if(get_next_version == 2){
		get_next_2(pattern, next);
		if (DEBUG) {
			fprintf(stdout, "next[]:\n");
			for (i = 0; i < len; ++i) {
				fprintf(stdout, "%d: %d, ", i, next[i]);
			}
			fprintf(stdout, "\n");
		}
	}else {
		get_next_1(pattern, next);
		if (DEBUG) {
			fprintf(stdout, "next[]:\n");
			for (i = 0; i < len; ++i) {
				fprintf(stdout, "%d: %d, ", i, next[i]);
			}
			fprintf(stdout, "\n");
		}
		memset(next, 0, len * sizeof(int));
		get_next_2(pattern, next);
		if (DEBUG) {
			fprintf(stdout, "next[]:\n");
			for (i = 0; i < len; ++i) {
				fprintf(stdout, "%d: %d, ", i, next[i]);
			}
			fprintf(stdout, "\n");
		}
	}

	fprintf(stdout, "This is first_index_KMP\n");
	if (next)
		free(next);
	else
		fprintf(stdout, "This is first_index_KMP\n");

	return index;
}

int all_index_KMP(const char *targe, const char *pattern, 
					int index_array[])
{
	int		ret = 0;
	int		len1 = 0;
	int		len2 = 0;

	fprintf(stdout, "This is all_index_KMP\n");

	len1 = strlen(targe);
	len2 = strlen(pattern);

	if (len1 < len2) {
		fprintf(stderr, "targe is shorter than pattern\n");
		ret = -1;
		goto out;
	}

	first_index_KMP(targe, pattern);

out:
	return ret;
}


int first_index_native(const char *targe, const char *pattern)
{
	int		index = -1;

	fprintf(stdout, "This is first_index_native\n");

	return index;
}

int all_index_native(const char *targe, const char *pattern, 
					int index_array[])
{
	int		ret = -1;
	fprintf(stdout, "This is all_index_native\n");

	return ret;
}
