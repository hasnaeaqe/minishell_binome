/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:37:08 by cbayousf          #+#    #+#             */
/*   Updated: 2025/06/22 10:15:58 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *expand_functions(char *str, char **env)
// {
//     int i=0;
//     int k=0;
//     char *resutl_str;
//     while(str[i])
//     {
//         if (str[i]=='\'')
//         {
//             i++;
//             while(str[i] && str[i]!='\'')
//                 i++;
//             if (str[i]=='\'')
//                 i++;
//         }
//         else if (str[i] =='"')
//         {
//             i++;
//             while (str[i] && str[i]!= '"')
//             {
//                 if (str[i]=='$')
//                 {
//                     resutl_str=ft_my_strlcat(resutl_str,str,i-k);
//                     //expand(&str[++i], env);
//                 }
//                 i++;
//             }
//             if (str[i]=='"')
//                 i++;
//         }
//         else
//         {
//             if (str[i]=='$')
//             {
                
//                 //expand(&str[++i], env);
//             }
//             i++;
//         }
           
//     }
//     return (NULL);
// }







// char *find_expand(char *str)
// {
//     int i = 0;
//     int j = 0;
//     char *dest;
//     while (str[i])
//     {
//         if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i]=='_' || str[i]=='$')
//             i++;
//         else
//             break;
//     }
//     dest = ft_malloc((i + 1) * sizeof(char));
//     while (j < i)
//     {
//         dest[j] = str[j];
//         j++;
//     }
//     dest[j]='\0';
//     return (dest);
// }
// char *extract_value(char *dest, char **env)
// {
//     t_env *en;
//     int i=0;
//     char *dst=NULL;
    
//     if (dest[i]=='$')
//         dst=&dest[++i];
//     en = ft_env(env);
//     while (en)
//     {
//         if (ft_strcmp(en->key, dst) == 0)
//             return (en->value);
//         en = en->next;
//     }
//     return ("");
// }
// char *rwina(char *value,char *dest,char *expand_value, int len)
// {
//     char *total_str;
//     int i = 0;
//     int j = 0;

//     total_str = ft_malloc((len + 1) * sizeof(int));
//     // puts(value);
//     // puts(dest);
//     while (value[i])
//     {
//         if (value[i]=='$')
//         {
//             if (ft_strnstr(&value[i], dest,ft_strlen(&value[i]))==1)
//             {
//                 while (*expand_value)
//                 {
//                     total_str[j++] = *expand_value++;
//                 }
//                 i+=ft_strlen(dest);
//             }
//             else
//             {
//                 total_str[j]=value[i];
//                 i++;
//                 j++;    
//             }
//         }
//         else
//         {
//             total_str[j]=value[i];
//             i++;
//             j++;    
//         }
//     }
//     total_str[j] = '\0';
//     return (total_str);
// }
// void expand(t_token **token,char *str, char **env)
// {
//     char *dest;
//     char *expand_value;
//     t_token *tmp;
//     int len;
//     char *value;
//     char *total_str;

//     tmp = *token;
//     value = ft_strdup((*token)->value);
//     printf("value : %s, str: %s\n",value,str);
//     dest = find_expand(str);
//     expand_value = extract_value(dest, env);
//     len = ft_strlen((*token)->value) - ft_strlen(dest) + ft_strlen(expand_value);
//     // free((*token)->value);
//     // (*token)->value = ft_malloc(len * sizeof(char));
//     // printf("value : %s, dest: %s , exapnd : %s , str: %s\n",value,dest,expand_value,str);
//     total_str = rwina(value,dest,expand_value, len);
//     // printf("%s\n",total_str);
//     (*token)->value = total_str;
//     (*token)->next=tmp->next;
//     // free(value);
//     // printf("token : %s\n",(*token)->value);
// }
// int petit_test(char *str ,int *k)
// {
//     int i=0;
//     while (str[i] && str[i]=='$')
//     {
//         i++;
//         (*k)++;
//     }
//     return (i);
// }
// void	expand_tokens(t_token **token, char **env)
// {
//     t_token *tmp;
//     char *str;
//     int i;
    
//     tmp = *token;
//     while(tmp)
//     {
//         if (tmp->type == TOK_WORD)
//         {
//             str = tmp->value;
//             i = 0;
//             while (str[i])
//             {
//                 if (str[i]=='\'')
//                 {
//                     i++;
//                     while(str[i] && str[i]!='\'')
//                         i++;
//                     if (str[i]=='\'')
//                         i++;
//                 }
//                 else if (str[i] =='"')
//                 {
//                     i++;
//                     while (str[i] && str[i]!= '"')
//                     {
//                         if (str[i]=='$' && str[i+1])
//                         {
//                             if (petit_test(&str[i],&i)%2 != 0)
//                                 expand(&tmp,&str[i], env);
//                         }
//                         i++;
//                     }
//                     if (str[i]=='"')
//                         i++;
//                 }
//                 else
//                 {
//                     if (str[i]=='$')
//                     {
//                         if (petit_test(&str[i],&i) % 2 != 0 && str[i])
//                             expand(&tmp,&str[i], env);
//                     }
//                     else
//                         i++;
//                 }
//             }   
//         }
//         printf("%s\n",tmp->value);
//         tmp = tmp->next;
//     }
// }



// void expand_tokens(t_token **token, char **env)
// {
//     t_token *tmp = *token;

//     while (tmp)
//     {
//         if (tmp->type == TOK_WORD || tmp->type == TOK_REDIR) // utile aussi pour > $F
//         {
//             char *new = ft_strdup(tmp->value);
//             int i = 0;
//             while (new[i])
//             {
//                 if (new[i] == '\'') // simple quotes = skip
//                 {
//                     i++;
//                     while (new[i] && new[i] != '\'')
//                         i++;
//                 }
//                 else if (new[i] == '"') // double quotes
//                 {
//                     i++;
//                     while (new[i] && new[i] != '"')
//                     {
//                         if (new[i] == '$')
//                         {
//                             char *expand_start = &new[i];
//                             char *key = find_expand(expand_start);
//                             char *value = extract_value(key, env);
//                             int len = ft_strlen(new) - ft_strlen(key) + ft_strlen(value);
//                             new = rwina(new, key, value, len);
//                             break; // on repart depuis début
//                         }
//                         i++;
//                     }
//                 }
//                 else if (new[i] == '$')
//                 {
//                     char *expand_start = &new[i];
//                     char *key = find_expand(expand_start);
//                     char *value = extract_value(key, env);
//                     int len = ft_strlen(new) - ft_strlen(key) + ft_strlen(value);
//                     new = rwina(new, key, value, len);
//                     break; // on repart depuis début
//                 }
//                 else
//                     i++;
//             }
//             tmp->value = new;
//         }
//         tmp = tmp->next;
//     }
// }
// char *rwina(char *value, char *dest, char *expand_value, int len)
// {
//     char *result;
//     int i = 0, j = 0;
//     int dest_len = ft_strlen(dest);

//     result = ft_malloc(len + 1);
//     while (value[i])
//     {
//         if (value[i] == '$' && ft_strncmp(&value[i + 1], dest, dest_len) == 0)
//         {
//             // injecter l'expansion
//             for (int k = 0; expand_value[k]; k++)
//                 result[j++] = expand_value[k];
//             i += dest_len + 1; // saute $ + nom
//         }
//         else
//             result[j++] = value[i++];
//     }
//     result[j] = '\0';
//     return (result);
// }
// char *extract_value(char *dest, char **env)
// {
//     t_env *en;
    
//     if (ft_strcmp(dest, "?") == 0)
//         return (ft_itoa(g_exit_status)); // ⚠️ définir `g_exit_status` globalement

//     en = ft_env(env);
//     while (en)
//     {
//         if (ft_strcmp(en->key, dest) == 0)
//             return (en->value ? en->value : "");
//         en = en->next;
//     }
//     return ("");
// }
// char *find_expand(char *str)
// {
//     int i = 1; // on saute le premier '$'
//     int j = 0;
//     char *dest;

//     if (!str || str[0] != '$')
//         return (ft_strdup(""));

//     // $?
//     if (str[1] == '?')
//         return (ft_strdup("?"));

//     while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
//         i++;

//     dest = ft_malloc(i * sizeof(char)); // sans le '$'
//     while (++j < i)
//         dest[j - 1] = str[j];
//     dest[j - 1] = '\0';

//     return (dest);
// }


// char *find_expand(char *str)
// {
//     int i = 1;
//     int j = 0;
//     char *dest;

//     if (!str || str[0] != '$')
//         return (ft_strdup(""));

//     if (str[1] == '?')
//         return (ft_strdup("?"));

//     if (ft_isdigit(str[i]))
//     {
//         dest = ft_malloc(2 * sizeof(char));
//         dest[j++] = str[i];
//         dest[j] = '\0';
//         return (dest); // 🔧 Ajouté
//     }

//     while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
//         i++;

//     dest = ft_malloc((i) * sizeof(char) + 1); // taille sans le '$' + '\0'

//     j = 0;
//     while (j < i - 1) // on saute le '$' => on commence à copier à str[1]
//     {
//         dest[j] = str[j + 1];
//         j++;
//     }
//     dest[j] = '\0';

//     return (dest);
// }
