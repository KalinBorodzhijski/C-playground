/**
 * @file string_local.c
 * @brief Implementation of Local String Functions
 *
 * This source file provides the implementations for a series of string manipulation
 * functions that are typically part of the standard <string.h> library. These
 * implementations are for educational purposes to demonstrate how such functions
 * can be implemented in C.
 */
#include "string_local.h"

static bool is_delemiter(const char c, const char * delemiters);

//--------------------------------------------------------------
int my_strlen(const char *inputStringP, StrResult* errorP) 
{
    *errorP = E_NOK;
    uint32_t u32StringLenL = 0;

    if (NULL != inputStringP)
    {
        while (*(inputStringP++) != '\0')
        {
            u32StringLenL++;
        }
        *errorP = S_OK;
    }
    else
    {
        *errorP = E_INVALID_ARGS;
    }

    return u32StringLenL;
}

//--------------------------------------------------------------
StrResult my_strcpy(char *dest, const char *src, const uint32_t u32dest_sizeP) 
{
    StrResult resultL = E_NOK;
    uint32_t u32idxL;

    if ((NULL != dest) && (NULL != src) && (0 < u32dest_sizeP))
    {
        for (u32idxL = 0; (src[u32idxL] != '\0') && (u32idxL < u32dest_sizeP); u32idxL++)
        {
            dest[u32idxL] = src[u32idxL];
        }
        
        resultL = S_OK;

        if (u32idxL < u32dest_sizeP)
        {
            dest[u32idxL] = '\0';
        }
        else if (u32idxL == u32dest_sizeP)
        {
            dest[--u32idxL] = '\0';
            resultL = E_DEST_OUT_OF_BOUND;
        }

    }
    else
    {
        resultL = E_INVALID_ARGS;
    }

    return resultL;
}

//--------------------------------------------------------------
StrResult my_strcat(const char *src, char *dest, const uint32_t u32dest_sizeP) 
{ 
    StrResult resultL = E_NOK;
    uint32_t u32DestLenL = 0u, u32SrcLenL = 0u, u32CntL;

    if ((NULL != dest) && (NULL != src) && (0 < u32dest_sizeP))
    {
        u32DestLenL = my_strlen(dest, &resultL);
        if(S_OK == resultL)
        {
            u32SrcLenL = my_strlen(src, &resultL);
            if(S_OK == resultL)
            {
                if((u32SrcLenL + u32DestLenL) >= u32dest_sizeP)
                {
                    resultL = E_DEST_OUT_OF_BOUND;
                }
                else
                {
                    for (u32CntL = 0; u32CntL < u32SrcLenL; u32CntL++)
                    {
                        dest[(u32DestLenL + u32CntL)] = src[u32CntL];
                    }
                    resultL = S_OK;                    
                }
            }
        }
    }
    else
    {
        resultL = E_INVALID_ARGS;
    }

    return resultL;
}

//--------------------------------------------------------------
StrResult my_strcmp(const char *pStringOneP, const char *pStringTwoP,  StrResult* errorP)
{
    int16_t s16resultL = 0;
    *errorP = E_NOK;

    if ((NULL != pStringOneP) && (NULL != pStringTwoP))
    {
        while ((*(pStringOneP++) != '\0') && (*(pStringTwoP++) != '\0'))
        {
            if((*pStringOneP) != (*pStringTwoP))
            {
                s16resultL = (*pStringOneP) - (*pStringTwoP);
                break;
            }
        }
        *errorP = S_OK;
    }
    else
    {
        *errorP = E_INVALID_ARGS;
    }

    return s16resultL;
}

//--------------------------------------------------------------
char *my_strstr(char *haystack, char *needle, StrResult* errorP) 
{
    *errorP = E_NOK;
    char* pResultPosition = NULL;
    char* pHaystachCurPositionL = NULL;
    char* pNeedleCurPositionL = NULL;
    bool bNeedleFoundL;

    if ((NULL != haystack) && (NULL != needle) && (NULL != errorP))
    {

        while (*haystack != '\0')
        {
            if(*haystack == *needle)
            {
                pHaystachCurPositionL = haystack;
                pNeedleCurPositionL = needle;
                bNeedleFoundL = true;

                while((*pHaystachCurPositionL != '\0') && (*pNeedleCurPositionL != '\0'))
                {
                    if(*pHaystachCurPositionL != *pNeedleCurPositionL)
                    {
                        bNeedleFoundL = false;
                        break;
                    }
                    pHaystachCurPositionL++;
                    pNeedleCurPositionL++;
                }

                if(true == bNeedleFoundL)
                {
                    pResultPosition = haystack;
                    break;
                }
            }
            haystack++;
        }
        
        *errorP = S_OK;
    }
    else
    {
        *errorP = E_INVALID_ARGS;
    }

    return pResultPosition;
}

//--------------------------------------------------------------
StrResult my_strncat(char *dest, const char *src, size_t n) 
{ 
    StrResult resultL = E_NOK;
    uint32_t u32DestLenL = 0u, u32CntL;

    if ((NULL != dest) && (NULL != src) && (0 < n))
    {
        u32DestLenL = my_strlen(dest, &resultL);
        if(S_OK == resultL)
        {
            for (u32CntL = 0; (u32CntL < n) && (src[u32CntL] != '\0'); u32CntL++)
            {
                dest[(u32DestLenL + u32CntL)] = src[u32CntL];
            }
            dest[(u32DestLenL + u32CntL)] = '\0';
        }
        resultL = S_OK;                    
    }
    else
    {
        resultL = E_INVALID_ARGS;
    }

    return resultL;
}

//--------------------------------------------------------------
const char *my_strchr(const char *inputStringP, int c) 
{
    bool bCharFoundL = false;

    if (NULL != inputStringP)
    {
        while (*(inputStringP++) != '\0')
        {
            if(*inputStringP == c)
            {
                bCharFoundL = true;
                break;
            }
        }
    }

    return bCharFoundL ? inputStringP : NULL;
}

//--------------------------------------------------------------
StrResult my_strrev(char *s) 
{   
    uint32_t u32StrLenL = 0;
    StrResult resultL = E_NOK; 

    if (NULL != s)
    {
        u32StrLenL = my_strlen(s, &resultL);

        if(resultL == S_OK)
        {
            for (size_t i = 0; i < u32StrLenL / 2u; i++)
            {
                char tempChar = s[i];
                s[i] = s[u32StrLenL - 1 - i];
                s[u32StrLenL - 1 - i] = tempChar;
            }
        }
    }
    else
    {
        resultL = E_INVALID_ARGS;
    }

    return resultL;
}

//--------------------------------------------------------------
StrResult my_strtolower(char *s) 
{ 
    StrResult resultL = E_NOK;

    if (NULL != s)
    {
        while (*s != '\0')
        {
            if((((char)*s) >= 'A') && (((char)*s) <= 'Z'))
            {
                (*s) += 'a' - 'A';
            }
            s++;
        }
        resultL = S_OK;
    }    
    else
    {
        resultL = E_INVALID_ARGS;
    }

    return resultL;
}

//--------------------------------------------------------------
StrResult my_strtoupper(char *s) 
{   
    StrResult resultL = E_NOK;

    if (NULL != s)
    {
        while (*s != '\0')
        {
            if((((char)*s) >= 'a') && (((char)*s) <= 'z'))
            {
                (*s) -= 'a' - 'A';
            }
            s++;
        }
        resultL = S_OK;
    }
    else
    {
        resultL = E_INVALID_ARGS;
    }

    return resultL;
}

//--------------------------------------------------------------
char *my_strtok(char *s, const char *delim) 
{
    static char * pCurrentPositionL = NULL;
    static bool bEndReached = false;
    char * pStartPositionL = NULL;
    bool bDelimiterFoundL;

    if (NULL != s)
    {
        pCurrentPositionL = s;
        bEndReached = false;
    }

    if(true == bEndReached)
    {
        return NULL;
    }

    if((pCurrentPositionL != NULL) && (delim != NULL))
    {
        pStartPositionL = pCurrentPositionL;
        
        while (*pCurrentPositionL != '\0')
        {
            bDelimiterFoundL = is_delemiter(*pCurrentPositionL, delim);

            if(true == bDelimiterFoundL)
            {
                // Skip the start position if it is delimiter
                if(pCurrentPositionL == pStartPositionL)
                {
                    pStartPositionL++;
                }
                else
                {
                    *pCurrentPositionL = '\0';
                    pCurrentPositionL++;
                    break;
                }
            }
            pCurrentPositionL++;
        }

        if(*pCurrentPositionL == '\0')
        {
            bEndReached = true;
            if(pCurrentPositionL == pStartPositionL)
            {
                return NULL;
            }
        }
    }
    
    return pStartPositionL;
}

//--------------------------------------------------------------
static bool is_delemiter(const char c, const char * delemiters)
{
    bool bDelimiterFoundL = false;
    while ((*delemiters != '\0'))
    {
        if((*delemiters) == c)
        {
            bDelimiterFoundL = true;
            break;
        }
        delemiters++;
    }
    return bDelimiterFoundL;
}

//--------------------------------------------------------------