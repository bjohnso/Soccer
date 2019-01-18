#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void	itoa_isnegative(int *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

static char	*ft_itoa(int n){
	int tmp;
	int len;
	int neg;
	char *str;

	tmp = n;
	len = 2;
	neg = 0;
	itoa_isnegative(&n, &neg);
	while (tmp /= 10)
		len++;
	len += neg;
	if ((str = (char *)malloc(sizeof(char)* len)) == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len --)
	{
		str[len] = n % 10 + '0';
		n = n/10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

static int      delim(char *str)
{
        if (*str == ',' || *str == '\n' || *str == '\0')
                return (1);
	if(*str == ' ')
	{
		str++;
		if (*str <= '9' && *str >= '0')
			return(1);
		str-=2;
		if (*str == ',' || (*str <= '9' && *str >= '0'))
			return (1);
	}
        return (0);
}

static int      count_words(char *str)
{
        int     count;

        count = 0;
        while (*str && delim(str))
                str++;
        while (*str)
        {
                while (*str && delim(str))
                        str++;
                if (*str && !delim(str))
                        count++;
                while (*str && !delim(str))
                        str++;
        }
        return (count);
}

static char     *malloc_word(char *str)
{
        int     i;
        char    *word;

        i = 0;
        while (str[i] && !delim(str + i))
                i++;
        word = (char *)malloc(sizeof(char) * (i + 1));
        i = 0;
        while (str[i] && !delim(str + i))
        {
                word[i] = str[i];
                i++;
        }
        word[i] = '\0';
        return (word);
}

char            **ft_split(char *str)
{
        int     i;
        int     words;
        char    **tab;

        i = -1;
        words = count_words(str);
        tab = (char **)malloc(sizeof(char *) * (words + 1));
        while (*str)
        {
                while (*str && delim(str))
                        str++;
                if (*str && !delim(str))
                        tab[++i] = malloc_word(str);
                while (*str && !delim(str))
                        str++;
        }
        tab[++i] = NULL;
        return (tab);
}

int      main(int argc, char **argv)
{
	char **result;
	char **split;
	char **split_b;
	char **str;
	char *ptr;
	char tmp[1000];
	int a, i, j, l, dup, fail;	
	i = 0;
	j = -1;
	dup = 0;
	a = 0;
	fail = 0;
	result = NULL;
	str = NULL;
	FILE *fp;
	char output[]="output.txt";
	char buff[1000];
	fp = fopen(output, "w");
	fclose(fp);
	char *new_ptr = &buff[0];
	if (argc < 2)
	{
        	printf("ENTER DATA (FORMAT MUST BE CORRECT) OR TEXT FILE PATH\n");
			scanf("%[^\n]s", tmp);
		if (strstr(tmp, ".txt")){
			if(!(fp = fopen(tmp, "r")))
				fail = 1;
			else{
				while (fgets((new_ptr + i), 2, fp))
					i++;
				fclose(fp);
				if(!(result = ft_split(new_ptr)))
					fail = 1;
			}	
		}
		else{
        		result = ft_split(tmp);
			while (result[i]){
				i++;
			}
			if (i % 4)
				fail = 1;
		}
	}
	else{
		if (strstr(argv[1], ".txt")){
			if(!(fp = fopen(argv[1], "r")))
				fail = 1;
			else{
				while (fgets((new_ptr + i), 2, fp))
					i++;
				fclose(fp);
				if(!(result = ft_split(new_ptr)))
					fail = 1;
			}
		}
		else{
			result = ft_split(argv[1]);
			while(result[i]){
                		i++;
        		}
        		if (i % 4)
                		fail = 1;
		}
	}
	if (fail)
		printf("%s\n", "FAILED, INCORRECT INPUT");
	else{
	i = 0;
        while(result[i * 4] != NULL){
		if (atoi(result[i * 4 + 1]) > atoi(result[i * 4 + 3])){
			fp = fopen(output, "r+");
			while (fgets(buff, 255, fp)){
                		if (strstr(buff, result[i * 4])){	
                     			split = ft_split(buff);
					l = atoi(split[1]) + 3;
					fseek(fp, -strlen(split[1])-1, SEEK_CUR);
					fputs(ft_itoa(l), fp); 
					dup = 1;
					free(split);
                     			break ;
				}
                		else{
                     			dup = 0;
                		}
              		}
              		fclose(fp);
              		if (!dup){
				fp = fopen(output, "a+");
              			while (result[i * 4][++j] != '\0'){
                   			fprintf(fp, "%c", result[i * 4][j]);
                		}
                		fprintf(fp, "%s\n", " 3");
                		j = -1;
				fclose(fp);
          		}
              		fp = fopen(output, "r+");
               		while (fgets(buff, 255, fp)){
                  		if (strstr(buff, result[i * 4 + 2])){
					split = ft_split(buff);	
                        		l = atoi(split[1]) + 0;
                       		 	fseek(fp, -strlen(split[1])-1, SEEK_CUR);
                        		fputs(ft_itoa(l), fp);
					free(split);
                    			dup = 1;
                    			break ;
                 		}
                 		else{
                    			dup = 0;
                  		}
               		}
               		fclose(fp);
               		if (!dup){
				fp = fopen(output, "a+");
               			while (result[i * 4 + 2][++j] != '\0'){           
		       			fprintf(fp, "%c", result[i * 4 + 2][j]);
                		}
                		fprintf(fp, "%s\n", " 0");
				fclose(fp);
                	}
               }
		if(atoi(result[i * 4 + 1]) < atoi(result[i * 4 + 3])){
			fp = fopen(output, "r+");
			while (fgets(buff, 255, fp)){
				if (strstr(buff, result[i * 4 + 2])){
					split = ft_split(buff);
                        		l = atoi(split[1]) + 3;
                        		fseek(fp, -strlen(split[1])-1, SEEK_CUR);
                        		fputs(ft_itoa(l), fp);
                             		dup = 1;
					free(split);
                             		break ;
                           	}
                          	else{
                            		dup = 0;
                          	}
			}
			fclose(fp);
			if (!dup){
				fp = fopen(output, "a+");
				while (result[i * 4 + 2][++j] != '\0'){
					fprintf(fp, "%c", result[i * 4 + 2][j]);
				}
				fprintf(fp, "%s\n", " 3");
				j = -1;
				fclose(fp);
			}
			fp = fopen(output, "r+");
			while (fgets(buff, 255, fp)){
				if (strstr(buff, result[i * 4])){
					split = ft_split(buff);
					l = atoi(split[1]) + 0;
					fseek(fp, -strlen(split[1])-1, SEEK_CUR);
					fputs(ft_itoa(l), fp);
					dup = 1;
					free(split);
					break ;
				}
				else{
					dup = 0;
				}
			}
			fclose(fp);
			if (!dup){
				fp = fopen(output, "a+");
				while (result[i * 4][++j] != '\0'){
					fprintf(fp, "%c", result[i * 4][j]);
				}
				fprintf(fp, "%s\n", " 0");
				fclose(fp);
			}
		}
		if (atoi(result[i * 4 + 1]) == atoi(result[i * 4 + 3])){
			fp = fopen(output, "r+");
			while (fgets(buff, 255, fp)){
				if (strstr(buff, result[i * 4])){
					split = ft_split(buff);
					l = atoi(split[1]) + 1;
					fseek(fp, -strlen(split[1])-1, SEEK_CUR);
                        		fputs(ft_itoa(l), fp);
					dup = 1;
					free(split);
					break ;
				}
				else{
					dup = 0;
				}
			}
			fclose(fp);
			if (!dup){
				fp = fopen(output, "a+");
				while (result[i * 4][++j] != '\0'){
					fprintf(fp, "%c", result[i * 4][j]);
				}          
				fprintf(fp, "%s\n", " 1");
				j = -1;
				fclose(fp);
                        }
                        fp = fopen(output, "r+");
			while (fgets(buff, 255, fp)){
				if (strstr(buff, result[i * 4 + 2])){
					split = ft_split(buff);
                        		l = atoi(split[1]) + 1;
                        		fseek(fp, -strlen(split[1])-1, SEEK_CUR);
                        		fputs(ft_itoa(l), fp);
                            		dup = 1;
					free(split);
                            		break ;
                          	}
				else{
					dup = 0;
				}
			}
			fclose(fp);
			if (!dup){
				fp = fopen(output, "a+");
				while (result[i * 4 + 2][++j] != '\0'){
					fprintf(fp, "%c", result[i * 4 + 2][j]);
				}           
				fprintf(fp, "%s\n", " 1");
				fclose(fp);
			}
		}
		j = -1;
		i++;
	}
	free(result);
	fp = fopen(output, "r");
	while (fgets(buff, 255, fp))
		a++;
	str = (char **)malloc(sizeof(char*) * (a + 1));
	a = -1;
	fclose(fp);
	fp = fopen(output, "r");
	char *buff_ptr = &buff[0];
	while (fgets((buff_ptr += 30), 30, fp)){
		str[++a] = buff_ptr;
	}
	str[++a] = NULL;
	fclose(fp);
	for(i = 0; i < (a - 2); i++){
		split = ft_split(str[i]);
		l = atoi(split[1]);
		split_b = ft_split(str[i + 1]);
		dup = atoi(split_b[1]);
		if (dup > l){
			ptr = str[i];
			str[i] = str[i + 1];
			str[i + 1] = ptr;
			i = -1;
		}
		else if (dup == l){
			if (strcmp(split[0], split_b[0]) > 0){
				ptr = str[i];
				str[i] = str[i + 1];
				str[i + 1] = ptr;
				i = -1;
			}
		}
		free(split);
		free(split_b);
	}
	i = -1;
	j = -1;
	a = 1;
	while(str[++i]){
		split = ft_split(str[i]);
		split_b = ft_split(str[i]);
		if (j == atoi(split[1]))
			if (atoi(split_b[1]) != 1)
				printf("%d. %s, %s pts\n", (a - 1), split_b[0], split_b[1]);
			else
				printf("%d. %s, %s pt\n", (a - 1), split_b[0], split_b[1]);
		else{
			if (atoi(split_b[1]) != 1)
				printf("%d. %s, %s pts\n", (a), split_b[0], split_b[1]);
			else
				printf("%d. %s, %s pt\n", (a), split_b[0], split_b[1]);
			a++;
		}
		j = atoi(split[1]);
		free(split);
		free(split_b);
	}
	free(str);
	}
	return (1);
}
